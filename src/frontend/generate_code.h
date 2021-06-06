#ifndef GENERATE_OPCODE_H
#define GENERATE_OPCODE_H
#include <stdint.h>

#include "symbol_table.h"

typedef enum {
  IR_FUNCTION,  //* FUNCTION Fn:
  IR_LABEL,     //* LABEL Ln:
  IR_MALLOC,    //* MALLOC xn [SIZE]
  IR_PARAM,     //* PARA xn
  IR_COPY,      //* x <- y
  IR_GOTO,      //* GOTO L
  IR_JUMP_IF,   //* IF x GOTO L
  IR_ARG,       //* ARG x
  IR_CALL,      //* CALL f SIZE
  IR_RETURN,    //* RETURN x
  IR_SCAN,      //* SCAN x
  IR_PRINT,     //* PRINT x
  IR_NOP,  //* do nothing, placeholder
  IR_UOP_BNOT,
  IR_UOP_NOT,
  IR_UOP_MINUS,
  IR_BOP_MUL,
  IR_BOP_DIV,
  IR_BOP_MOD,
  IR_BOP_ADD,
  IR_BOP_SUB,
  IR_BOP_FMUL,
  IR_BOP_FDIV,
  IR_BOP_FADD,
  IR_BOP_FSUB,
  IR_BOP_FLT,
  IR_BOP_FLE,
  IR_BOP_FGT,
  IR_BOP_FGE,
  IR_BOP_FEQ,
  IR_BOP_FNE,
  IR_BOP_LT,
  IR_BOP_LE,
  IR_BOP_GT,
  IR_BOP_GE,
  IR_BOP_EQ,
  IR_BOP_NE,
  IR_BOP_SR,
  IR_BOP_SL,
  IR_BOP_BAND,
  IR_BOP_BOR,
  IR_BOP_BXOR,
  IR_BOP_AND,
  IR_BOP_OR,
} IRType;

typedef struct Instruction {
  IRType type;
  int32_t line;
  const char* attr[3];
} Instruction;

typedef struct IR {
  Instruction** ins;
  Instruction* curI;
  int maxInsCnt;
  int curInsIdx;
} IR;

IR GenerateIR(SymbolTable* st);

#endif