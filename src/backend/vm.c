#include "vm.h"

#include <stdlib.h>

// extern reader.c
int Read(VM* vm, FILE* f);
// extern optimize.c
void Optimize(Instruction* ins, int cnt, FILE* b);
// extern opcode.c
Context* _NewContext(Context* cur);

extern Executor ops[];

static void _ExecLoop(VM* vm) {
  // system("stty raw -echo");
  Instruction* i;
  vm->ctx = _NewContext(vm->ctx);
  while (true) {
    i = &(vm->ins[vm->pc]);
    ops[i->iType](i, vm);
  }
}

void Run(FILE* f, FILE* b) {
  VM vm;
  ArenaInit();
  int cnt = Read(&vm, f);
  fclose(f);
  Optimize(vm.ins, cnt, b);
  vm.pc = 0;
  vm.stkTop = vm.stack;
  _ExecLoop(&vm);
}