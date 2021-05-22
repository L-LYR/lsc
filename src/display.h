#ifndef DISPLAY_H
#define DISPLAY_H

#include "symbol_table.h"

typedef struct {
  int depth;
  FILE *out;
  const char *fileLoc;
} Fmt;

// internal
void _Notify(const char *fmtStr, ...);
void _NotifyRedeclaration(int curLine, const char *id, SymbolType declareType, int declareLine);
void _NotifyRedefinition(int curLine, const char *id, SymbolType defineType, int defineLine);
void _NotifyTypeConflict(int curLine, const char *id, const char *tNew, const char *tOld, int declareLine);
void _NotifyInvalidLocOfJumpStm(int curLine, const char *stm, const char *loc);
void _NotifyWrongReturnStm(int curLine, const char *id, _Bool needReturn);
void _NotifyInvalidTypeOfVar(int curLine, const char *id, const char *type);
void _NotifyArrayDimTooBig(int curLine, const char *id, int dim, int lim);
void _NotifyInvalidArrayDim(int curLine);
void _NotifyRepetition(Attribute *old, Attribute *new, const char *id);
void _PauseForDisplay();

// external
void DisplayAST(AST *t, Fmt *fmt);
void DisplaySymbolTable(SymbolTable st, Fmt *fmt);

#endif