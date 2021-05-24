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
#include "stdbool.h"
#include "symbol_table.h"

static const char *ReservedSymbolList[] = {
    "void", "i32", "f32", "string", "bool", "if", "else", "for", "return", "break", "continue", "print", "scan", "+", "-", "++", "--", "~", "!", "*", "/", "%",  "<",
    ">",    "<=",  ">=",  "==",     "!=",   "<<", ">>",   "&",   "|",      "^",     "&&",       "||",    "=",    ",", "(", ")",  "[",  "]", "{", "}", ";", NULL,
};

typedef enum { VOID, I32, F32, STRING, BOOL } BaseType;
static const char *BaseTypeStrs[] = {NULL, NULL, NULL, NULL, NULL};

void AtomInit() {
  AtomLoad(ReservedSymbolList);
  // register
  BaseTypeStrs[VOID] = AtomString("void");
  BaseTypeStrs[I32] = AtomString("i32");
  BaseTypeStrs[F32] = AtomString("f32");
  BaseTypeStrs[STRING] = AtomString("string");
  BaseTypeStrs[BOOL] = AtomString("bool");
}

SymbolTable GlobalSymbolTable = NULL;
SymbolTable CurrentSymbolTable = NULL;
static int DefaultTableSize = 32;
static int CurID = 0;
static const int MAX_ARRAY_DIM = 8;
static char InnerStrBuffer[128];
static int InnerBuffer[MAX_ARRAY_DIM];

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

static FuncAttr *_NewFuncAttr(int defLoc, const char *rt, int paraNum) {
  int size = sizeof(FuncAttr) + sizeof(const char *) * paraNum;
  FuncAttr *a = ArenaAllocFor(size);
  memset(a, 0, size);
  a->defLoc = defLoc;
  a->returnType = rt;
  a->paraNum = paraNum;
  return a;
}

static VarAttr *_NewVarDeclAttr(void *initializer, int arrDimNum, int *arrDim) {
  int size = sizeof(VarAttr) + sizeof(int) * arrDimNum;
  VarAttr *a = ArenaAllocFor(size);
  a->initializer = initializer;
  a->arrDimNum = arrDimNum;
  memcpy(a->arrDim, arrDim, sizeof(int) * arrDimNum);
  return a;
}

static ExprAttr *_NewExprAttr(const char *type, _Bool assignable, int dim) {
  ExprAttr *a = ALLOC(sizeof(ExprAttr));
  a->type = type;
  a->isLvalue = assignable;
  a->dim = dim;
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
    TablePut(s->curTab, id, attr);
    _PauseForDisplay();
  } else {
    _NotifyRepetition(a, attr, id);
  }
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

    if (a->aa.f->defLoc != -1) {
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

static ExprAttr *_CheckExpressionType(ASTNode *n);

static Attribute *_LocateIdentifier(const char *id) {
  Scope *s = CurrentSymbolTable;
  Attribute *a = NULL;
  while (s != NULL) {
    if (s->curTab != NULL) {
      a = TableGet(s->curTab, id);
    }
    if (a != NULL) {
      break;
    }
    s = s->prev;
  }
  return a;
}

static _Bool _CheckFuncParaList(ASTNode *n, FuncAttr *fa, const char *id, int line);

static ExprAttr *_CheckFuncCall(ASTNode *n) {
  ASTNode *p = n->attr[0];
  Attribute *a = _LocateIdentifier(p->attr[0]);
  if (a == NULL) {
    _NotifyUndefinedReference(n->line, p->attr[0]);
    return NULL;
  }
  if (a->sType == Variable) {
    _NotifyUncallable(n->line, p->attr[0], a->type);
    return NULL;
  }
  FuncAttr *fa = a->aa.f;
  if (_CheckFuncParaList(n->attr[1], fa, p->attr[0], n->line)) {
    return _NewExprAttr(fa->returnType, false, 0);
  }
  return NULL;
}

static ExprAttr *_CheckBinaryExpr(ASTNode *n) {
  ASTNode *l = n->attr[1];
  ASTNode *r = n->attr[2];
  ExprAttr *lhs = _CheckExpressionType(l);
  if (lhs == NULL) {
    return NULL;
  }
  ExprAttr *rhs = _CheckExpressionType(r);
  if (rhs == NULL) {
    FREE(lhs);
    return NULL;
  }
  const char *op = n->attr[0];
  if (op == AtomString(",")) {  // no restriction
    FREE(lhs);
    return rhs;
  }
  // in other binary expression, operands must have the same type
  if (lhs->type != rhs->type) {
    _NotifyTypeUnmatch(n->line, lhs->type, rhs->type, op);
    FREE(lhs);
    FREE(rhs);
    return NULL;
  }
  // assignment's lhs must be lvalue.
  if (op == AtomString("=")) {
    if (!lhs->isLvalue) {
      _NotifyUnassignable(l->line);
      FREE(lhs);
      FREE(rhs);
      return NULL;
    }
    if (lhs->dim != 0) {
      _NotifyAssignmentBetweenArray(n->line);
      FREE(lhs);
      FREE(rhs);
      return NULL;
    }
    FREE(lhs);
    return rhs;
  }
  // in other binary expression, operands must not be string
  if (lhs->type == BaseTypeStrs[STRING]) {
    _NotifyInvalidArgumentType(l->line, lhs->type, "binary expression", op);
    FREE(lhs);
    FREE(rhs);
    return NULL;
  }
  if (rhs->type == BaseTypeStrs[STRING]) {
    _NotifyInvalidArgumentType(r->line, rhs->type, "binary expression", op);
    FREE(lhs);
    FREE(rhs);
    return NULL;
  }
  // return bool
  if (op == AtomString("||") || op == AtomString("&&") || op == AtomString("==") || op == AtomString("!=") || op == AtomString("<") || op == AtomString(">") || op == AtomString("<=") ||
      op == AtomString(">=")) {
    FREE(lhs);
    FREE(rhs);
    return _NewExprAttr(BaseTypeStrs[BOOL], false, 0);
  }
  // must be i32
  if (op == AtomString("&") || op == AtomString("|") || op == AtomString("^") || op == AtomString("%")) {
    if (lhs->type != BaseTypeStrs[I32]) {
      FREE(lhs);
      FREE(rhs);
      return NULL;
    }
    if (rhs->type != BaseTypeStrs[I32]) {
      FREE(lhs);
      FREE(rhs);
      return NULL;
    }
    FREE(lhs);
    FREE(rhs);
    return _NewExprAttr(BaseTypeStrs[I32], false, 0);
  }
  if (op == AtomString("+") || op == AtomString("-") || op == AtomString("*") || op == AtomString("/")) {
    // no limit
    const char *t = lhs->type;
    FREE(lhs);
    FREE(rhs);
    return _NewExprAttr(t, false, 0);
  }
  // unreachable
  RAISE(Unreachable);
  return NULL;
}

static const char *_DereferenceArray(const char *t) {
  static char InnerBuffer[128];
  memset(InnerBuffer, 0, sizeof(InnerBuffer));
  const char *p = t;
  while (*p != '[' && *p != '\0') {
    p++;
  }
  if (*p == '\0') {
    RAISE(Unreachable);
  }
  int len = p - t;
  strncpy(InnerBuffer, t, len);
  const char *q = p;
  while (*q != ']' && *q != '\0') {
    q++;
  }
  strcpy(InnerBuffer + len, q + 1);
  return AtomString(InnerBuffer);
}

static ExprAttr *_CheckPostfixExprType(ASTNode *n) {
  ExprAttr *idx = _CheckExpressionType(n->attr[2]);
  if (idx == NULL) {
    return NULL;
  }
  ExprAttr *arr = NULL;
  ASTNode *p = n->attr[1];
  if (p->nType == PostfixExpr) {
    arr = _CheckPostfixExprType(p);
  } else {
    arr = _CheckExpressionType(p);
  }
  if (arr == NULL) {
    FREE(idx);
    return NULL;
  }
  if (arr->dim <= 0) {
    _NotifyUnsubscriptable(p->line);
    FREE(idx);
    FREE(arr);
    return NULL;
  }
  if (idx->type != BaseTypeStrs[I32]) {
    _NotifyNonIntegerSubscript(p->line);
    FREE(idx);
    FREE(arr);
    return NULL;
  }
  arr->dim--;
  arr->isLvalue = true;
  arr->type = _DereferenceArray(arr->type);
  FREE(idx);
  return arr;
}

static ExprAttr *_CheckUnaryExprType(ASTNode *n) {
  ExprAttr *a = _CheckExpressionType(n->attr[1]);
  if (a == NULL) {
    return NULL;
  }
  const char *t = a->type;
  const char *op = n->attr[0];
  if (op == AtomString("!")) {
    if (t == BaseTypeStrs[STRING]) {
      _NotifyInvalidArgumentType(n->line, t, "unary expression", "!");
      FREE(a);
      return NULL;
    }
    a->type = BaseTypeStrs[BOOL];
    a->isLvalue = false;
  } else if (op == AtomString("~")) {
    if (t != BaseTypeStrs[I32]) {
      _NotifyInvalidArgumentType(n->line, t, "unary expression", "~");
      FREE(a);
      return NULL;
    }
    a->isLvalue = false;
  } else if (op == AtomString("+") || op == AtomString("-")) {
    if (t == BaseTypeStrs[BOOL] || t == BaseTypeStrs[STRING]) {
      _NotifyInvalidArgumentType(n->line, t, "unary expression", "+/-");
      FREE(a);
      return NULL;
    }
    a->isLvalue = false;
  } else if (op == AtomString("--") || op == AtomString("++")) {
    if (!a->isLvalue) {
      _NotifyUnassignable(n->line);
      FREE(a);
      return NULL;
    }
    if (t != BaseTypeStrs[I32]) {
      _NotifyInvalidArgumentType(n->line, t, "unary expression", "~");
      FREE(a);
      return NULL;
    }
    a->isLvalue = false;
  } else {
    RAISE(Unreachable);
  }
  return a;
}

static ExprAttr *_CheckExpressionType(ASTNode *n) {
  if (n == NULL) {
    return NULL;
  }
  if (n->nType == BinaryExpr) {
    return _CheckBinaryExpr(n);
  } else if (n->nType == PostfixExpr) {
    return _CheckPostfixExprType(n);
  } else if (n->nType == FunctionCall) {
    return _CheckFuncCall(n);
  } else if (n->nType == UnaryExpr) {
    return _CheckUnaryExprType(n);
  } else if (n->nType == Identifier) {
    // find in the current and all previous scopes
    Attribute *a = _LocateIdentifier(n->attr[0]);
    if (a == NULL) {
      _NotifyUndefinedReference(n->line, n->attr[0]);
      return NULL;
    }
    int dim = 0;
    if (a->sType == Variable) {
      dim = a->aa.v->arrDimNum;
    }
    return _NewExprAttr(a->type, dim == 0, dim);
  } else if (n->nType == StrConst) {
    return _NewExprAttr(BaseTypeStrs[STRING], false, 0);
  } else if (n->nType == FloatConst) {
    return _NewExprAttr(BaseTypeStrs[F32], false, 0);
  } else if (n->nType == IntConst) {
    return _NewExprAttr(BaseTypeStrs[I32], false, 0);
  } else if (n->nType == BoolConst) {
    return _NewExprAttr(BaseTypeStrs[BOOL], false, 0);
  } else {
    RAISE(Unreachable);
  }
  return NULL;
}

static _Bool _CheckFuncParaList(ASTNode *n, FuncAttr *fa, const char *id, int line) {
  ASTNode *p = n;
  int i = fa->paraNum - 1;
  _Bool match = true;
  while (p != NULL && i >= 0) {
    ExprAttr *a = _CheckExpressionType(p->attr[1]);
    const char *t = NULL;
    if (a != NULL) {
      t = a->type;
      FREE(a);
    }
    if (t != fa->paraTypeList[i]) {
      _NotifyFuncCallUnmatch(line, fa->paraTypeList[i], t, i + 1);
      match = false;
    }
    i--;
    p = p->attr[0];
  }
  if (p != NULL) {
    while (p != NULL) {
      i--;
      p = p->attr[0];
    }
    _NotifyParaNumberUnmatch(line, id, fa->paraNum, fa->paraNum - i - 1);
    return false;
  }
  if (i + 1 != 0) {
    _NotifyParaNumberUnmatch(line, id, fa->paraNum, fa->paraNum - i - 1);
    return false;
  }
  return match;
}

static _Bool _IsBaseType(const char *t) {
  for (BaseType i = I32; i <= BOOL; ++i) {
    if (t == BaseTypeStrs[i]) {
      return true;
    }
  }
  return false;
}

static void _CheckIOArgList(ASTNode *n, int line) {
  ASTNode *p = n;
  while (p != NULL) {
    ExprAttr *a = _CheckExpressionType(p->attr[1]);
    if (a != NULL) {
      if (!_IsBaseType(a->type)) {
        _NotifyIOStmMustGetBaseType(line, a->type);
      }
      FREE(a);
    }
    p = p->attr[0];
  }
}

static _Bool _CheckInitializerList(ASTNode *n, const char *t, int maxDim, int curDim, int cnt, int line);
static _Bool _CheckInitializer(ASTNode *n, const char *t, int maxDim, int curDim) {
  // Before this function is called, InnerBuffer will get the dimensions of Array.
  if (n->nType == Initializer) {
    if (maxDim > curDim) {
      _NotifyExpectArrayInitializer(n->line);
      return false;
    }
    ExprAttr *ea = _CheckExpressionType(n->attr[0]);
    if (ea != NULL) {
      if (ea->type != t) {
        _NotifyTypeUnmatchInitializer(n->line, t, ea->type);
        FREE(ea);
        return false;
      }
      FREE(ea);
      return true;
    } else {
      return false;
    }
  } else if (n->nType == ArrayInitializer) {
    if (maxDim <= curDim) {
      _NotifyArrayInitializerOnBaseType(n->line);
      return false;
    }
    return _CheckInitializerList(n->attr[0], t, maxDim, curDim, 0, n->line);
  } else {
    RAISE(UnknownNodeType);
  }
  return true;
}

static _Bool _CheckInitializerList(ASTNode *n, const char *t, int maxDim, int curDim, int cnt, int line) {
  if (n == NULL) {
    if (cnt != InnerBuffer[curDim]) {
      _NotifyArrayInitializerDimUnmatch(line, InnerBuffer[curDim], cnt);
      return false;
    }
    return true;
  }
  if (!_CheckInitializerList(n->attr[0], t, maxDim, curDim, cnt + 1, line)) {
    return false;
  }
  if (!_CheckInitializer(n->attr[1], t, maxDim, curDim + 1)) {
    return false;
  }
  return true;
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
  // handle expression

  ExprAttr *a = _CheckExpressionType(n->attr[0]);
  if (a != NULL) {
    if (a->type != BaseTypeStrs[BOOL]) {
      _NotifyConditionExprNeedBoolType(((ASTNode *)(n->attr[0]))->line);
    }
    FREE(a);
  }

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
static void _HandleLoopStm(ASTNode *n) {
  // handle expressions
  ASTNode *init = n->attr[0];  // Expr Stm
  ASTNode *cond = n->attr[1];  // Expr Stm
  ASTNode *inc = n->attr[2];   // Expr
  ExprAttr *a = NULL;
  a = _CheckExpressionType(init->attr[0]);
  if (a != NULL) {
    FREE(a);
  }
  a = _CheckExpressionType(cond->attr[0]);
  if (a != NULL) {
    if (a->type != BaseTypeStrs[BOOL]) {
      _NotifyConditionExprNeedBoolType(cond->line);
    }
    FREE(a);
  }
  a = _CheckExpressionType(inc);
  if (a != NULL) {
    FREE(a);
  }

  // _CheckExpressionType();
  _AddPeerScope(LoopBody, "Loop Statement");
  _HandleCompoundStm(n->attr[3]);
}

static void _HandleReturnStm(ASTNode *n) {
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
  _Bool needReturn = rt != BaseTypeStrs[VOID];

  if ((needReturn && n->attr[1] == NULL) || (!needReturn && n->attr[1] != NULL)) {
    _NotifyWrongReturnStm(n->line, s->name, needReturn);
  }
  if (n->attr[1] != NULL) {
    ExprAttr *ea = _CheckExpressionType(n->attr[1]);
    if (ea != NULL) {
      if (a->aa.f->returnType != ea->type) {
        _NotifyReturnTypeUnmatch(n->line, a->aa.f->returnType, ea->type, s->name);
      }
      FREE(ea);
    }
    a->aa.f->hasReturnValue = true;
  }
}

static void _HandleStm(ASTNode *n) {
  if (n->nType == CompoundStm) {
    _AddPeerScope(Simple, "Compound Statement");
    _HandleCompoundStm(n);
  } else if (n->nType == LoopStm) {
    _HandleLoopStm(n);
  } else if (n->nType == SelectionStm) {
    _HandleSelectionStm(n);
  } else if (n->nType == JumpStm) {
    if (strncmp(n->attr[0], "continue", 8) == 0) {
      if (CurrentSymbolTable->prev->sType != LoopBody) {
        _NotifyInvalidLocOfJumpStm(n->line, "continue", "loop body");
      }
    } else if (strncmp(n->attr[0], "break", 5) == 0) {
      if (CurrentSymbolTable->prev->sType != LoopBody) {
        _NotifyInvalidLocOfJumpStm(n->line, "break", "loop body");
      }
    } else if (strncmp(n->attr[0], "return", 6) == 0) {
      _HandleReturnStm(n);
    } else {
      RAISE(Unreachable);
    }
  } else if (n->nType == IOStm) {
    _CheckIOArgList(n->attr[1], n->line);
  } else if (n->nType == ExpressionStm) {
    ExprAttr *a = _CheckExpressionType(n->attr[0]);
    if (a != NULL) {
      FREE(a);
    }
  } else {
    RAISE(UnexpectedNodeType);
  }
}

static void _HandleStmList(ASTNode *n) {
  if (n == NULL) {
    return;
  }
  _HandleStmList(n->attr[0]);
  _HandleStm(n->attr[1]);
}

static const char *_GetBaseType(ASTNode *n, const char *id) {
  const char *type = n->attr[0];
  if (strncmp(type, "bool", 4) == 0) {
    return AtomString("bool");
  } else if (strncmp(type, "i32", 3) == 0) {
    return AtomString("i32");
  } else if (strncmp(type, "f32", 3) == 0) {
    return AtomString("f32");
  } else if (strncmp(type, "string", 5) == 0) {
    return AtomString("string");
  } else if (strncmp(type, "void", 4) == 0) {
    _NotifyInvalidTypeOfVar(n->line, id, "void");
    return NULL;
  } else {
    RAISE(Unreachable);
  }
  return NULL;
}

// return the dimension
// InnerBuffer will hold the details.
static int _GetArrayDimList(const char *type, int curLine) {
  const char *p = type;
  int *buffer = InnerBuffer;
  int dim = 0;
  while (*p != '\0') {
    if (*p == '[') {
      const char *q = strchr(p, ']');
      int len = q - p - 1;
      strncpy(InnerStrBuffer, p + 1, len);
      InnerStrBuffer[len] = '\0';
      int curDim = atoi(InnerStrBuffer);
      if (curDim <= 0) {
        _NotifyInvalidArrayDim(curLine);
        return -1;
      }
      *buffer++ = curDim;
      p = q + 1;
      dim++;
    } else {
      p++;
    }
  }
  return dim;
}

// The backend VM will be constructed by C.
// So return the corresponding size.
static int _GetBaseTypeSize(const char *type) {
  if (type == BaseTypeStrs[BOOL]) {
    return sizeof(_Bool);
  } else if (type == BaseTypeStrs[I32]) {
    return sizeof(int32_t);
  } else if (type == BaseTypeStrs[F32]) {
    return sizeof(float);
  } else if (type == BaseTypeStrs[STRING]) {
    return sizeof(const char *);
  } else {
    RAISE(Unreachable);
  }
  return -1;
}

static void _HandleDeclarator(ASTNode *n, Scope *s) {
  ASTNode *t = n->attr[0];
  ASTNode *id = n->attr[1];
  // Get base type
  const char *bt = _GetBaseType(t, id->attr[0]);
  if (bt == NULL) {  // void ..invalid
    return;
  }
  // get array dim
  int dim = _GetArrayDimList(t->attr[0], n->line);
  if (dim > MAX_ARRAY_DIM) {  // too big
    _NotifyArrayDimTooBig(n->line, id->attr[0], dim, MAX_ARRAY_DIM);
    return;
  }
  // calculate variable size
  int varSize = _GetBaseTypeSize(bt);
  for (int i = 0; i < dim; ++i) {
    varSize *= InnerBuffer[i];
  }
  Attribute *a = _NewAttribute(Variable, t->attr[0], s->stkTop, id->line);
  s->stkTop += varSize;
  // check initializer
  if (n->attr[2] != NULL && !_CheckInitializer(n->attr[2], bt, dim, 0)) {
    a->aa.v = _NewVarDeclAttr(NULL, dim, InnerBuffer);
  } else {
    a->aa.v = _NewVarDeclAttr(n->attr[2], dim, InnerBuffer);
  }
  // insert into symbol table
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

static void _FillFuncParaType(ASTNode *n, const char *ptl[], int i) {
  if (n == NULL) {
    return;
  }
  _FillFuncParaType(n->attr[0], ptl, i - 1);
  ASTNode *p = (ASTNode *)(n->attr[1]);
  if (p->nType == Declarator) {
    ptl[i] = ((ASTNode *)(p->attr[0]))->attr[0];
  } else if (p->nType == TypeSpecifier) {
    ptl[i] = p->attr[0];
  } else {
    RAISE(UnknownNodeType);
  }
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
    ASTNode *rt = p->attr[0];
    ASTNode *id = p->attr[1];
    ASTNode *pl = p->attr[2];
    const char *t = _SpecifyFuncType(rt, pl);
    Attribute *a = _NewAttribute(Function, t, 0, id->line);

    int paraNum = _GetFuncParaCount(pl);
    a->aa.f = _NewFuncAttr(-1, rt->attr[0], paraNum);
    _FillFuncParaType(pl, a->aa.f->paraTypeList, paraNum - 1);

    _AddSymbol(GlobalSymbolTable, id->attr[0], a);
  } else if (p->nType == FunctionDef) {
    // insert and check
    ASTNode *rt = p->attr[0];
    ASTNode *id = p->attr[1];
    ASTNode *pl = p->attr[2];
    const char *t = _SpecifyFuncType(rt, pl);
    Attribute *a = _CheckFuncDef(id, t);
    if (a != NULL) {
      int paraNum = _GetFuncParaCount(pl);
      if (a->aa.f == NULL) {
        a->aa.f = _NewFuncAttr(p->line, rt->attr[0], paraNum);
        _FillFuncParaType(pl, a->aa.f->paraTypeList, paraNum - 1);
      }

      a->aa.f->defLoc = p->line;
      if (strncmp(id->attr[0], "main", 4) == 0) {
        a->aa.f->isMain = true;
      }
      _AddPeerScope(FuncBody, id->attr[0]);
      _HandleDeclaratorList(pl, CurrentSymbolTable);
      // parameter declarator list is also a declarator list...LOL
      _HandleCompoundStm(p->attr[3]);
      _Bool needReturn = rt->attr[0] != BaseTypeStrs[VOID];
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