#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include "../lib/llsc.h"
#include "ast.h"
#include "stdint.h"

void AtomInit(void);

/*
Identifier Item:
    +-----------------+ +---------+------+----------+---------+
    | identifier name | | address | type | decl loc | def loc |
    +-----------------+ +---------+------+----------+---------+
Scope Layer:
    +------------+------------+------------+------------+-------+--------+
    | prev layer | peer layer | next layer | hash table | level | stkTop |
    +------------+------------+------------+------------+-------+--------+
*/

typedef struct Scope Scope;

typedef enum {
  Global,
  Simple,
  LoopBody,
  FuncBody,
} ScopeType;

struct Scope {
  int level;               // scope level
  int id;                  // to show the relationship between scopes
  int32_t stkTop;          // stack top
  ScopeType sType;         // scope type
  const char *name;        // name of scope
  Scope *prev;             // previous layer
  Scope *peer;             // peer layer
  Scope *next;             // next layer
  struct table_t *curTab;  // current table
};

typedef enum {
  Function,
  Variable,
} SymbolType;

typedef struct {
  int defLoc;
  int paraNum;
  _Bool isMain;
  _Bool hasReturnValue;
  ASTNode *defNode;
  const char *returnType;
  const char *paraTypeList[0];
} FuncAttr;

typedef struct {
  void *initializer;
  int arrDimNum;
  int arrDim[0];
} VarAttr;

typedef union {
  FuncAttr *f;
  VarAttr *v;
} AdditionalAttribute;

typedef struct {
  SymbolType sType;  // symbol type
  const char *type;  // specified type
  int32_t address;
  int id;  // the sequence of declaration, global scope will not need this
  int declLoc;
  AdditionalAttribute aa;
} Attribute;

typedef struct {
  const char *type;
  int dim;  // only use for array type
  _Bool isLvalue;
} ExprAttr;

typedef struct Symboltable {
  Scope *s;
  struct table_t *constTable;
} SymbolTable;

SymbolTable *SymbolTableCreateFromAST(AST *ast);
void FreeSymbolTable(SymbolTable *st);

#endif