#include <stdlib.h>
#include <string.h>

#include "../exception/exception.h"
#include "vm.h"

static const char* InsNameInit[] = {
    "exit",
    "malloc",
    "var",
    "param",
    "copy",
    "copy_to_deref",
    "copy_from_deref",
    "goto",
    "jump_if",
    "jump_if_not",
    "arg",
    "call",
    "return",
    "scan",
    "print",
    "bnot",
    "not",
    "neg",
    "fneg",
    "mul",
    "div",
    "mod",
    "add",
    "sub",
    "fmul",
    "fdiv",
    "fadd",
    "fsub",
    "flt",
    "fle",
    "fgt",
    "fge",
    "feq",
    "fne",
    "lt",
    "le",
    "gt",
    "ge",
    "eq",
    "ne",
    "sr",
    "sl",
    "band",
    "bor",
    "bxor",
    "and",
    "or",
};

static const int InsTypeNum = sizeof(InsNameInit) / sizeof(InsNameInit[0]);
static const char* InsTypeName[InsTypeNum];
static const int DefaultTableSize = 128;
static struct table_t* ConstTab;
static struct table_t* LabelTab;
static const int LineBufferSize = 65536;
static char LineBuffer[LineBufferSize];

static void _Init() {
  InsType t = EXIT;
  int i = 0;
  while (i < InsTypeNum) {
    InsTypeName[t++] = AtomString(InsNameInit[i++]);
  }
  ConstTab = TableCreate(DefaultTableSize, (equal_t)AtomEqual, (hash_t)AtomHash);
  LabelTab = TableCreate(DefaultTableSize, (equal_t)AtomEqual, (hash_t)AtomHash);
}

static InsType _GetInsType(const char* s) {
  InsType t = EXIT;
  const char* tar = AtomString(s);
  while (InsTypeName[t] != tar) {
    t++;
  }
  if (t == InsTypeNum) {
    return -1;
  }
  return t;
}

static void _ConvertEscapeChar(char* p) {
  char* q = p;
  while (*p != '\0') {
    if (*p != '\\') {
      *q++ = *p++;
    } else {
      p++;
      switch (*p++) {
        case '\\':
          *q++ = '\\';
          break;
        case 'n':
          *q++ = '\n';
          break;
        case 't':
          *q++ = '\t';
          break;
        case 'f':
          *q++ = '\f';
          break;
        case 'v':
          *q++ = '\v';
          break;
        case 'r':
          *q++ = '\r';
          break;
      }
    }
  }
  *q = '\0';
}

static int _ReadLine(FILE* f) {
  if (fgets(LineBuffer, LineBufferSize - 1, f) == NULL) {
    if (feof(f)) {
      return -1;
    }
    if (ferror(f)) {
      RAISE(FileReadError);
    }
  }
  int len = strlen(LineBuffer);
  if (LineBuffer[len - 1] != '\n' && len == LineBufferSize - 1) {
    RAISE(BufferOverflow);
  }
  LineBuffer[len - 1] = '\0';
  return len - 1;
}

static void _ReadDateSeg(FILE* f) {
  if (_ReadLine(f) == -1) {
    RAISE(UnexpectedEOF);
  }
  if (strncmp(LineBuffer, ".data", 5) != 0) {
    RAISE(UnknownSegment);
  }
  char* p;
  int eIdx;
  while (true) {
    eIdx = _ReadLine(f);
    if (eIdx <= 0) {
      break;
    }
    p = LineBuffer;
    while (*p != ',') {
      p++;
    }
    if (*p != ',' || *(p + 1) != '"' || LineBuffer[eIdx - 1] != '"') {
      RAISE(UnexpectedDelim);
    }
    LineBuffer[eIdx - 1] = *(p + 1) = *p = '\0';
    p += 2;
    _ConvertEscapeChar(p);
    TablePut(ConstTab, AtomString(LineBuffer), (void*)AtomString(p));
  }
}

static void _SetAttr(Instruction* i, int j, const char* a) {
  if (a == NULL) {
    return;
  }
  switch (*a) {
    case 't':
      i->opd[j].oType = RegNo;
      i->opd[j].val = strtol(a + 1, NULL, 10);
      break;
    case 'x':
      i->opd[j].oType = StkIdx;
      i->opd[j].val = strtol(a + 1, NULL, 10);
      break;
    case 's':
      i->opd[j].oType = Addr;
      i->opd[j].val = (int64_t)TableGet(ConstTab, AtomString(a));
      break;
    case '0':
      i->opd[j].oType = Imm;
      i->opd[j].val = strtol(a, NULL, 16);
      break;
    case 'r':
      i->opd[j].oType = RegNo;
      i->opd[j].val = -1;
      break;
    default:
      i->opd[j].val = (int64_t)AtomString(a);
      i->opd[j].oType = Dummy;
  }
}

static Instruction* _ReadCodeSeg(FILE* f) {
  if (_ReadLine(f) == -1) {
    RAISE(UnexpectedEOF);
  }
  if (strncmp(LineBuffer, ".text", 5) != 0) {
    RAISE(UnknownSegment);
  }
  int eIdx;
  int insNum = 0;
  int maxInsNum = 0;
#define InsArrIncSize 64
  Instruction* ins = NULL;
  char *p = NULL, *q = NULL;
  while (true) {
    eIdx = _ReadLine(f);
    if (eIdx == 0) {  // empty line
      continue;
    }
    if (eIdx == -1) {  // EOF
      break;
    }
    p = LineBuffer;
    if (strncmp(p, "label", 5) == 0) {
      TablePut(LabelTab, AtomString(p + 6), (void*)(int64_t)(insNum));
    } else if (strncmp(p, "function", 8) == 0) {
      TablePut(LabelTab, AtomString(p + 9), (void*)(int64_t)(insNum));
    } else {
      if (insNum >= maxInsNum) {
        maxInsNum += InsArrIncSize;
        RESIZE(ins, maxInsNum * sizeof(Instruction));
        memset(&ins[insNum], 0, sizeof(Instruction) * InsArrIncSize);
      }
      q = strtok(p + 2, " ");
      if ((ins[insNum].iType = _GetInsType(q)) < EXIT) {
        RAISE(UnknownInsType);
      }
      for (int i = 0; i < 3; ++i) {
        q = strtok(NULL, " ");
        _SetAttr(&ins[insNum], i, q);
      }
      insNum++;
    }
  }
  for (int i = 0; i < insNum; ++i) {
    switch (ins[i].iType) {
      case CALL:
      case GOTO:
        ins[i].opd[0].val = (int64_t)(TableGet(LabelTab, (void*)ins[i].opd[0].val));
        ins[i].opd[0].oType = Imm;
        break;
      case JUMP_IF:
      case JUMP_IF_NOT:
        ins[i].opd[1].val = (int64_t)(TableGet(LabelTab, (void*)ins[i].opd[1].val));
        ins[i].opd[1].oType = Imm;
        break;
      default:
        continue;  // do nothing
    }
  }
  TableFree(&LabelTab);
  return ins;
}

void Read(VM* vm, FILE* f) {
  _Init();
  _ReadDateSeg(f);
  vm->ins = _ReadCodeSeg(f);
  vm->constTab = ConstTab;
}