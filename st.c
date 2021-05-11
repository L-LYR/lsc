#include "st.h"
#include "panic.h"
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

STNode *NewSTNode(STNodeType t, int nAttr) {
  int nodeSize = sizeof(STNode) + sizeof(void *) * nAttr;
  STNode *r = (STNode *)malloc(nodeSize);
  if (r == NULL) {
    PANIC("bad malloc!");
  }
  r->dummy = '\0';
  r->nType = t;
  r->nAttr = nAttr;
  return r;
}

void AddAttrs(STNode *n, const void *a, ...) {
  va_list as;
  const void *p;
  int i;
  va_start(as, a);
  for (i = 0, p = a; i < n->nAttr; p = va_arg(as, const void *), i++) {
    n->attr[i] = p;
  }
  va_end(as);
}

static const char *TypeNames[] = {
    "program",
    "global list",
    "global declaration or definition",
    "declaration",
    "type specifiers",
    "init declarator list",
    "init declarator",
    "declarator",
    "parameter type list",
    "identifier",
    "initializer",
    "initializer list",
    "function definition",
    "parameter declarator list",
    "parameter declarator",
    "compound statement",
    "loop statement",
    "selection statement",
    "expression statement",
    "io statement",
    "jump statement",
    "statement list",
    "declaration list",
    "statement",
    "expression",
    "assignment expression",
    "unary expression",
    "postfix expression",
    "argument list",
    "logical and expression",
    "logical or expression",
    "bitwise and expression",
    "bitwise or expression",
    "bitwise xor expression",
    "equality expression",
    "relational expression",
    "shift expression",
    "additive expression",
    "multiplicative expression",
    "primary expression",
    "operator",
    "delimiter",
};

static _Bool CheckDummy(const void *p) { return (*(const char *)p) == 0; }

static int UnitIndent = 2;
static void _Display(STNode *node, Fmt *f) {
  if (node == NULL) {
    return;
  }
  fprintf(f->out, "%*s%s\n", f->indent, "", TypeNames[node->nType]);
  f->indent += UnitIndent;
  for (int i = 0; i < node->nAttr; ++i) {
    if (CheckDummy(node->attr[i])) {
      _Display((STNode *)(node->attr[i]), f);
    } else {
      fprintf(f->out, "%*s%s\n", f->indent, "", (const char *)(node->attr[i]));
    }
  }
  f->indent -= UnitIndent;
}

void DisplayST(ST *t, Fmt *f) { _Display(t->root, f); }

static void _Free(STNode *node) {
  if (node == NULL) {
    return;
  }
  for (int i = 0; i < node->nAttr; ++i) {
    if (CheckDummy(node->attr[i])) {
      _Free((STNode *)(node->attr[i]));
    } else {
      free((void *)(node->attr[i]));
    }
  }
  free(node);
}

void FreeST(ST *t) { _Free(t->root); }