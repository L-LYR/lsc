#include "display.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../lib/llsc.h"
#include "exception.h"

extern Scope *GlobalSymbolTable;

static char TmpInnerBuffer[128];

static const char *SymbolTypeStrs[] = {
    "Function",
    "Variable",
};

static const char *SymbolTableHeaders[] = {
    "Identifier", "Type", "Specified Type", "Offset", "Declaration Location", NULL,
};

static const char *FuncDefDetailHeaders[] = {
    "Function Name", "Definition Location", "Parameter Number", "Main Function?", "Return Type", "Parameter Type List", NULL,
};

static const char *TypeStr[] = {
    "Bool Constant",       "Integer Constant",
    "Float Constant",      "String Constant",
    "Identifier",          "Specified Type",
    "Initializer",         "Expression Statement",
    "Array Initializer",   "IO Statement",
    "Jump Statement",      "Unary Expression",
    "Declaration",         "Function Call",
    "Compound Statement",  "Arugument List",
    "Declaration List",    "Statement List",
    "Declarator List",     "Initializer List",
    "Global List",         "Parameter Declaration List",
    "Parameter Type List", "Postfix Expression",
    "Bianry Expression",   "Selection Statement",
    "Declarator",          "Function Declaration",
    "Loop Statement",      "Function Definition",
};

// from lscp.c
extern _Bool Pause;
extern Fmt SymbolTableDisplayFmt;

// wrapper of fprintf for stderr
void _Notify(const char *fmtStr, ...) {
  // generally notify
  va_list args;
  va_start(args, fmtStr);
  vfprintf(stderr, fmtStr, args);
  va_end(args);
}

void _NotifyRedeclaration(int curLine, const char *id, SymbolType declareType, int declareLine) {
  static const char *Redeclaration = "Line %d: '%s' has been declared as '%s' at line %d.\n\n";
  _Notify(Redeclaration, curLine, id, SymbolTypeStrs[declareType], declareLine);
}

void _NotifyRedefinition(int curLine, const char *id, SymbolType defineType, int defineLine) {
  static const char *Redefinition = "Line %d: '%s' has been defined as '%s' at line %d.\n\n";
  _Notify(Redefinition, curLine, id, SymbolTypeStrs[defineType], defineLine);
}

void _NotifyTypeConflict(int curLine, const char *id, const char *tNew, const char *tOld, int declareLine) {
  static const char *Conflict = "Line %d: Conflicting types for '%s', '%s' is no match for '%s' at line %d.\n\n";
  _Notify(Conflict, curLine, id, tNew, tOld, declareLine);
}

void _NotifyInvalidLocOfJumpStm(int curLine, const char *stm, const char *loc) {
  static const char *InvalidLocOfJumpStm = "Line %d: '%s' statement is not in %s.\n\n";
  _Notify(InvalidLocOfJumpStm, curLine, stm, loc);
}

void _NotifyWrongReturnStm(int curLine, const char *id, _Bool needReturn) {
  static const char *VoidFunctionShouldNotReturn = "Line %d: void function '%s' should not return a value.\n\n";
  static const char *NonVoidFunctionMustReturn = "Line %d: non-void function '%s' need return a value.\n\n";
  if (!needReturn) {
    _Notify(VoidFunctionShouldNotReturn, curLine, id);
  } else {
    _Notify(NonVoidFunctionMustReturn, curLine, id);
  }
}

void _NotifyRepetition(Attribute *old, Attribute *new, const char *id) {
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

void _PauseForDisplay() {
  if (Pause) {
    fprintf(stdout, "Stop For Display Current Symbol Table.\n");
    DisplaySymbolTable(GlobalSymbolTable, &SymbolTableDisplayFmt);
    fprintf(stdout, "Press Any Key To Continue...\n");
    getchar();
  }
}

static void _DisplayTableHeaders(Fmt *fmt, const char *p[]) {
  fprintf(fmt->out, "%s", *p++);
  while (*p != NULL) {
    fprintf(fmt->out, ";%s", *p++);
  }
  fputc('\n', fmt->out);
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
  memset(TmpInnerBuffer, 0, sizeof(TmpInnerBuffer));
  sprintf(TmpInnerBuffer, "%s %s", BeautifyST_py, fmt->fileLoc);
  system(TmpInnerBuffer);
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

static void _DisplayNode(ASTNode *node, Fmt *fmt) {
#define Attr(node, n) ((const char *)(node->attr[(n)]))
  if (node->nType <= TypeSpecifier) {
    fprintf(fmt->out, "%-d %s: %s\n", fmt->depth, TypeStr[node->nType], Attr(node, 0));
  } else if (node->nType <= ArrayInitializer) {
    fprintf(fmt->out, "%-d %s\n", fmt->depth, TypeStr[node->nType]);
  } else if (node->nType <= UnaryExpr) {
    fprintf(fmt->out, "%-d %s: %s\n", fmt->depth, TypeStr[node->nType], Attr(node, 0));
  } else if (node->nType <= ParameterTypeList) {
    fprintf(fmt->out, "%-d %s\n", fmt->depth, TypeStr[node->nType]);
  } else if (node->nType <= BinaryExpr) {
    fprintf(fmt->out, "%-d %s: %s\n", fmt->depth, TypeStr[node->nType], Attr(node, 0));
  } else if (node->nType <= FunctionDef) {
    fprintf(fmt->out, "%-d %s\n", fmt->depth, TypeStr[node->nType]);
  } else {
    RAISE(UnknownNodeType);
  }
#undef Attr
}

static void _DisplayAST(ASTNode *node, Fmt *fmt);
static void _DisplayNodeList(ASTNode *node, Fmt *fmt) {
  if (node == NULL) {
    return;
  }
  _DisplayNodeList(node->attr[0], fmt);
  _DisplayAST(node->attr[1], fmt);
}

static void _GoDown(ASTNode *node, Fmt *fmt) {
  if (node->nType <= TypeSpecifier) {
    // do nothing
  } else if (node->nType <= ArrayInitializer) {
    _DisplayAST(node->attr[0], fmt);
  } else if (node->nType <= UnaryExpr) {
    _DisplayAST(node->attr[1], fmt);
  } else if (node->nType <= CompoundStm) {
    _DisplayAST(node->attr[0], fmt);
    _DisplayAST(node->attr[1], fmt);
  } else if (node->nType <= ParameterTypeList) {
    _DisplayNodeList(node, fmt);
    return;  // must return, or it may call mapper twice.
  } else if (node->nType <= BinaryExpr) {
    _DisplayAST(node->attr[1], fmt);
    _DisplayAST(node->attr[2], fmt);
  } else if (node->nType <= FunctionDecl) {
    _DisplayAST(node->attr[0], fmt);
    _DisplayAST(node->attr[1], fmt);
    _DisplayAST(node->attr[2], fmt);
  } else if (node->nType <= FunctionDef) {
    _DisplayAST(node->attr[0], fmt);
    _DisplayAST(node->attr[1], fmt);
    _DisplayAST(node->attr[2], fmt);
    _DisplayAST(node->attr[3], fmt);
  } else {
    RAISE(UnknownNodeType);
  }
}

static void _BeautifyAST(Fmt *fmt) {
  static const char *BeautifyAST_py = "./bin/BeautifyAST.py";
  memset(TmpInnerBuffer, 0, sizeof(TmpInnerBuffer));
  sprintf(TmpInnerBuffer, "%s %s", BeautifyAST_py, fmt->fileLoc);
  system(TmpInnerBuffer);
}

static void _DisplayAST(ASTNode *node, Fmt *fmt) {
  if (node == NULL) {
    return;
  }
  fmt->depth++;
  _DisplayNode(node, fmt);
  _GoDown(node, fmt);
  fmt->depth--;
}

void DisplayAST(AST *t, Fmt *fmt) {
  fmt->out = fopen(fmt->fileLoc, "w");
  if (fmt->out == NULL) {
    RAISE(OutFileOpenErr);
  }
  _DisplayAST(t->root, fmt);
  fclose(fmt->out);
  _BeautifyAST(fmt);
}