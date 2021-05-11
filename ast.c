#include "ast.h"
#include "panic.h"
#include "text.h"
#include <stdio.h>
#include <stdlib.h>

static size_t ASTNodeSize(int nChild) {
  return sizeof(ASTNode) + sizeof(void *) * nChild;
}

ASTNode *NewASTNode(ASTNodeType t) {
  ASTNode *r;
  if (t <= ArrayInitializer) {
    r = (ASTNode *)malloc(ASTNodeSize(1));
  } else if (t <= ParameterTypeList) {
    r = (ASTNode *)malloc(ASTNodeSize(2));
  } else if (t <= FunctionDecl) {
    r = (ASTNode *)malloc(ASTNodeSize(3));
  } else if (t <= FunctionDef) {
    r = (ASTNode *)malloc(ASTNodeSize(4));
  } else {
    PANIC("unkown type of AST node!");
  }
  if (r == NULL) {
    PANIC("bad malloc!");
  }
  r->nType = t;
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
    return; // or it may call mapper twice.
  } else if (node->nType <= BinaryExpr) {
    _Map((ASTNode *)(node->attr[0]), m, cl);
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
    PANIC("unkown type of AST node!");
  }
  if (!TopDown) {
    m(node, cl);
  }
}

void Map(AST *t, mapper m, void *cl, _Bool topDown) {
  TopDown = topDown;
  _Map(t->root, m, cl);
}

static int UnitIndent = 2;
// TypeStr is corrsponding to ASTNodeType.
static const char *TypeStr[] = {
    "Bool Constant",
    "Integer Constant",
    "Float Constant",
    "String Constant",
    "Identifier",
    "Specified Type",
    "Initializer",
    "Expression Statement",
    "Array Initializer",
    "IO Statement",
    "Jump Statement",
    "Unary Expression",
    "Function Call",
    "Parameter Declarator",
    "Declaration",
    "Compound Statement",
    "Arugument List",
    "Declaration List",
    "Statement List",
    "Declarator List",
    "Initializer List",
    "Global",
    "Parameter Declaration List",
    "Parameter Type List",
    "Postfix Expression",
    "Bianry Expression",
    "Selection Statement",
    "Declarator",
    "Function Declaration",
    "Loop Statement",
    "Function Definition",
};
void Printer(ASTNode *node, void *cl) {
#define Attr(node, n) ((const char *)(node->attr[(n)]))
  Fmt *fmt = cl;
  int indent = fmt->depth * UnitIndent;
  if (node->nType <= TypeSpecifier) {
    fprintf(fmt->out, "%*s%s: %s\n", indent, "", TypeStr[node->nType],
            Attr(node, 0));
  } else if (node->nType <= ArrayInitializer) {
    fprintf(fmt->out, "%*s%s\n", indent, "", TypeStr[node->nType]);
  } else if (node->nType <= UnaryExpr) {
    fprintf(fmt->out, "%*s%s: %s\n", indent, "", TypeStr[node->nType],
            Attr(node, 0));
  } else if (node->nType <= ParameterTypeList) {
    fprintf(fmt->out, "%*s%s\n", indent, "", TypeStr[node->nType]);
  } else if (node->nType <= BinaryExpr) {
    fprintf(fmt->out, "%*s%s: %s\n", indent, "", TypeStr[node->nType],
            Attr(node, 1));
  } else if (node->nType <= FunctionDef) {
    fprintf(fmt->out, "%*s%s\n", indent, "", TypeStr[node->nType]);
  } else {
    PANIC("unkown type of AST node!");
  }
#undef Attr
}

void DisplayAST(AST *t, Fmt *fmt) {
  fprintf(fmt->out, "AST\n");
  Map(t, Printer, fmt, true);
}

void FreeAttr(ASTNode *node, void *cl) {
  if (node->nType <= ArrayInitializer) {
    free((void *)(node->attr[0]));
  } else if (node->nType <= UnaryExpr) {
    free((void *)(node->attr[1]));
  } else if (node->nType <= ParameterTypeList) {
    free((void *)(node->attr[0]));
    free((void *)(node->attr[1]));
  } else if (node->nType <= BinaryExpr) {
    free((void *)(node->attr[0]));
    free((void *)(node->attr[2]));
  } else if (node->nType <= FunctionDecl) {
    free((void *)(node->attr[0]));
    free((void *)(node->attr[1]));
    free((void *)(node->attr[2]));
  } else if (node->nType <= FunctionDef) {
    free((void *)(node->attr[0]));
    free((void *)(node->attr[1]));
    free((void *)(node->attr[2]));
    free((void *)(node->attr[3]));
  } else {
    PANIC("unkown type of AST node!");
  }
}

void FreeAST(AST *t) {
  Map(t, FreeAttr, NULL, false);
  free(t->root);
  t->root = NULL;
}

void SpecifyType(ASTNode *node, const char *baseType) {
  if (node == NULL) {
    return;
  }
  if (node->nType != DeclaratorList) {
    PANIC("unexpected AST node type!");
  }
  ASTNode *d = (ASTNode *)(node->attr[1]);
  ASTNode *ts = (ASTNode *)(d->attr[0]);
  const char *t = ts->attr[0];
  ts->attr[0] = AppendStr(baseType, t);
  free((void *)t); // memory leak!!
  SpecifyType((ASTNode *)(node->attr[0]), baseType);
}