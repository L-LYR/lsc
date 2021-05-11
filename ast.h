#ifndef AST_H
#define AST_H

#include <stdbool.h>
#include <stdio.h>

typedef enum {
  // all kinds of constant will be treated
  // as a string in syntax analysis
  BoolConst,        // [0]const char*
  IntConst,         // [0]const char*
  FloatConst,       // [0]const char*
  StrConst,         // [0]const char*
  Identifier,       // [0]const char*
  TypeSpecifier,    // [0]const char*
  Initializer,      // [0]expression
  ExpressionStm,    // [0]expression
  ArrayInitializer, // [0]initializer list
  // Identifiers will be temporarily treated as strings.

  IOStm,               // [0]const char* IO [1]arguement list
  JumpStm,             // [0]const char* keyword [1]expression
  UnaryExpr,           // [0]const char* operator [1]expression
  FunctionCall,        // [0]identifier [1]arguement list
  ParameterDecl,       // [0]type specifier [1]identifier
  Declaration,         // [0]base type [1]declarator list
  CompoundStm,         // [0]declaration list [1]statement list
  ArguementList,       // [0]next [1]expression
  DeclarationList,     // [0]next [1]declaration
  StatementList,       // [0]next [1]statement
  DeclaratorList,      // [0]next [1]declarator
  InitializerList,     // [0]next [1]initializer
  GlobalDeclOrDefList, // [0]next [1]declaration or function definition
  ParameterDeclList,   // [0]next [1]parameter declarator
  ParameterTypeList,   // [0]next [1]type specifier

  PostfixExpr,  // [0]expression [1]const char* operator [2]expression
  BinaryExpr,   // [0]expression [1]const char* operator [2]expression
  SelectionStm, // [0]condition expression [1]branch1 [2]branch2
  Declarator,   // [0]type specifier [1]identifier [2]initializer
  FunctionDecl, // [0]return type [1]identifier [2]parameter list

  LoopStm,     // [0]init [1]condition [2]inc [3]loop body
  FunctionDef, // [0]const char* return type [1]identifier
               // [2]parameter decl list [3]compound statement
} ASTNodeType;

typedef struct ASTNode ASTNode;
typedef struct AST AST;

struct ASTNode {
  ASTNodeType nType;   // node type
  const void *attr[0]; // attribute
};

struct AST {
  ASTNode *root;
};

/*
  Create an AST node corresponding to the given type.
*/

ASTNode *NewASTNode(ASTNodeType t);

/*
  Apply the mapper on each node in AST.
  cl means closure.
  cl can be NULL or a struct pointer.
  The struct's first field must be an integer named depth.
*/

typedef void (*mapper)(ASTNode *, void *);
void Map(AST *t, mapper m, void *cl, _Bool topDown);

/*
  Printer is a mapper, which prints the AST Node.
  cl should be a Fmt pointer, which controls the indent and redirection.
*/

typedef struct {
  int depth;
  FILE *out;
} Fmt;

void Printer(ASTNode *node, void *cl);
void DisplayAST(AST *t, Fmt *fmt);

/*
  FreeAttr is a mapper, which free each AST Node.
  cl should be NULL, because it will not be used;
*/

void FreeAttr(ASTNode *node, void *cl);
void FreeAST(AST *t);

/*
  SpecifyType will only be called in the declaration action.
*/

void SpecifyType(ASTNode *node, const char *baseType);

#endif