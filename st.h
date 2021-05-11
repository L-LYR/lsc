#ifndef ST_H
#define ST_H

#include <stdbool.h>
#include <stdio.h>

typedef enum {
  PROGRAM,
  GLOBAL_LIST,
  GLOBAL_DECLARATION_OR_DEFINITION,
  DECLARATION,
  TYPE_SPECIFIERS,
  INIT_DECLARATOR_LIST,
  INIT_DECLARATOR,
  DECLARATOR,
  PARAMETER_TYPE_LIST,
  ID,
  INITIALIZER,
  INITIALIZER_LIST,
  FUNCTION_DEFINITION,
  PARAMETER_DECLARATOR_LIST,
  PARAMETER_DECLARATOR,
  COMPOUND_STATEMENT,
  LOOP_STATEMENT,
  SELECTION_STATEMENT,
  EXPRESSION_STATEMENT,
  IO_STATEMENT,
  JUMP_STATEMENT,
  STATEMENT_LIST,
  DECLARATION_LIST,
  STATEMENT,
  EXPRESSION,
  ASSIGNMENT_EXPRESSION,
  UNARY_EXPRESSION,
  POSTFIX_EXPRESSION,
  ARGUMENT_LIST,
  LOGICAL_AND_EXPRESSION,
  LOGICAL_OR_EXPRESSION,
  BITWISE_AND_EXPRESSION,
  BITWISE_OR_EXPRESSION,
  BITWISE_XOR_EXPRESSION,
  EQUALITY_EXPRESSION,
  RELATIONAL_EXPRESSION,
  SHIFT_EXPRESSION,
  ADDITIVE_EXPRESSION,
  MULTIPLICATIVE_EXPRESSION,
  PRIMARY_EXPRESSION,
  OPERATOR,
  DELIMITER,
} STNodeType;

typedef struct STNode STNode;
typedef struct ST ST;

struct STNode {
  char dummy;          // distinguish STNode* from char*
  STNodeType nType;    // node type
  int nAttr;           // number of attributes
  const void *attr[0]; // attributes
};

struct ST {
  STNode *root;
};

typedef struct {
  int indent;
  FILE *out;
} Fmt;

STNode *NewSTNode(STNodeType t, int nAttr);

void AddAttrs(STNode *n, const void *a, ...);

void DisplayST(ST *t, Fmt *f);

void FreeST(ST *t);

#endif