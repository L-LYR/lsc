/*
  Symbol Table is designed in a harry.
  So the interfaces defined here are all bullshits.
*/

#include "symbol_table.h"

#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

#include "../lib/llsc.h"
#include "exception.h"
#include "limit.h"
#include "stdbool.h"
#include "symbol_table.h"

// from lscp.c
extern _Bool Pause;
extern Fmt SymbolTableDisplayFmt;

static const char *ReservedSymbolList[] = {
    "void", "i32", "f32", "string", "bool", "if", "else", "for", "return", "break", "continue", "print", "scan", "+", "-", "++", "--", "~", "!", "*", "/", "%",  "<",
    ">",    "<=",  ">=",  "==",     "!=",   "<<", ">>",   "&",   "|",      "^",     "&&",       "||",    "=",    ",", "(", ")",  "[",  "]", "{", "}", ";", NULL,
};

static const char *SymbolTypeStrs[] = {
    "Function",
    "Variable",
};

void AtomInit() { AtomLoad(ReservedSymbolList); }

SymbolTable GlobalSymbolTable = NULL;
SymbolTable CurrentSymbolTable = NULL;
static int DefaultTableSize = 32;
static int CurID = 0;

static Scope *_NewScope(Scope *peer, Scope *prev, ScopeType t, const char *name, int level, struct table_t *tab) {
  Scope *s = ArenaAllocFor(sizeof(Scope));
  s->id = CurID++;
  s->level = level;
  s->name = name;
  s->stkTop = 0;
  s->peer = peer;
  s->prev = prev;
  s->next = NULL;
  s->curTab = tab;
  s->sType = t;
  return s;
}

static Attribute *_NewAttribute(SymbolType t, const char *type, int32_t addr, int declLoc) {
  Attribute *a = ArenaAllocFor(sizeof(Attribute));
  a->sType = t;
  a->type = type;
  a->address = addr;
  a->declLoc = declLoc;
  a->aa.f = NULL;
  return a;
}

static Scope *_NewDummyLayer(Scope *prev) {
  Scope *s = ALLOC(sizeof(Scope));
  memset(s, 0, sizeof(Scope));
  s->id = -1;
  s->prev = prev;
  s->level = prev->level + 1;
  return s;
}

static FuncDefAttr *_NewFuncDefAttr(int defLoc, const char *rt, int paraNum) {
  int size = sizeof(FuncDefAttr) + sizeof(const char *) * paraNum;
  FuncDefAttr *a = ArenaAllocFor(size);
  memset(a, 0, size);
  a->defLoc = defLoc;
  a->returnType = rt;
  a->paraNum = paraNum;
  return a;
}

static void _SymbolTableInit() {
  struct table_t *t = TableCreate(DefaultTableSize, (equal_t)AtomEqual, (hash_t)AtomHash);
  GlobalSymbolTable = _NewScope(NULL, NULL, Global, "Global Scope", 0, t);
  CurrentSymbolTable = GlobalSymbolTable;
}

static void _AddPeerScope(ScopeType type, const char *name) {
  CurrentSymbolTable->peer = _NewScope(NULL, CurrentSymbolTable->prev, type, name, CurrentSymbolTable->level, NULL);
  CurrentSymbolTable = CurrentSymbolTable->peer;
}

// wrapper of fprintf for stderr
static void _Notify(const char *fmt, ...) {
  // generally notify
  va_list args;
  va_start(args, fmt);
  vfprintf(stderr, fmt, args);
  va_end(args);
}

static void _NotifyRedeclaration(int curLine, const char *id, SymbolType declareType, int declareLine) {
  static const char *Redeclaration = "Line %d: '%s' has been declared as '%s' at line %d.\n\n";
  _Notify(Redeclaration, curLine, id, SymbolTypeStrs[declareType], declareLine);
}

static void _NotifyRedefinition(int curLine, const char *id, SymbolType defineType, int defineLine) {
  static const char *Redefinition = "Line %d: '%s' has been defined as '%s' at line %d.\n\n";
  _Notify(Redefinition, curLine, id, SymbolTypeStrs[defineType], defineLine);
}

static void _NotifyTypeConflict(int curLine, const char *id, const char *tNew, const char *tOld, int declareLine) {
  static const char *Conflict = "Line %d: Conflicting types for '%s', '%s' is no match for '%s' at line %d.\n\n";
  _Notify(Conflict, curLine, id, tNew, tOld, declareLine);
}

static void _NotifyInvalidLocOfJumpStm(int curLine, const char *stm, const char *loc) {
  static const char *InvalidLocOfJumpStm = "Line %d: '%s' statement is not in %s.\n\n";
  _Notify(InvalidLocOfJumpStm, curLine, stm, loc);
}

static void _NotifyWrongReturnStm(int curLine, const char *id, _Bool needReturn) {
  static const char *VoidFunctionShouldNotReturn = "Line %d: void function '%s' should not return a value.\n\n";
  static const char *NonVoidFunctionMustReturn = "Line %d: non-void function '%s' need return a value.\n\n";
  if (!needReturn) {
    _Notify(VoidFunctionShouldNotReturn, curLine, id);
  } else {
    _Notify(NonVoidFunctionMustReturn, curLine, id);
  }
}

static void _NotifyRepetition(Attribute *old, Attribute *new, const char *id) {
  // for the way of management of memory,
  // redefinition of function will not be notified here.
  if (new->sType == Variable) {  // redeclaration
    if (old->declLoc != -1) {
      _NotifyRedeclaration(new->declLoc, id, old->sType, old->declLoc);
    } else if (old->aa.f != NULL) {
      _NotifyRedefinition(new->declLoc, id, old->sType, old->aa.f->defLoc);
    } else {
      RAISE(Unreachable);
    }
  } else if (new->sType == Function) {
    if (old->sType == Variable) {  // redeclaration
      _NotifyRedeclaration(new->declLoc, id, old->sType, old->declLoc);
    } else if (old->sType == Function) {
      _Bool isDecl = new->declLoc != -1;
      _Bool hasDecl = old->declLoc != -1;
      _Bool hasDef = old->aa.f != NULL;

      if (hasDef) {  // redefinition
        _NotifyRedefinition(new->declLoc, id, old->sType, old->aa.f->defLoc);
      } else if (hasDecl && isDecl) {  // redeclaration
        _NotifyRedeclaration(new->declLoc, id, old->sType, old->declLoc);
      }
    }
  }
}

static void _PauseForDisplay() {
  if (Pause) {
    fprintf(stdout, "Stop For Display Current Symbol Table.\n");
    DisplaySymbolTable(GlobalSymbolTable, &SymbolTableDisplayFmt);
    fprintf(stdout, "Press Any Key To Continue...\n");
    getchar();
  }
}

static void _AddSymbol(Scope *s, const char *id, Attribute *attr) {
  if (s->curTab == NULL) {
    s->curTab = TableCreate(DefaultTableSize, (equal_t)AtomEqual, (hash_t)AtomHash);
  }
  Attribute *a = TableGet(s->curTab, id);
  if (a == NULL) {
    CurrentSymbolTable->stkTop += SizeOf(attr->type);
    TablePut(s->curTab, id, attr);
    _PauseForDisplay();
  } else {
    _NotifyRepetition(a, attr, id);
  }
}

// called when it comes to a definition of function
// return the corresponding attribute pointer
// if the return value is NULL, it occurs an
static Attribute *_CheckFuncDef(ASTNode *id, const char *t) {
  Attribute *a = NULL;
  Scope *s = GlobalSymbolTable;
  if (s->curTab != NULL) {
    a = TableGet(s->curTab, id->attr[0]);
  }  // s->curTable == NULL there must have a == NULL.
  if (a == NULL) {
    a = _NewAttribute(Function, t, 0, id->line);
    _AddSymbol(s, id->attr[0], a);
  } else {
    if (a->sType == Variable) {
      _NotifyRedefinition(id->line, id->attr[0], a->sType, a->aa.f->defLoc);
      return NULL;
    }

    if (a->aa.f != NULL) {
      _NotifyRedefinition(id->line, id->attr[0], a->sType, a->aa.f->defLoc);
      return NULL;
    }

    // check function type
    if (!AtomEqual(t, a->type)) {
      _NotifyTypeConflict(id->line, id->attr[0], t, a->type, a->declLoc);
      return NULL;
    }
  }
  return a;
}

static void _AddNewLayer() {
  CurrentSymbolTable->next = _NewDummyLayer(CurrentSymbolTable);
  CurrentSymbolTable = CurrentSymbolTable->next;
  _PauseForDisplay();
}

static void _BackToPrevScope() {
  CurrentSymbolTable = CurrentSymbolTable->prev;
  Scope *dummy = CurrentSymbolTable->next;
  CurrentSymbolTable->next = dummy->peer;
  FREE(dummy);
}

// static void _GoDownAndCheck(ASTNode *n) {}
static void _HandleDeclList(ASTNode *n);
static void _HandleStmList(ASTNode *n);

static void _HandleCompoundStm(ASTNode *n) {
  if (n == NULL) {
    return;
  }
  _HandleDeclList(n->attr[0]);
  _AddNewLayer();
  _HandleStmList(n->attr[1]);
  _BackToPrevScope();
}

static void _HandleSelectionStm(ASTNode *n) {
  if (n == NULL) {
    return;
  }
  // handle expression
  _AddPeerScope(Simple, "if");
  // if
  _HandleCompoundStm(n->attr[1]);
  // else
  ASTNode *p = (ASTNode *)(n->attr[2]);
  if (p == NULL) {
    return;
  }

  if (p->nType == CompoundStm) {
    _AddPeerScope(Simple, "else");
    _HandleCompoundStm(n->attr[2]);
  } else if (p->nType == SelectionStm) {
    _HandleSelectionStm(p);
  } else {
    RAISE(UnexpectedNodeType);
  }
}

static void _HandleStmList(ASTNode *n) {
  if (n == NULL) {
    return;
  }
  _HandleStmList(n->attr[0]);
  ASTNode *p = (ASTNode *)(n->attr[1]);
  if (p->nType == CompoundStm) {
    _AddPeerScope(Simple, "Compound Statement");
    _HandleCompoundStm(p);
  } else if (p->nType == LoopStm) {
    // handle expressions
    _AddPeerScope(LoopBody, "Loop Statement");
    _HandleCompoundStm(p->attr[3]);
  } else if (p->nType == SelectionStm) {
    _HandleSelectionStm(p);
  } else if (p->nType == JumpStm) {
    if (strncmp(p->attr[0], "continue", 8) == 0) {
      if (CurrentSymbolTable->prev->sType != LoopBody) {
        _NotifyInvalidLocOfJumpStm(p->line, "continue", "loop body");
      }
    } else if (strncmp(p->attr[0], "break", 5) == 0) {
      if (CurrentSymbolTable->prev->sType != LoopBody) {
        _NotifyInvalidLocOfJumpStm(p->line, "break", "loop body");
      }
    } else if (strncmp(p->attr[0], "return", 6) == 0) {
      Scope *s = CurrentSymbolTable;
      while (s != NULL && s->sType != FuncBody) {
        s = s->prev;
      }
      if (s == NULL) {
        RAISE(Unreachable);
      }
      struct table_t *t = GlobalSymbolTable->curTab;
      Attribute *a = TableGet(t, s->name);
      const char *rt = a->aa.f->returnType;
      _Bool needReturn = strncmp(rt, "void", 4) != 0;

      if ((needReturn && p->attr[1] == NULL) || (!needReturn && p->attr[1] != NULL)) {
        _NotifyWrongReturnStm(p->line, s->name, needReturn);
      }
      if (p->attr[1] != NULL) {
        // _CheckExpressionType();
        a->aa.f->hasReturnValue = true;
      }
    } else {
      RAISE(Unreachable);
    }
  } else if (p->nType == IOStm) {
  } else if (p->nType == ExpressionStm) {
  } else {
    RAISE(UnexpectedNodeType);
  }
}

static void _HandleDeclarator(ASTNode *n, Scope *s) {
  ASTNode *t = n->attr[0];
  ASTNode *id = n->attr[1];
  Attribute *a = _NewAttribute(Variable, t->attr[0], s->stkTop, id->line);
  // _AddSymbolToCurScope(id->attr[0], a);
  _AddSymbol(s, id->attr[0], a);
}

static void _HandleDeclaratorList(ASTNode *n, Scope *s) {
  if (n == NULL) {
    return;
  }
  _HandleDeclaratorList(n->attr[0], s);
  _HandleDeclarator(n->attr[1], s);
}

static void _HandleDeclList(ASTNode *n) {
  if (n == NULL) {
    return;
  }
  _HandleDeclList(n->attr[0]);
  // Declaration Node is useless here.
  // Specifying types is handled in the AST.
  _HandleDeclaratorList(((ASTNode *)(n->attr[1]))->attr[1], CurrentSymbolTable);
}

static const char *_GernerateParaTypeList(ASTNode *n) {
  if (n == NULL) {
    return NULL;
  }
  const char *p = _GernerateParaTypeList(n->attr[0]);
  const char *t;
  ASTNode *d = (ASTNode *)(n->attr[1]);

  if (n->nType == ParameterTypeList) {
    t = d->attr[0];
  } else if (n->nType == ParameterDeclList) {
    t = ((ASTNode *)(d->attr[0]))->attr[0];
  }

  if (p == NULL) {
    return t;
  }
  return AtomConcatenate(p, ",", t, NULL);
}

static const char *_SpecifyFuncType(ASTNode *st, ASTNode *p) {
  const char *t;
  if (p != NULL) {
    t = AtomConcatenate(st->attr[0], "(", _GernerateParaTypeList(p), ")", NULL);
  } else {
    t = AtomAppend(st->attr[0], "(void)");
  }
  return t;
}

static int _GetFuncParaCount(ASTNode *n) {
  if (n == NULL) {
    return 0;
  }
  return 1 + _GetFuncParaCount(n->attr[0]);
}

static void _FillFuncDefParaType(ASTNode *n, const char *ptl[], int i) {
  if (n == NULL) {
    return;
  }
  _FillFuncDefParaType(n->attr[0], ptl, i - 1);
  ASTNode *p = (ASTNode *)(n->attr[1]);
  ptl[i] = ((ASTNode *)(p->attr[0]))->attr[0];
}

static void _HandleGlobalList(ASTNode *n) {
  if (n == NULL) {
    return;
  }
  _HandleGlobalList(n->attr[0]);

  ASTNode *p = (ASTNode *)(n->attr[1]);
  if (p->nType == Declaration) {
    // insert and check
    _HandleDeclaratorList(p->attr[1], GlobalSymbolTable);
  } else if (p->nType == FunctionDecl) {
    // insert and check
    const char *t = _SpecifyFuncType(p->attr[0], p->attr[2]);
    ASTNode *id = p->attr[1];
    Attribute *a = _NewAttribute(Function, t, 0, id->line);
    _AddSymbol(GlobalSymbolTable, id->attr[0], a);
  } else if (p->nType == FunctionDef) {
    // insert and check
    ASTNode *rt = (ASTNode *)(p->attr[0]);
    ASTNode *id = p->attr[1];
    ASTNode *pl = p->attr[2];
    const char *t = _SpecifyFuncType(rt, pl);
    // Attribute *a = _NewAttribute(Function, t, 0, -1);

    Attribute *a = _CheckFuncDef(id, t);
    if (a != NULL) {
      int paraNum = _GetFuncParaCount(pl);
      a->aa.f = _NewFuncDefAttr(id->line, rt->attr[0], paraNum);
      _FillFuncDefParaType(pl, a->aa.f->paraTypeList, paraNum - 1);

      if (strncmp(id->attr[0], "main", 4) == 0) {
        a->aa.f->isMain = true;
      }

      _AddPeerScope(FuncBody, id->attr[0]);
      _HandleDeclaratorList(pl, CurrentSymbolTable);
      // parameter declarator list is also a declarator list...LOL
      _HandleCompoundStm(p->attr[3]);

      _Bool needReturn = strncmp(rt->attr[0], "void", 4) != 0;

      if (needReturn && !a->aa.f->hasReturnValue) {
        _NotifyWrongReturnStm(p->line, id->attr[0], needReturn);
      }
    }
  } else {
    RAISE(UnexpectedNodeType);
  }
}

SymbolTable SymbolTableCreateFromAST(AST *ast) {
  _SymbolTableInit();
  _AddNewLayer();
  _HandleGlobalList(ast->root);
  _BackToPrevScope();
  return GlobalSymbolTable;
}

static const char *SymbolTableHeaders[] = {
    "Identifier", "Type", "Specified Type", "Offset", "Declaration Location", NULL,
};
static const char *FuncDefDetailHeaders[] = {
    "Function Name", "Definition Location", "Parameter Number", "Main Function?", "Return Type", "Parameter Type List", NULL,
};

static void _DisplayTableHeaders(Fmt *fmt, const char *p[]) {
  fprintf(fmt->out, "%s", *p++);
  while (*p != NULL) {
    fprintf(fmt->out, ";%s", *p++);
  }
  fputc('\n', fmt->out);
}
static void _DisplayFuncDefDetail(Fmt *fmt) {
  void **arr = TableToArray(GlobalSymbolTable->curTab, NULL);
  int i = 0;
  Attribute *a;
  FuncDefAttr *f;
  fprintf(fmt->out, "Function Definition Detail:\n");
  _DisplayTableHeaders(fmt, FuncDefDetailHeaders);
  while (arr[i] != NULL) {
    a = ((Attribute *)(arr[i + 1]));
    f = a->aa.f;
    if (f != NULL) {
      fprintf(fmt->out, "%s;%d;%d;%s;%s;", arr[i], f->defLoc, f->paraNum, f->isMain ? "True" : "False", f->returnType);
      if (f->paraNum > 0) {
        for (int j = 0; j < f->paraNum; ++j) {
          // fprintf(fmt->out, "[%d]%s ", j + 1, f->paraTypeList[j]);
          fprintf(fmt->out, "%s ", f->paraTypeList[j]);
        }
        fputc('\n', fmt->out);
      } else {
        fprintf(fmt->out, "void\n");
      }
    }
    i += 2;
  }
  FREE(arr);
  putc('\n', fmt->out);
}

static void _DisplaySymbolTable(struct table_t *t, Fmt *fmt) {
  if (t == NULL) {
    fprintf(fmt->out, "empty\n\n");
    return;
  }
  void **arr = TableToArray(t, NULL);
  int i = 0;
  Attribute *a;
  _DisplayTableHeaders(fmt, SymbolTableHeaders);
  while (arr[i] != NULL) {
    a = ((Attribute *)(arr[i + 1]));
    fprintf(fmt->out, "%s;%s;%s;%d;%d\n", (const char *)(arr[i]), SymbolTypeStrs[a->sType], a->type, a->address, a->declLoc);
    i += 2;
  }
  FREE(arr);
  putc('\n', fmt->out);
}

static void _DisplaySymbolTableTree(SymbolTable st, Fmt *fmt) {
  if (st == NULL) {
    return;
  }
  // display peer;
  while (st != NULL) {
    if (st->id == -1) {  // skip dummy head
      st = st->peer;
      continue;
    }
    fprintf(fmt->out, "%s: scope %d, level %d", st->name, st->id, st->level);
    if (st->prev == NULL) {
      fputc('\n', fmt->out);
    } else {
      fprintf(fmt->out, ", parent scope %d: \n", st->prev->id);
    }
    _DisplaySymbolTable(st->curTab, fmt);
    _DisplaySymbolTableTree(st->next, fmt);
    st = st->peer;
  }
}

static void _BeautifyST(Fmt *fmt) {
  static const char *BeautifyST_py = "./bin/BeautifyST.py";
  char buffer[128];
  memset(buffer, 0, sizeof(buffer));
  sprintf(buffer, "%s %s", BeautifyST_py, fmt->fileLoc);
  system(buffer);
}

void DisplaySymbolTable(SymbolTable st, Fmt *fmt) {
  fmt->out = fopen(fmt->fileLoc, "w");
  if (fmt->out == NULL) {
    RAISE(OutFileOpenErr);
  }
  _DisplaySymbolTableTree(st, fmt);
  _DisplayFuncDefDetail(fmt);
  fclose(fmt->out);
  _BeautifyST(fmt);
}

void FreeSymbolTable(SymbolTable st) {
  if (st == NULL) {
    return;
  }
  while (st != NULL) {
    if (st->curTab != NULL) {
      TableFree(&(st->curTab));
    }
    FreeSymbolTable(st->next);
    st = st->peer;
  }
}