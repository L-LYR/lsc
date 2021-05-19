#include "symbol_table.h"
#include "../lib/llsc.h"
#include "exception.h"
#include "limit.h"
#include "stdbool.h"
#include "symbol_table.h"
#include <stdlib.h>
#include <string.h>

static const char *ReservedSymbolList[] = {
    "void",   "i32",   "f32",      "string", "bool", "if", "else", "for",
    "return", "break", "continue", "print",  "scan", "+",  "-",    "++",
    "--",     "~",     "!",        "*",      "/",    "%",  "<",    ">",
    "<=",     ">=",    "==",       "!=",     "<<",   ">>", "&",    "|",
    "^",      "&&",    "||",       "=",      ",",    "(",  ")",    "[",
    "]",      "{",     "}",        ";",      NULL,
};

void AtomInit() { AtomLoad(ReservedSymbolList); }

SymbolTable GlobalSymbolTable = NULL;
SymbolTable CurrentSymbolTable = NULL;
static int DefaultTableSize = 32;
static int CurID = 0;
static Scope *_NewScope(Scope *peer, Scope *prev, int level,
                        struct table_t *tab) {
  Scope *s = ArenaAllocFor(sizeof(Scope));
  s->id = CurID++;
  s->level = level;
  s->stkTop = 0;
  s->peer = peer;
  s->prev = prev;
  s->next = NULL;
  s->curTab = tab;
  return s;
}

static Attribute *_NewAttribute(const char *type, const char *init,
                                int32_t addr, int declLoc, int defLoc) {
  Attribute *a = ArenaAllocFor(sizeof(Attribute));
  a->type = type;
  a->init = init;
  a->address = addr;
  a->declLoc = declLoc;
  a->defLoc = defLoc;
  return a;
}

static Scope *_NewDummyLayer(Scope *prev) {
  Scope *s = ALLOC(sizeof(Scope));
  memset(s, 0, sizeof(Scope));
  s->prev = prev;
  s->level = prev->level + 1;
  return s;
}

static void _SymbolTableInit() {
  CurrentSymbolTable = GlobalSymbolTable = _NewScope(
      NULL, NULL, 0,
      TableCreate(DefaultTableSize, (equal_t)AtomEqual, (hash_t)AtomHash));
}

static void _AddPeerScope() {
  CurrentSymbolTable->peer = _NewScope(NULL, CurrentSymbolTable->prev,
                                       CurrentSymbolTable->level, NULL);
  CurrentSymbolTable = CurrentSymbolTable->peer;
}

static void _AddSymbol(struct table_t *t, const char *id, Attribute *attr) {
  if (TableGet(t, id) == NULL) {
    CurrentSymbolTable->stkTop += SizeOf(attr->type);
    TablePut(t, id, attr);
  } else {
    // error!
    // temporarily for unreachable
    TRY RAISE(Unreachable);
    EXCEPT(Unreachable)
    printf("?\n");
    END_TRY;
  }
}

static void _AddSymbolToCurScope(const char *id, Attribute *attr) {
  if (CurrentSymbolTable->curTab == NULL) {
    CurrentSymbolTable->curTab =
        TableCreate(DefaultTableSize, (equal_t)AtomEqual, (hash_t)AtomHash);
  }
  _AddSymbol(CurrentSymbolTable->curTab, id, attr);
}

static void _AddSymbolToPrevScope(const char *id, Attribute *attr) {
  _AddSymbol(CurrentSymbolTable->prev->curTab, id, attr);
}

static void _AddNewLayer() {
  CurrentSymbolTable->next = _NewDummyLayer(CurrentSymbolTable);
  CurrentSymbolTable = CurrentSymbolTable->next;
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
  _AddPeerScope();
  _HandleCompoundStm(n->attr[1]);
  ASTNode *p = (ASTNode *)(n->attr[2]);
  if (p == NULL) {
    return;
  }

  if (p->nType == CompoundStm) {
    _AddPeerScope();
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
    _AddPeerScope();
    _HandleCompoundStm(p);
  } else if (p->nType == LoopStm) {
    // handle expressions
    _AddPeerScope();
    _HandleCompoundStm(p->attr[3]);
  } else if (p->nType == SelectionStm) {
    _HandleSelectionStm(p);
  } else if (p->nType == JumpStm || p->nType == IOStm ||
             p->nType == ExpressionStm) {
    // hanle expression
  } else {
    RAISE(UnexpectedNodeType);
  }
}

static void _HandleDeclarator(ASTNode *n) {
  ASTNode *t = n->attr[0];
  ASTNode *id = n->attr[1];
  Attribute *a =
      _NewAttribute(t->attr[0], NULL, CurrentSymbolTable->stkTop, id->line, -1);
  _AddSymbolToCurScope(id->attr[0], a);
}

static void _HandleDeclaratorList(ASTNode *n) {
  if (n == NULL) {
    return;
  }
  _HandleDeclaratorList(n->attr[0]);
  _HandleDeclarator(n->attr[1]);
}

static void _HandleDeclaration(ASTNode *n) {
  if (n == NULL) {
    return;
  }
  _HandleDeclaratorList(n->attr[1]);
}

static void _HandleDeclList(ASTNode *n) {
  if (n == NULL) {
    return;
  }
  _HandleDeclList(n->attr[0]);
  _HandleDeclaration(n->attr[1]);
}

static const char *_HandleParaTypeList(ASTNode *n) {
  if (n == NULL) {
    return NULL;
  }
  const char *p = _HandleParaTypeList(n->attr[0]);
  const char *t = ((ASTNode *)(n->attr[1]))->attr[0];
  if (p == NULL) {
    return AtomAppend("(", t);
  }
  return AtomConcatenate(p, ",", t, NULL);
}

static const char *_HandleParaDeclList(ASTNode *n) {
  if (n == NULL) {
    return NULL;
  }
  const char *p = _HandleParaDeclList(n->attr[0]);
  ASTNode *d = (ASTNode *)(n->attr[1]);
  _HandleDeclarator(d);
  const char *t = ((ASTNode *)(d->attr[0]))->attr[0];
  if (p == NULL) {
    return AtomAppend("(", t);
  }
  return AtomConcatenate(p, ",", t, NULL);
}

static const char *_SpecifyFuncType(ASTNode *st, ASTNode *p) {
  const char *t;
  if (p != NULL) {
    const char *pl;
    if (p->nType == ParameterTypeList) {
      pl = _HandleParaTypeList(p);
    } else if (p->nType == ParameterDeclList) {
      pl = _HandleParaDeclList(p);
    }
    t = AtomConcatenate(st->attr[0], pl, ")", NULL);
  } else {
    t = AtomAppend(st->attr[0], "(void)");
  }
  return t;
}

static void _HandleGlobalList(ASTNode *n) {
  if (n == NULL) {
    return;
  }
  _HandleGlobalList(n->attr[0]);

  ASTNode *p = (ASTNode *)(n->attr[1]);
  if (p->nType == Declaration) {
    // insert and check
    // Here we must change the scope...
    SymbolTable tmp = CurrentSymbolTable;
    CurrentSymbolTable = GlobalSymbolTable;
    _HandleDeclaration(p);
    CurrentSymbolTable = tmp;
  } else if (p->nType == FunctionDecl) {
    // insert and check
    const char *t = _SpecifyFuncType(p->attr[0], p->attr[2]);
    ASTNode *id = p->attr[1];
    Attribute *a = _NewAttribute(t, NULL, 0, id->line, -1);
    _AddSymbolToPrevScope(id->attr[0], a);
  } else if (p->nType == FunctionDef) {
    // insert and check
    _AddPeerScope();
    const char *t = _SpecifyFuncType(p->attr[0], p->attr[2]);
    ASTNode *id = p->attr[1];
    Attribute *a = _NewAttribute(t, NULL, 0, -1, id->line);
    _AddSymbolToPrevScope(id->attr[0], a);
    _HandleCompoundStm(p->attr[3]);
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

static void _DisplayTable(struct table_t *t, Fmt *fmt) {
  if (t == NULL) {
    fprintf(fmt->out, "Empty Scope\n\n");
    return;
  }
  void **arr = TableToArray(t, NULL);
  int i = 0;
  Attribute *a;
  fprintf(fmt->out, "%s;%s;%s;%s;%s\n", "Identifier", "Specified Type",
          "Offset", "Declaration Location", "Definition Location");
  while (arr[i] != NULL) {
    a = ((Attribute *)(arr[i + 1]));
    fprintf(fmt->out, "%s;%s;%d;%d;%d\n", (const char *)(arr[i]), a->type,
            a->address, a->declLoc, a->defLoc);
    i += 2;
  }
  FREE(arr);
  putc('\n', fmt->out);
}

static void _DisplaySymbolTable(SymbolTable st, Fmt *fmt) {
  if (st == NULL) {
    return;
  }
  // display peer;
  while (st != NULL) {
    fprintf(fmt->out, "Scope %d, Level %d, ", st->id, st->level);
    if (st->prev == NULL) {
      fprintf(fmt->out, "Top Scope: \n");
    } else {
      fprintf(fmt->out, "Parent Scope %d: \n", st->prev->id);
    }
    _DisplayTable(st->curTab, fmt);
    _DisplaySymbolTable(st->next, fmt);
    st = st->peer;
  }
}

static const char *BeautifyST_py = "./bin/BeautifyST.py";
static void _BeautifyST(Fmt *fmt) {
  char buffer[128];
  memset(buffer, 0, sizeof(buffer));
  sprintf(buffer, "%s %s", BeautifyST_py, fmt->fileLoc);
  system(buffer);
}

void DisplaySymbolTable(SymbolTable st, Fmt *fmt) {
  _DisplaySymbolTable(st, fmt);
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