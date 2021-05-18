// #define PY_SSIZE_T_CLEAN
#include "ast.h"
#include "../lib/llsc.h"
#include "exception.h"
#include <string.h>
// #include <python3.8/Python.h>
#include <stdio.h>
#include <stdlib.h>

static size_t ASTNodeSize(int nChild) {
  return sizeof(ASTNode) + sizeof(void *) * nChild;
}

ASTNode *NewASTNode(ASTNodeType t, int line) {
  ASTNode *r;
  if (t <= ArrayInitializer) {
    r = ArenaAllocFor(ASTNodeSize(1));
  } else if (t <= ParameterTypeList) {
    r = ArenaAllocFor(ASTNodeSize(2));
  } else if (t <= FunctionDecl) {
    r = ArenaAllocFor(ASTNodeSize(3));
  } else if (t <= FunctionDef) {
    r = ArenaAllocFor(ASTNodeSize(4));
  } else {
    RAISE(UnknownNodeType);
  }
  r->nType = t;
  r->line = line;
  return r;
}

static _Bool TopDown = false;
static void _GoDown(ASTNode *node, mapper m, void *cl);
static void _Map(ASTNode *node, mapper m, void *cl);

static void _MapForList(ASTNode *node, mapper m, void *cl) {
  if (node == NULL) {
    return;
  }
  _MapForList((ASTNode *)node->attr[0], m, cl);
  _Map((ASTNode *)node->attr[1], m, cl);
  if (!TopDown) {
    m(node, cl);
  }
}

static void _Map(ASTNode *node, mapper m, void *cl) {
  if (node == NULL) {
    return;
  }
  if (cl != NULL) {
    (*((int *)cl))++; // down to the child node, depth++
  }
  _GoDown(node, m, cl);
  if (cl != NULL) {
    (*((int *)cl))--; // back to the father node, depth--
  }
}

static void _GoDown(ASTNode *node, mapper m, void *cl) {
  if (TopDown) {
    m(node, cl);
  }
  if (node->nType <= TypeSpecifier) {
    // do nothing
  } else if (node->nType <= ArrayInitializer) {
    _Map((ASTNode *)(node->attr[0]), m, cl);
  } else if (node->nType <= UnaryExpr) {
    _Map((ASTNode *)(node->attr[1]), m, cl);
  } else if (node->nType <= CompoundStm) {
    _Map((ASTNode *)(node->attr[0]), m, cl);
    _Map((ASTNode *)(node->attr[1]), m, cl);
  } else if (node->nType <= ParameterTypeList) {
    _MapForList(node, m, cl);
    return; // must return, or it may call mapper twice.
  } else if (node->nType <= BinaryExpr) {
    _Map((ASTNode *)(node->attr[1]), m, cl);
    _Map((ASTNode *)(node->attr[2]), m, cl);
  } else if (node->nType <= FunctionDecl) {
    _Map((ASTNode *)(node->attr[0]), m, cl);
    _Map((ASTNode *)(node->attr[1]), m, cl);
    _Map((ASTNode *)(node->attr[2]), m, cl);
  } else if (node->nType <= FunctionDef) {
    _Map((ASTNode *)(node->attr[0]), m, cl);
    _Map((ASTNode *)(node->attr[1]), m, cl);
    _Map((ASTNode *)(node->attr[2]), m, cl);
    _Map((ASTNode *)(node->attr[3]), m, cl);
  } else {
    RAISE(UnknownNodeType);
  }
  if (!TopDown) {
    m(node, cl);
  }
}

void Map(AST *t, mapper m, void *cl, _Bool topDown) {
  TopDown = topDown;
  _Map(t->root, m, cl);
}

// TypeStr is corrsponding to ASTNodeType.
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
static void _Printer(ASTNode *node, void *cl) {
#define Attr(node, n) ((const char *)(node->attr[(n)]))
  Fmt *fmt = cl;
  if (node->nType <= TypeSpecifier) {
    fprintf(fmt->out, "%-d %s: %s\n", fmt->depth, TypeStr[node->nType],
            Attr(node, 0));
  } else if (node->nType <= ArrayInitializer) {
    fprintf(fmt->out, "%-d %s\n", fmt->depth, TypeStr[node->nType]);
  } else if (node->nType <= UnaryExpr) {
    fprintf(fmt->out, "%-d %s: %s\n", fmt->depth, TypeStr[node->nType],
            Attr(node, 0));
  } else if (node->nType <= ParameterTypeList) {
    fprintf(fmt->out, "%-d %s\n", fmt->depth, TypeStr[node->nType]);
  } else if (node->nType <= BinaryExpr) {
    fprintf(fmt->out, "%-d %s: %s\n", fmt->depth, TypeStr[node->nType],
            Attr(node, 0));
  } else if (node->nType <= FunctionDef) {
    fprintf(fmt->out, "%-d %s\n", fmt->depth, TypeStr[node->nType]);
  } else {
    RAISE(UnknownNodeType);
  }
#undef Attr
}

static const char *BeautifyAST_py = "./bin/BeautifyAST.py";

static void _BeautifyAST(Fmt *fmt) {
  char buffer[128];

  // memset(buffer, 0, sizeof(buffer));
  // sprintf(buffer, "%s %s","sudo chmod +x", BeautifyAST_py);
  // system(buffer);

  memset(buffer, 0, sizeof(buffer));
  sprintf(buffer, "%s %s", BeautifyAST_py, fmt->fileLoc);
  system(buffer);

  // wchar_t *program = Py_DecodeLocale("lscp", NULL);
  // ASSERT(program != NULL);
  // wchar_t *fileLoc = Py_DecodeLocale(fmt->fileLoc, NULL);
  // ASSERT(fileLoc != NULL);
  // wchar_t *argv[] = {program, fileLoc};

  // FILE *pyFp = fopen(BeautifyAST_py, "r");
  // ASSERT(pyFp != NULL);

  // Py_SetProgramName(program);
  // Py_Initialize();
  // PySys_SetArgv(2, argv);
  // PyRun_SimpleFile(pyFp, BeautifyAST_py);
  // int ret = Py_FinalizeEx();
  // ASSERT(ret == 0);

  // PyMem_RawFree(program);
  // PyMem_RawFree(fileLoc);
}

void DisplayAST(AST *t, Fmt *fmt) {
  Map(t, _Printer, fmt, true);
  fclose(fmt->out);
  _BeautifyAST(fmt);
}

// void FreeAttr(ASTNode *node, void *cl) {
//   if (node->nType <= TypeSpecifier) {
//     return;
//   } else if (node->nType <= ArrayInitializer) {
//     FREE((node->attr[0]));
//   } else if (node->nType <= UnaryExpr) {
//     FREE((node->attr[1]));
//   } else if (node->nType <= ParameterTypeList) {
//     FREE((node->attr[0]));
//     FREE((node->attr[1]));
//   } else if (node->nType <= BinaryExpr) {
//     FREE((node->attr[1]));
//     FREE((node->attr[2]));
//   } else if (node->nType <= FunctionDecl) {
//     FREE((node->attr[0]));
//     FREE((node->attr[1]));
//     FREE((node->attr[2]));
//   } else if (node->nType <= FunctionDef) {
//     FREE((node->attr[0]));
//     FREE((node->attr[1]));
//     FREE((node->attr[2]));
//     FREE((node->attr[3]));
//   } else {
//     RAISE(UnknownNodeType);
//   }
// }

// void FreeAST(AST *t) {
//   Map(t, FreeAttr, NULL, false);
//   FREE(t->root);
//   t->root = NULL;
// }

// TODO: try to implement tree command
// Use ANSI to draw a tree like tree command.
// static const char *HorizonLine = "─";
// static const char *VerticalLine = "│";
// static const char *Corner = "└";
// static const char *Branch = "├";

void SpecifyType(ASTNode *node, const char *baseType) {
  if (node == NULL) {
    return;
  }
  if (node->nType != DeclaratorList) {
    RAISE(UnknownNodeType);
  }
  ASTNode *d = (ASTNode *)(node->attr[1]);
  ASTNode *ts = (ASTNode *)(d->attr[0]);
  const char *t = ts->attr[0];
  if (t == NULL) {
    t = "";
  }
  ts->attr[0] = (void *)AtomAppend(baseType, t);
  SpecifyType((ASTNode *)(node->attr[0]), baseType);
}