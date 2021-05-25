#ifndef DISPLAY_H
#define DISPLAY_H

#include "symbol_table.h"

typedef struct {
  int depth;
  FILE *out;
  const char *fileLoc;
} Fmt;

#define RED "\x1B[31m"
#define GRN "\x1B[32m"
#define YEL "\x1B[33m"
#define BLU "\x1B[34m"
#define MAG "\x1B[35m"
#define CYN "\x1B[36m"
#define WHT "\x1B[37m"
#define RESET "\x1B[0m"

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
void _NotifyUndefinedReference(int curLine, const char *id);
void _NotifyInvalidArgumentType(int curLine, const char *type, const char *what, const char *detail);
void _NotifyUnassignable(int curLine);
void _NotifyUnsubscriptable(int curLine);
void _NotifyNonIntegerSubscript(int curLine);
void _NotifyTypeUnmatch(int curLine, const char *lType, const char *rType, const char *op);
void _NotifyTypeUnmatchInitializer(int curLine, const char *want, const char *get);
void _NotifyUncallable(int curLine, const char *id, const char *type);
void _NotifyFuncCallUnmatch(int curLine, const char *want, const char *get, int i);
void _NotifyParaNumberUnmatch(int curLine, const char *id, int want, int get);
void _NotifyConditionExprNeedBoolType(int curLine);
void _NotifyReturnTypeUnmatch(int curLine, const char *want, const char *get, const char *id);
void _NotifyIOStmMustGetBaseType(int curLine, const char *get);
void _NotifyAssignmentBetweenArray(int curLine);
void _NotifyArrayInitializerOnBaseType(int curLine);
void _NotifyExpectArrayInitializer(int curLine);
void _NotifyArrayInitializerDimUnmatch(int curLine, int want, int get);
void _NotifyNoMainFunction(int curLine);

void _NotifyRepetition(Attribute *old, Attribute *new, const char *id);
void _PauseForDisplay();

// external
void DisplayAST(AST *t, Fmt *fmt);
void DisplaySymbolTable(SymbolTable st, Fmt *fmt);

#endif