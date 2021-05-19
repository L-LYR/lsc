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
struct Scope {
  int level;
  int id;
  int32_t stkTop;         // stack top
  SymbolTable prev;       // previous layer
  SymbolTable peer;       // peer layer
  SymbolTable next;       // next layer
  struct table_t *curTab; // current table
};

typedef struct {
  const char *type; // specified type
  const char *init; // initializer be NULL
  int32_t address;  // used in IR
  int declLoc;
  int defLoc;
} Attribute;

SymbolTable SymbolTableCreateFromAST(AST *ast);
void DisplaySymbolTable(SymbolTable st, Fmt *fmt);
void FreeSymbolTable(SymbolTable st);

#endif