#include "generate_code.h"

#include <bits/stdint-intn.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../exception/exception.h"
#include "../lib/llsc.h"
#include "ast.h"
#include "symbol_table.h"
#include "to_str.h"

extern const char* BaseTypeStrs[];  // symbol_table.c

static IR InnerIR;
static Scope* CurrentScope;
static Scope* GlobalScope;

static struct stack_t* ContinueInsStk;
static struct stack_t* BreakInsStk;

static const int DefaultIncNum = 64;
static void _AppendIns() {
  if (InnerIR.curInsIdx >= InnerIR.maxInsCnt) {
    InnerIR.maxInsCnt += DefaultIncNum;
    RESIZE(InnerIR.ins, InnerIR.maxInsCnt * sizeof(Instruction*));
  }
  InnerIR.curI->line = InnerIR.curInsIdx;
  InnerIR.ins[InnerIR.curInsIdx++] = InnerIR.curI;
}

static void _NewIns(IRType t) {
  InnerIR.curI = ArenaAllocFor(sizeof(Instruction));
  memset(InnerIR.curI, 0, sizeof(Instruction));
  InnerIR.curI->type = t;
}

static const char** _GetAttr(int i) {
  ASSERT(i >= 0 && i <= 2);
  return InnerIR.curI->attr + i;
}

static void _Emit(IRType t, const char* attr, ...) {
  _NewIns(t);
  va_list args;
  va_start(args, attr);
  const char* p = attr;
  int i = 0;
  while (p != NULL) {
    *_GetAttr(i++) = p;
    p = va_arg(args, const char*);
  }
  _AppendIns();
}

static int TmpVarCnt = 0;  // for each function, it should begin from 0.
static const char* _GetTmpVar() { return AtomAppend("t", Itoa(TmpVarCnt++)); }

static int LabelCnt = 0;
static const char* _GetLabel() { return AtomAppend("L", Itoa(LabelCnt++)); }

// static const char* _GetMark() {
//   static int MarkCnt = 0;
//   return AtomAppend("M", Itoa(MarkCnt++));
// }

static Instruction* _GetCurIns() { return InnerIR.ins[InnerIR.curInsIdx - 1]; }

// static int _GerCurLine() { return InnerIR.curInsIdx - 1; }

static int32_t _CalArrSize(VarAttr* va) {
  int32_t size = 4;
  for (int i = 0; i < va->arrDimNum; ++i) {
    size *= va->arrDim[i];
  }
  return size;
}

// this is a awful design...but I have no other solution...
static int _AttrCmp(const void* l, const void* r) {
  Attribute* la = (Attribute*)*(void**)l;
  Attribute* ra = (Attribute*)*(void**)r;
  if (la->sType != Function && ra->sType != Function) {
    return la->id - ra->id;
  } else {
    if (la->sType != Function) {
      return -1;
    } else {
      if (ra->sType == Function) {
        return la->id - ra->id;
      } else {
        return 1;
      }
    }
  }
}

static void** _GenerateDeclSeq(struct table_t* table) {
  if (table == NULL) {
    return NULL;
  }
  void** arr = ALLOC((table->size + 1) * (sizeof(void*)));
  int i, j;
  for (i = 0, j = 0; i < table->capacity; i++) {
    for (struct binding* p = table->buckets[i]; p != NULL; p = p->link) {
      arr[j++] = p->value;
    }
  }
  arr[j] = NULL;
  qsort(arr, table->size, sizeof(void*), _AttrCmp);
  return arr;
}

static int _CalCurrentIDBase(Scope* s) {
  if (s->sType == Global) {
    return 0;
  }
  int base = 0;
  while (true) {
    s = s->prev;
    if (s->sType == Global) {
      break;
    }
    base += s->cnt;
  }
  return base;
}

static const char* _SearchFromCurScope(ASTNode* id) {
  Attribute* a;

  for (Scope* s = CurrentScope; s != NULL; s = s->prev) {
    if (s->curTab == NULL) {
      continue;
    }
    a = TableGet(s->curTab, id->attr[0]);
    if (a != NULL && id->line >= a->declLoc) {
      const char* p = "x";
      if (s->sType == Global) {
        p = "g";
      }
      return AtomAppend(p, Itoa(a->id + _CalCurrentIDBase(s)));
    }
  }
  RAISE(Unreachable);
  return NULL;
}

static const char* _GenerateFromExpr(ASTNode* n);

static const char* _GenerateFromUnarayExpr(ASTNode* n) {
  const char* y = _GenerateFromExpr(n->attr[1]);
  if (n->attr[0] == AtomString("+")) {
    return y;
  }
  const char* x = NULL;
  if (n->attr[0] == AtomString("~")) {
    x = _GetTmpVar();
    _Emit(IR_UOP_BNOT, x, y, NULL);
  } else if (n->attr[0] == AtomString("!")) {
    x = _GetTmpVar();
    _Emit(IR_UOP_NOT, x, y, NULL);
  } else if (n->attr[0] == AtomString("++")) {
    x = y;
    _Emit(IR_BOP_ADD, x, y, AtomString("0x1"), NULL);
  } else if (n->attr[0] == AtomString("--")) {
    x = y;
    _Emit(IR_BOP_SUB, x, y, AtomString("0x1"), NULL);
  } else if (n->attr[0] == AtomString("-")) {
    x = _GetTmpVar();
    _Emit(IR_UOP_MINUS, x, y, NULL);
  } else if (n->attr[0] == AtomString("f-")) {
    x = _GetTmpVar();
    _Emit(IR_UOP_FMINUS, x, y, NULL);
  } else {
    RAISE(Unreachable);
  }
  return x;
}
static const char* _GenerateFromPostfixExpr(ASTNode* n);

static const char* _GenerateFromBinaryExpr(ASTNode* n) {
  if (n->attr[0] == AtomString("=")) {
    ASTNode* l = n->attr[1];
    ASTNode* r = n->attr[2];
    if (l->nType == PostfixExpr) {
      const char* y = _GenerateFromPostfixExpr(l);
      const char* z = _GenerateFromExpr(r);
      _Emit(IR_COPY_TO_DEREF, y, z, NULL);
      return z;
    } else {
      const char* y = _GenerateFromExpr(l);
      const char* z = _GenerateFromExpr(r);
      _Emit(IR_COPY, y, z, NULL);
      return y;
    }
  }

  const char* y = _GenerateFromExpr(n->attr[1]);
  if (n->attr[0] == AtomString("&&")) {
    const char* x = _GetTmpVar();
    _Emit(IR_JUMP_IF, y, NULL, NULL);
    Instruction* i1 = _GetCurIns();
    _Emit(IR_COPY, x, AtomString("0x0"), NULL);
    _Emit(IR_GOTO, NULL);
    Instruction* i2 = _GetCurIns();
    i1->attr[1] = _GetLabel();
    _Emit(IR_LABEL, i1->attr[1], NULL);
    const char* z = _GenerateFromExpr(n->attr[2]);
    _Emit(IR_BOP_AND, x, y, z, NULL);
    i2->attr[0] = _GetLabel();
    _Emit(IR_LABEL, i2->attr[0], NULL);
    return x;
  }

  if (n->attr[0] == AtomString("||")) {
    const char* x = _GetTmpVar();
    _Emit(IR_JUMP_IF, y, NULL, NULL);
    Instruction* i1 = _GetCurIns();
    const char* z = _GenerateFromExpr(n->attr[2]);
    _Emit(IR_BOP_OR, x, y, z, NULL);
    _Emit(IR_GOTO, NULL);
    Instruction* i2 = _GetCurIns();
    i1->attr[1] = _GetLabel();
    _Emit(IR_LABEL, i1->attr[1], NULL);
    _Emit(IR_COPY, x, AtomString("0x1"), NULL);
    i2->attr[0] = _GetLabel();
    _Emit(IR_LABEL, i2->attr[0], NULL);
    return x;
  }

  const char* z = _GenerateFromExpr(n->attr[2]);

  const char* x = _GetTmpVar();
  if (n->attr[0] == AtomString(",")) {
    _Emit(IR_COPY, x, z, NULL);
    return x;
  }

  if (n->attr[0] == AtomString("+")) {
    _Emit(IR_BOP_ADD, x, y, z, NULL);
  } else if (n->attr[0] == AtomString("-")) {
    _Emit(IR_BOP_SUB, x, y, z, NULL);
  } else if (n->attr[0] == AtomString("*")) {
    _Emit(IR_BOP_MUL, x, y, z, NULL);
  } else if (n->attr[0] == AtomString("/")) {
    _Emit(IR_BOP_DIV, x, y, z, NULL);
  } else if (n->attr[0] == AtomString("%")) {
    _Emit(IR_BOP_MOD, x, y, z, NULL);
  } else if (n->attr[0] == AtomString("<<")) {
    _Emit(IR_BOP_SL, x, y, z, NULL);
  } else if (n->attr[0] == AtomString(">>")) {
    _Emit(IR_BOP_SR, x, y, z, NULL);
  } else if (n->attr[0] == AtomString("&")) {
    _Emit(IR_BOP_BAND, x, y, z, NULL);
  } else if (n->attr[0] == AtomString("|")) {
    _Emit(IR_BOP_BOR, x, y, z, NULL);
  } else if (n->attr[0] == AtomString("^")) {
    _Emit(IR_BOP_BXOR, x, y, z, NULL);
  } else if (n->attr[0] == AtomString("<")) {
    _Emit(IR_BOP_LT, x, y, z, NULL);
  } else if (n->attr[0] == AtomString(">")) {
    _Emit(IR_BOP_GT, x, y, z, NULL);
  } else if (n->attr[0] == AtomString("<=")) {
    _Emit(IR_BOP_LE, x, y, z, NULL);
  } else if (n->attr[0] == AtomString(">=")) {
    _Emit(IR_BOP_GE, x, y, z, NULL);
  } else if (n->attr[0] == AtomString("==")) {
    _Emit(IR_BOP_EQ, x, y, z, NULL);
  } else if (n->attr[0] == AtomString("!=")) {
    _Emit(IR_BOP_NE, x, y, z, NULL);
  } else if (n->attr[0] == AtomString("f+")) {
    _Emit(IR_BOP_FADD, x, y, z, NULL);
  } else if (n->attr[0] == AtomString("f-")) {
    _Emit(IR_BOP_FSUB, x, y, z, NULL);
  } else if (n->attr[0] == AtomString("f*")) {
    _Emit(IR_BOP_FMUL, x, y, z, NULL);
  } else if (n->attr[0] == AtomString("f/")) {
    _Emit(IR_BOP_FDIV, x, y, z, NULL);
  } else if (n->attr[0] == AtomString("f<")) {
    _Emit(IR_BOP_FLT, x, y, z, NULL);
  } else if (n->attr[0] == AtomString("f>")) {
    _Emit(IR_BOP_FGT, x, y, z, NULL);
  } else if (n->attr[0] == AtomString("f<=")) {
    _Emit(IR_BOP_FLE, x, y, z, NULL);
  } else if (n->attr[0] == AtomString("f>=")) {
    _Emit(IR_BOP_FGE, x, y, z, NULL);
  } else if (n->attr[0] == AtomString("f==")) {
    _Emit(IR_BOP_FEQ, x, y, z, NULL);
  } else if (n->attr[0] == AtomString("f!=")) {
    _Emit(IR_BOP_FNE, x, y, z, NULL);
  } else {
    RAISE(Unreachable);
    return NULL;
  }
  return x;
}

static const char* _GenerateFromPostfixExpr(ASTNode* n) {
  static const int* ArrCurDim = NULL;
  static int ArrCurOffset = 4;
  static int ArrCurIdx = 0;
  if (n->nType == Identifier) {
    Attribute* a;
    Scope* s = CurrentScope;
    while (s != NULL) {
      if (s->curTab == NULL) {
        s = s->prev;
        continue;
      }
      a = TableGet(s->curTab, n->attr[0]);
      if (a != NULL) {
        break;
      }
      s = s->prev;
    }
    ArrCurDim = a->aa.v->arrDim;
    ArrCurIdx = 0;
    for (int i = 0; i < a->aa.v->arrDimNum; ++i) {
      ArrCurOffset *= ArrCurDim[i];
    }
    const char* p = s->sType == Global ? "g" : "x";
    return AtomAppend(p, Itoa(a->id + _CalCurrentIDBase(s)));
  }
  const char* x = _GenerateFromPostfixExpr(n->attr[1]);
  ArrCurOffset /= ArrCurDim[ArrCurIdx++];
  const char* y = _GenerateFromExpr(n->attr[2]);
  const char* t1 = _GetTmpVar();
  _Emit(IR_BOP_MUL, t1, y, AtomString(Itox(ArrCurOffset)), NULL);
  const char* t2 = _GetTmpVar();
  _Emit(IR_BOP_ADD, t2, x, t1, NULL);
  // check bound
  return t2;
}

static void _GenerateFromArgList(ASTNode* n, int* cnt) {
  if (n == NULL) {
    return;
  }
  _GenerateFromArgList(n->attr[0], cnt);
  _Emit(IR_ARG, _GenerateFromExpr(n->attr[1]), NULL);
  (*cnt)++;
}

static const char* _GenerateFromExpr(ASTNode* n) {
  if (n == NULL) {
    return NULL;
  }
  if (n->nType == Identifier) {
    // find recurrsively fron current scope
    // return the id
    return _SearchFromCurScope(n);
  } else if (n->nType == IntConst) {
    return AtomString(Itox(strtol(n->attr[0], NULL, 0)));
  } else if (n->nType == BoolConst) {
    if (n->attr[0] == AtomString("false")) {
      return AtomString("0x0");
    } else {
      return AtomString("0x1");
    }
  } else if (n->nType == StrConst) {
    return TableGet(InnerIR.ConstTable, n->attr[0]);
  } else if (n->nType == FloatConst) {
    return AtomString(Ftox(strtof(n->attr[0], NULL)));
  } else if (n->nType == BinaryExpr) {
    return _GenerateFromBinaryExpr(n);
  } else if (n->nType == UnaryExpr) {
    return _GenerateFromUnarayExpr(n);
  } else if (n->nType == PostfixExpr) {
    const char* y = _GenerateFromPostfixExpr(n);
    const char* x = _GetTmpVar();
    _Emit(IR_COPY_FROM_DEREF, x, y, NULL);
    return x;
  } else if (n->nType == FunctionCall) {
    int argCnt = 0;
    _GenerateFromArgList(n->attr[1], &argCnt);
    ASTNode* id = n->attr[0];
    _Emit(IR_CALL, id->attr[0], AtomString(Itox(argCnt)), NULL);
    Attribute* a = TableGet(GlobalScope->curTab, id->attr[0]);
    if (a->aa.f->returnType != AtomString("void")) {
      const char* rv = _GetTmpVar();
      _Emit(IR_COPY, rv, "rv", NULL);
      return rv;
    } else {
      return NULL;
    }
  } else {
    RAISE(Unreachable);
  }
  return NULL;
}

static void _GenerateFromIOStm(ASTNode* n) {
  const char* fmt = _GenerateFromExpr(n->attr[1]);
  if (n->attr[0] == AtomString("print")) {
    const char* x = _GenerateFromExpr(n->attr[2]);
    _Emit(IR_PRINT, fmt, x, NULL);
  } else if (n->attr[0] == AtomString("scan")) {
    ASTNode* np = n->attr[2];
    const char* x;
    if (np->nType == PostfixExpr) {
      x = _GenerateFromPostfixExpr(np);
      const char* t = _GetTmpVar();
      _Emit(IR_SCAN, fmt, t, NULL);
      _Emit(IR_COPY_TO_DEREF, x, t, NULL);
    } else {
      x = _GenerateFromExpr(np);
      _Emit(IR_SCAN, fmt, x, NULL);
    }
  } else {
    RAISE(Unreachable);
  }
}

static void _GenerateFromCompoundStm(ASTNode* n);
static void _GenerateFromStm(ASTNode* n);

static void _GenerateFromLoopStm(ASTNode* n) {
  // initialization
  _GenerateFromStm(n->attr[0]);
  // goto cond
  _Emit(IR_GOTO, NULL);  // goto cond
  Instruction* inLoop = _GetCurIns();
  // label in
  const char* in = _GetLabel();
  _Emit(IR_LABEL, in, NULL);
  Instruction* begin = _GetCurIns();
  StackPush(ContinueInsStk, begin);
  StackPush(BreakInsStk, begin);
  // body
  _GenerateFromCompoundStm(n->attr[3]);
  // label continue
  const char* skip = _GetLabel();
  _Emit(IR_LABEL, skip, NULL);
  // fill continue
  if (!StackEmpty(ContinueInsStk)) {
    Instruction* continueIns = StackPop(ContinueInsStk);
    while (continueIns->line > begin->line) {
      continueIns->attr[0] = skip;
      continueIns = StackPop(ContinueInsStk);
    }
  }
  // increment
  _GenerateFromExpr(n->attr[2]);
  // condition
  const char* cond = _GetLabel();
  inLoop->attr[0] = cond;
  _Emit(IR_LABEL, cond, NULL);

  const char* condition = _GenerateFromExpr(((ASTNode*)(n->attr[1]))->attr[0]);
  // if [cond] goto [label in]
  _Emit(IR_JUMP_IF, condition, in, NULL);
  // label out
  const char* out = _GetLabel();
  _Emit(IR_LABEL, out, NULL);
  // fill break
  if (!StackEmpty(BreakInsStk)) {
    Instruction* breakIns = StackPop(BreakInsStk);
    while (breakIns->line > begin->line) {
      breakIns->attr[0] = out;
      breakIns = StackPop(BreakInsStk);
    }
  }
}

static void _GenerateFromSelectStm(ASTNode* n) {
  const char* cond = _GenerateFromExpr(n->attr[0]);
  _Emit(IR_JUMP_IF_NOT, cond, NULL, NULL);
  Instruction* i = _GetCurIns();
  _GenerateFromCompoundStm(n->attr[1]);
  const char* nop = _GetLabel();
  _Emit(IR_LABEL, nop, NULL);
  i->attr[1] = nop;
  // fill back
  if (n->attr[2] != NULL) {
    _GenerateFromStm(n->attr[2]);
  }
}

static void _GenerateFromStm(ASTNode* n) {
  if (n->nType == CompoundStm) {
    _GenerateFromCompoundStm(n);
  } else if (n->nType == LoopStm) {
    _GenerateFromLoopStm(n);
  } else if (n->nType == SelectionStm) {
    _GenerateFromSelectStm(n);
  } else if (n->nType == JumpStm) {
    if (n->attr[0] == AtomString("continue")) {
      _Emit(IR_GOTO, NULL, NULL);  // label skip
      StackPush(ContinueInsStk, _GetCurIns());
    } else if (n->attr[0] == AtomString("break")) {
      _Emit(IR_GOTO, NULL, NULL);  // label out
      StackPush(BreakInsStk, _GetCurIns());
    } else if (n->attr[0] == AtomString("return")) {
      _Emit(IR_RETURN, _GenerateFromExpr(n->attr[1]), NULL);
    } else {
      RAISE(Unreachable);
    }
  } else if (n->nType == IOStm) {
    _GenerateFromIOStm(n);
  } else if (n->nType == ExpressionStm) {
    _GenerateFromExpr(n->attr[0]);
  } else {
    RAISE(UnexpectedNodeType);
  }
}

static void _GenerateFromStmList(ASTNode* n) {
  if (n == NULL) {
    return;
  }
  _GenerateFromStmList(n->attr[0]);
  _GenerateFromStm(n->attr[1]);
}

static void _GenerateFromInitializer(ASTNode* n, const char* base);
static void _GenerateFromInitializerList(ASTNode* n, const char* base) {
  if (n == NULL) {
    return;
  }
  _GenerateFromInitializerList(n->attr[0], base);
  _GenerateFromInitializer(n->attr[1], base);
}

static int ArrInitOffset = 0;
static void _GenerateFromInitializer(ASTNode* n, const char* base) {
  if (n->nType == Initializer) {
    const char* tar = _GetTmpVar();
    _Emit(IR_BOP_ADD, tar, base, AtomString(Itox(ArrInitOffset)), NULL);
    _Emit(IR_COPY_TO_DEREF, tar, _GenerateFromExpr(n->attr[0]), NULL);
    ArrInitOffset += 4;
  } else if (n->nType == ArrayInitializer) {
    _GenerateFromInitializerList(n->attr[0], base);
  } else {
    RAISE(UnexpectedNodeType);
  }
}

static void _GenerateFromVarDecl(Attribute* a, const char* prefix) {
  ASTNode* init = a->aa.v->initializer;
  if (a->sType == Parameter) {  // PARAM
    const char* cp = AtomAppend(prefix, Itoa(a->id + _CalCurrentIDBase(CurrentScope)));
    _Emit(IR_PARAM, cp, NULL);
    return;
  }

  if (a->aa.v->arrDimNum > 0) {  // MALLOC
    const char* cp = AtomAppend(prefix, Itoa(a->id + _CalCurrentIDBase(CurrentScope)));
    _Emit(IR_MALLOC, cp, AtomString(Itox(_CalArrSize(a->aa.v))), NULL);
    if (init != NULL) {
      ArrInitOffset = 0;
      _GenerateFromInitializer(init, cp);
    }
  } else if (a->aa.v->arrDimNum == 0) {  // VAR
    const char* cp = AtomAppend(prefix, Itoa(a->id + _CalCurrentIDBase(CurrentScope)));
    _Emit(IR_VAR, cp, NULL);
    if (init != NULL) {
      _Emit(IR_COPY, cp, _GenerateFromExpr(init->attr[0]), NULL);
    }
  } else {
    RAISE(Unreachable);
  }
}

static void _GenerateFromScopeDecl() {
  int idx = 0;
  void** arr = _GenerateDeclSeq(CurrentScope->curTab);
  if (arr == NULL) {
    return;
  }
  Attribute* a;
  while (arr[idx] != NULL) {
    a = (Attribute*)(arr[idx]);
    if (a->sType != Function) {
      _GenerateFromVarDecl(a, "x");
    } else {
      RAISE(Unreachable);
    }
    idx++;
  }
  FREE(arr);
}

static void _GenerateFromCompoundStm(ASTNode* n) {
  _GenerateFromScopeDecl();
  Scope* tmp = NULL;
  if (CurrentScope->next != NULL) {
    tmp = CurrentScope;
    CurrentScope = CurrentScope->next;
  }
  _GenerateFromStmList(n->attr[1]);
  if (tmp != NULL) {
    CurrentScope = CurrentScope->prev;
  }
  if (CurrentScope->peer != NULL) {
    CurrentScope = CurrentScope->peer;
  }
}

static void _GenerateFromGlobalScope() {
  int idx = 0;
  void** arr = _GenerateDeclSeq(CurrentScope->curTab);
  Attribute* a;
  while (arr[idx] != NULL) {
    a = (Attribute*)(arr[idx]);
    if (a->sType != Function) {
      _GenerateFromVarDecl(a, "g");
    } else {
      _Emit(IR_CALL, AtomString("main"), AtomString("0x0"), NULL);
      _Emit(IR_EXIT, NULL);
      break;
    }
    idx++;
  }
  TmpVarCnt = 0;
  CurrentScope->cnt = idx;
  CurrentScope = CurrentScope->next;
  ASTNode *f, *id, *body;
  while (arr[idx] != NULL) {
    _Emit(IR_NOP, NULL);
    a = (Attribute*)(arr[idx]);
    if (a->sType == Function) {
      if (a->aa.f->defNode == NULL) {
        break;
      }
      f = a->aa.f->defNode;
      id = f->attr[1];
      body = ((ASTNode*)(f->attr[3]))->attr[1];
      _Emit(IR_FUNCTION, id->attr[0], NULL);
      _GenerateFromScopeDecl();
      Scope* tmp = NULL;
      if (CurrentScope->next != NULL) {
        tmp = CurrentScope;
        CurrentScope = CurrentScope->next;
      }
      _GenerateFromStmList(body);
      TmpVarCnt = 0;
      if (tmp != NULL) {
        CurrentScope = CurrentScope->prev;
      }
      if (CurrentScope->peer != NULL) {
        CurrentScope = CurrentScope->peer;
      }
    } else {
      RAISE(Unreachable);
    }

    idx++;
  }
  FREE(arr);
}

IR GenerateIR(SymbolTable* st) {
  GlobalScope = CurrentScope = st->s;
  InnerIR.ConstTable = st->constTable;
  ContinueInsStk = StackCreate();
  BreakInsStk = StackCreate();
  _Emit(IR_LABEL, _GetLabel(), NULL);  // label 0 is the entry
  _GenerateFromGlobalScope();
  StackFree(&ContinueInsStk);
  StackFree(&BreakInsStk);
  return InnerIR;
}

void FreeIR(IR* ir) {
  FREE(ir->ins);
  // TableFree(&(ir->ConstTable));
  memset(ir, 0, sizeof(IR));
}