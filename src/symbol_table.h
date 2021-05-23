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
typedef Scope *SymbolTable;

typedef enum {
  Global,
  Simple,
  LoopBody,
  FuncBody,
} ScopeType;

struct Scope {
  int level;               // scope level
  const char *name;        // name of scope
  int id;                  // to show the relationship between scopes
  ScopeType sType;         // scope type
  int32_t stkTop;          // stack top
  SymbolTable prev;        // previous layer
  SymbolTable peer;        // peer layer
  SymbolTable next;        // next layer
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
  const char *returnType;
  const char *paraTypeList[0];
} FuncAttr;

typedef struct {
  void *initializer;
  int arrDimNum;
  int *arrDim[0];
} VarAttr;

typedef union {
  FuncAttr *f;
  VarAttr *v;
} AdditionalAttribute;

typedef struct {
  SymbolType sType;  // symbol type
  const char *type;  // specified type
  int32_t address;   // used in IR
  int declLoc;
  AdditionalAttribute aa;
} Attribute;

typedef struct {
  const char *type;
  int dim;  // only use for array type
  _Bool isLvalue;
} ExprAttr;

SymbolTable SymbolTableCreateFromAST(AST *ast);
void FreeSymbolTable(SymbolTable st);

#endif