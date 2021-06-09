#include "vm.h"

// extern reader.c
void Read(VM* vm, FILE* f);

extern Executor ops[];

static void _ExecLoop(VM* vm) {
  Instruction* i;
  while (true) {
    i = &(vm->ins[vm->pc]);
    ops[i->iType](i, vm);
  }
}

void Run(FILE* f) {
  VM vm;
  ArenaInit();
  Read(&vm, f);
  fclose(f);
  vm.pc = 0;
  vm.stkTop = vm.stack;
  _ExecLoop(&vm);
}