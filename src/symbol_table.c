/*
  Symbol Table is designed in a harry.
  So the interfaces defined here are all bullshits.
*/

#include "symbol_table.h"

#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

#include "../lib/llsc.h"
#include "display.h"
#include "exception.h"
#include "limit.h"
#include "stdbool.h"
#include "symbol_table.h"

static const char *ReservedSymbolList[] = {
    "void", "i32", "f32", "string", "bool", "if", "else", "for", "return", "break", "continue", "print", "scan", "+", "-", "++", "--", "~", "!", "*", "/", "%",  "<",
    ">",    "<=",  ">=",  "==",     "!=",   "<<", ">>",   "&",   "|",      "^",     "&&",       "||",    "=",    ",", "(", ")",  "[",  "]", "{", "}", ";", NULL,
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