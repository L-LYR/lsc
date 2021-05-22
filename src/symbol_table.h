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
} FuncDefAttr;

typedef struct {
  void *initializer;
  int arrDimNum;
  int *arrDim[0];
} VarDeclAttr;

typedef union {
  FuncDefAttr *f;
  VarDeclAttr *v;
} AdditionalAttribute;

typedef struct {
  SymbolType sType;  // symbol type
  const char *type;  // specified type
  int32_t address;   // used in IR
  int declLoc;
  AdditionalAttribute aa;
} Attribute;

SymbolTable SymbolTableCreateFromAST(AST *ast);
void DisplaySymbolTable(SymbolTable st, Fmt *fmt);
void FreeSymbolTable(SymbolTable st);

#endif