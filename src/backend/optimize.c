#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../lib/llsc.h"
#include "vm.h"

// extern reader.c
extern const char *InsTypeName[];

static const Instruction *InnerIns;
static int InsCnt = 0;

static int *BBNoArr = NULL;
static BasicBlock *BBs = NULL;
static int BBCnt = 0;

const char *OperandTypeStr[] = {
    "", "Imm", "Addr", "StkIdx", "GlobalIdx", "RegNo",
};

static void _ShowOperand(const Instruction *ins, FILE *b) {
  for (int i = 0; i < 3; ++i) {
    if (ins->opd[i].oType == Dummy) {
      return;
    }
    fprintf(b, " %s", OperandTypeStr[ins->opd[i].oType]);
    switch (ins->opd[i].oType) {
      case Imm:
      case Addr:
        // fprintf(b, "(0x%X)", (int32_t)(ins->opd[i].val));
        // break;
      case StkIdx:
      case gIdx:
      case RegNo:
        fprintf(b, "(%ld)", ins->opd[i].val);
        break;
      default:
        return;
    }
  }
}

static void _GenerateBBs(FILE *b) {
  int arrSize = sizeof(_Bool) * (InsCnt + 1);
  _Bool *isBegin = ALLOC(arrSize);
  _Bool *isEnd = ALLOC(arrSize);
  memset(isBegin, 0, arrSize);
  memset(isEnd, 0, arrSize);
  isBegin[0] = true;
  for (int i = 0; i < InsCnt; ++i) {
    if (InnerIns[i].iType == CALL || InnerIns[i].iType == GOTO) {
      isBegin[InnerIns[i].opd[0].val] = true;
      isBegin[i + 1] = true;
      isEnd[i] = true;
    } else if (InnerIns[i].iType == JUMP_IF || InnerIns[i].iType == JUMP_IF_NOT) {
      isBegin[InnerIns[i].opd[1].val] = true;
      isBegin[i + 1] = true;
      isEnd[i] = true;
    } else if (InnerIns[i].iType == EXIT || InnerIns[i].iType == RETURN) {
      //   isBegin[i] = true;
      isEnd[i] = true;
      isBegin[i + 1] = true;
    }
  }

  int i = 0;
  while (i < InsCnt) {
    if (isBegin[i]) {
      // find end
      int j;
      for (j = i; j < InsCnt; ++j) {
        if (isEnd[j]) {
          break;
        }
      }
      fprintf(b, "\ts%d:BB%d[%d,%d]\\n", BBCnt, BBCnt, i, j);
      while (i <= j) {
        fprintf(b, "%d %s", i, InsTypeName[InnerIns[i].iType]);
        _ShowOperand(&InnerIns[i], b);
        fprintf(b, "\\n");
        BBNoArr[i] = BBCnt;
        i++;
      }
      fprintf(b, "\n");

      BBCnt++;
    } else {
      i++;
    }
  }

  FREE(isBegin);
  FREE(isEnd);
}

void _GenerateDFG(FILE *b) {
  BBs = ALLOC(sizeof(BasicBlock) * BBCnt);
  int last = 0;
  int from, to;
  for (int i = 0; i < InsCnt; ++i) {
    int cur = BBNoArr[i];
    if (last != cur) {
      BBs[last].end = i - 1;
      BBs[cur].begin = i;
      if (InnerIns[i - 1].iType != EXIT && InnerIns[i - 1].iType != RETURN) {
        fprintf(b, "\ts%d --> s%d\n", last, cur);
      }
      last = cur;
    }
    if (InnerIns[i].iType == CALL || InnerIns[i].iType == GOTO) {
      from = BBNoArr[i];
      to = BBNoArr[InnerIns[i].opd[0].val];
      fprintf(b, "\ts%d --> s%d\n", from, to);
    } else if (InnerIns[i].iType == JUMP_IF || InnerIns[i].iType == JUMP_IF_NOT) {
      from = BBNoArr[i];
      to = BBNoArr[InnerIns[i].opd[1].val];
      fprintf(b, "\ts%d --> s%d\n", from, to);
    } else if (InnerIns[i].iType == EXIT || InnerIns[i].iType == RETURN) {
    }
  }
  BBs[last].end = InsCnt - 1;
}

void Optimize(Instruction *ins, int cnt, FILE *b) {
  InnerIns = ins;
  InsCnt = cnt;
  BBNoArr = ALLOC(sizeof(int) * InsCnt);
  fprintf(b, "```mermaid\nstateDiagram-v2\n");
  _GenerateBBs(b);
  _GenerateDFG(b);
  fprintf(b, "```\n");

  FREE(BBNoArr);
  FREE(BBs);
  fclose(b);
}
