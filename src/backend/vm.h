#ifndef VM_H
#define VM_H
#include <stdint.h>

#include "../lib/llsc.h"

#define MaxRegsNum 64
#define MaxStackDepth 65536

typedef enum InsType {
  EXIT,
  MALLOC,
  VAR,
  PARAM,
  COPY,
  COPY_TO_DEREF,
  COPY_FROM_DEREF,
  GOTO,
  JUMP_IF,
  JUMP_IF_NOT,
  ARG,
  CALL,
  RETURN,
  SCAN,
  PRINT,
  BNOT,
  NOT,
  NEG,
  FNEG,
  MUL,
  DIV,
  MOD,
  ADD,
  SUB,
  FMUL,
  FDIV,
  FADD,
  FSUB,
  FLT,
  FLE,
  FGT,
  FGE,
  FEQ,
  FNE,
  LT,
  LE,
  GT,
  GE,
  EQ,
  NE,
  SR,
  SL,
  BAND,
  BOR,
  BXOR,
  AND,
  OR,
} InsType;

typedef enum {
  Dummy,
  Imm,
  Addr,
  StkIdx,
  RegNo,
} OperandType;

typedef struct Operand {
  OperandType oType;
  int64_t val;
} Operand;

typedef struct Instruction {
  InsType iType;
  Operand opd[3];
} Instruction;

typedef struct Context {
  int64_t raddr;             // return address
  int64_t* baddr;            // base address of data stack
  int64_t regs[MaxRegsNum];  // register file
  struct Context* prev;
} Context;

typedef struct VM {
  int64_t pc;  // program counter
  int64_t rv;  // return value
  int64_t* stkTop;
  Context* ctx;
  int64_t stack[MaxStackDepth];
  struct table_t* constTab;
  Instruction* ins;
} VM;

typedef void (*Executor)(Instruction* i, VM*);

void Run(FILE* f, FILE* b);

typedef struct {
  int begin;
  int end;
} BasicBlock;

#endif