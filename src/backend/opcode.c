#include <stdlib.h>
#include <string.h>
#include <sys/select.h>
#include <unistd.h>

#include "../exception/exception.h"
#include "vm.h"

Context* _NewContext(Context* cur) {
  Context* c = ALLOC(sizeof(Context));
  memset(c, 0, sizeof(Context));
  c->prev = cur;
  return c;
}

static int64_t _GetVal(VM* vm, Operand* opd) {
  switch (opd->oType) {
    case RegNo:
      if (opd->val == -1) {
        return vm->rv;
      } else {
        return vm->ctx->regs[opd->val];
      }
    case Imm:
    case Addr:
      return opd->val;
    case StkIdx:
      return vm->ctx->baddr[opd->val];
    case gIdx:
      return vm->stack[opd->val];
    default:
      RAISE(Unreachable);
      return 0;
  }
}

static int64_t* _GetRef(VM* vm, Operand* opd) {
  switch (opd->oType) {
    case RegNo:
      return &(vm->ctx->regs[opd->val]);
    case StkIdx:
      return &(vm->ctx->baddr[opd->val]);
    case gIdx:
      return &(vm->stack[opd->val]);
    case Addr:
    case Imm:
      return (int64_t*)opd->val;
    default:
      RAISE(Unreachable);
      return NULL;
  }
}

void vmexit(Instruction* _, VM* vm) {
  ArenaClear();
  AtomReset();
  TableFree(&(vm->constTab));
  FREE(vm->ctx);
  FREE(vm->ins);
  // system("reset");
  exit(vm->rv);
}

void vmmalloc(Instruction* i, VM* vm) {
  int64_t* tar = _GetRef(vm, &(i->opd[0]));
  int64_t size = _GetVal(vm, &(i->opd[1]));
  ASSERT(vm->stkTop == tar);
  *(vm->stkTop++) = (int64_t)ArenaAllocFor(size);
  vm->pc++;
}

void vmvar(Instruction* _, VM* vm) {
  vm->stkTop++;
  vm->pc++;
}
void vmparam(Instruction* _, VM* vm) { vm->pc++; }

void vmcopy(Instruction* i, VM* vm) {
  int64_t* tar = _GetRef(vm, &(i->opd[0]));
  int64_t src = _GetVal(vm, &(i->opd[1]));
  *tar = src;
  vm->pc++;
}

void vmcopytoderef(Instruction* i, VM* vm) {
  int32_t* tar = (int32_t*)_GetVal(vm, &(i->opd[0]));
  int32_t src = (int32_t)_GetVal(vm, &(i->opd[1]));
  *tar = src;
  vm->pc++;
}

void vmcopyfromderef(Instruction* i, VM* vm) {
  int64_t* tar = _GetRef(vm, &(i->opd[0]));
  int32_t* src = (int32_t*)_GetVal(vm, &(i->opd[1]));
  *tar = *src;
  vm->pc++;
}

void vmgoto(Instruction* i, VM* vm) {
  int64_t tar = _GetVal(vm, &(i->opd[0]));
  vm->pc = tar;
}

void vmjumpif(Instruction* i, VM* vm) {
  int64_t cond = _GetVal(vm, &(i->opd[0]));
  int64_t tar = _GetVal(vm, &(i->opd[1]));
  if (cond) {
    vm->pc = tar;
  } else {
    vm->pc++;
  }
}

void vmjumpifnot(Instruction* i, VM* vm) {
  int64_t cond = _GetVal(vm, &(i->opd[0]));
  int64_t tar = _GetVal(vm, &(i->opd[1]));
  if (!cond) {
    vm->pc = tar;
  } else {
    vm->pc++;
  }
}

void vmarg(Instruction* i, VM* vm) {
  int64_t val = _GetVal(vm, &(i->opd[0]));
  *(vm->stkTop++) = val;
  vm->pc++;
}

void vmcall(Instruction* i, VM* vm) {
  int64_t tar = _GetVal(vm, &(i->opd[0]));
  int64_t n = _GetVal(vm, &(i->opd[1]));
  Context* ctx = _NewContext(vm->ctx);
  vm->ctx = ctx;
  ctx->raddr = vm->pc + 1;
  ctx->baddr = vm->stkTop - n;
  vm->pc = tar;
}

void vmreturn(Instruction* i, VM* vm) {
  if (i->opd[0].oType == Dummy) {
    vm->rv = 0;
  } else {
    vm->rv = _GetVal(vm, &(i->opd[0]));
  }
  Context* ctx = vm->ctx;
  vm->ctx = ctx->prev;
  vm->pc = ctx->raddr;
  vm->stkTop = ctx->baddr;
  FREE(ctx);
}
static int _NonBlockGetchar() {
  fd_set rfds;
  struct timeval tv;
  int ch = 0;
  FD_ZERO(&rfds);
  FD_SET(0, &rfds);
  tv.tv_sec = 1;
  tv.tv_usec = 0;
  if (select(1, &rfds, NULL, NULL, &tv) > 0) {
    ch = getchar();
  }
  return ch;
}

void vmscan(Instruction* i, VM* vm) {
  const char* fmt = (const char*)_GetVal(vm, &(i->opd[0]));
  int64_t* val = _GetRef(vm, &(i->opd[1]));
  scanf(fmt, val);
  // usleep(500000);
  // *val = _NonBlockGetchar();
  vm->pc++;
}

void vmprint(Instruction* i, VM* vm) {
  const char* fmt = (const char*)_GetVal(vm, &(i->opd[0]));
  int32_t val = (int32_t)_GetVal(vm, &(i->opd[1]));
  printf(fmt, val);
  vm->pc++;
}

void vmbnot(Instruction* i, VM* vm) {
  int64_t* tar = _GetRef(vm, &(i->opd[0]));
  int32_t l = (int32_t)_GetVal(vm, &(i->opd[1]));
  *tar = ~l;
  vm->pc++;
}

void vmnot(Instruction* i, VM* vm) {
  int64_t* tar = _GetRef(vm, &(i->opd[0]));
  int32_t l = (int32_t)_GetVal(vm, &(i->opd[1]));
  *tar = !l;
  vm->pc++;
}

void vmneg(Instruction* i, VM* vm) {
  int64_t* tar = _GetRef(vm, &(i->opd[0]));
  int32_t l = (int32_t)_GetVal(vm, &(i->opd[1]));
  *tar = -l;
  vm->pc++;
}

void vmfneg(Instruction* i, VM* vm) {
  int64_t* tar = _GetRef(vm, &(i->opd[0]));
  int32_t l = (int32_t)_GetVal(vm, &(i->opd[1]));
  float f = *(float*)&l;
  f = -f;
  l = *(int32_t*)&f;
  *tar = l;
  vm->pc++;
}

void vmmul(Instruction* i, VM* vm) {
  int64_t* tar = _GetRef(vm, &(i->opd[0]));
  int32_t l = (int32_t)_GetVal(vm, &(i->opd[1]));
  int32_t r = (int32_t)_GetVal(vm, &(i->opd[2]));
  *tar = l * r;
  vm->pc++;
}

void vmdiv(Instruction* i, VM* vm) {
  int64_t* tar = _GetRef(vm, &(i->opd[0]));
  int32_t l = (int32_t)_GetVal(vm, &(i->opd[1]));
  int32_t r = (int32_t)_GetVal(vm, &(i->opd[2]));
  *tar = l / r;
  vm->pc++;
}

void vmmod(Instruction* i, VM* vm) {
  int64_t* tar = _GetRef(vm, &(i->opd[0]));
  int32_t l = (int32_t)_GetVal(vm, &(i->opd[1]));
  int32_t r = (int32_t)_GetVal(vm, &(i->opd[2]));
  *tar = l % r;
  vm->pc++;
}

void vmadd(Instruction* i, VM* vm) {
  int64_t* tar = _GetRef(vm, &(i->opd[0]));
  int32_t l = (int32_t)_GetVal(vm, &(i->opd[1]));
  int32_t r = (int32_t)_GetVal(vm, &(i->opd[2]));
  *tar = l + r;
  vm->pc++;
}

void vmsub(Instruction* i, VM* vm) {
  int64_t* tar = _GetRef(vm, &(i->opd[0]));
  int32_t l = (int32_t)_GetVal(vm, &(i->opd[1]));
  int32_t r = (int32_t)_GetVal(vm, &(i->opd[2]));
  *tar = l - r;
  vm->pc++;
}

void vmfmul(Instruction* i, VM* vm) {
  int64_t* tar = _GetRef(vm, &(i->opd[0]));
  int32_t l = (int32_t)_GetVal(vm, &(i->opd[1]));
  int32_t r = (int32_t)_GetVal(vm, &(i->opd[2]));
  float lf = *(float*)&l;
  float rf = *(float*)&r;
  float ans = lf * rf;
  *tar = *(int32_t*)&ans;
  vm->pc++;
}

void vmfdiv(Instruction* i, VM* vm) {
  int64_t* tar = _GetRef(vm, &(i->opd[0]));
  int32_t l = (int32_t)_GetVal(vm, &(i->opd[1]));
  int32_t r = (int32_t)_GetVal(vm, &(i->opd[2]));
  float lf = *(float*)&l;
  float rf = *(float*)&r;
  float ans = lf / rf;
  *tar = *(int32_t*)&ans;
  vm->pc++;
}

void vmfadd(Instruction* i, VM* vm) {
  int64_t* tar = _GetRef(vm, &(i->opd[0]));
  int32_t l = (int32_t)_GetVal(vm, &(i->opd[1]));
  int32_t r = (int32_t)_GetVal(vm, &(i->opd[2]));
  float lf = *(float*)&l;
  float rf = *(float*)&r;
  float ans = lf + rf;
  *tar = *(int32_t*)&ans;
  vm->pc++;
}

void vmfsub(Instruction* i, VM* vm) {
  int64_t* tar = _GetRef(vm, &(i->opd[0]));
  int32_t l = (int32_t)_GetVal(vm, &(i->opd[1]));
  int32_t r = (int32_t)_GetVal(vm, &(i->opd[2]));
  float lf = *(float*)&l;
  float rf = *(float*)&r;
  float ans = lf - rf;
  *tar = *(int32_t*)&ans;
  vm->pc++;
}

void vmflt(Instruction* i, VM* vm) {
  int64_t* tar = _GetRef(vm, &(i->opd[0]));
  int32_t l = (int32_t)_GetVal(vm, &(i->opd[1]));
  int32_t r = (int32_t)_GetVal(vm, &(i->opd[2]));
  float lf = *(float*)&l;
  float rf = *(float*)&r;
  *tar = lf < rf;
  vm->pc++;
}

void vmfle(Instruction* i, VM* vm) {
  int64_t* tar = _GetRef(vm, &(i->opd[0]));
  int32_t l = (int32_t)_GetVal(vm, &(i->opd[1]));
  int32_t r = (int32_t)_GetVal(vm, &(i->opd[2]));
  float lf = *(float*)&l;
  float rf = *(float*)&r;
  *tar = lf <= rf;
  vm->pc++;
}

void vmfgt(Instruction* i, VM* vm) {
  int64_t* tar = _GetRef(vm, &(i->opd[0]));
  int32_t l = (int32_t)_GetVal(vm, &(i->opd[1]));
  int32_t r = (int32_t)_GetVal(vm, &(i->opd[2]));
  float lf = *(float*)&l;
  float rf = *(float*)&r;
  *tar = lf > rf;
  vm->pc++;
}

void vmfge(Instruction* i, VM* vm) {
  int64_t* tar = _GetRef(vm, &(i->opd[0]));
  int32_t l = (int32_t)_GetVal(vm, &(i->opd[1]));
  int32_t r = (int32_t)_GetVal(vm, &(i->opd[2]));
  float lf = *(float*)&l;
  float rf = *(float*)&r;
  *tar = lf >= rf;
  vm->pc++;
}

void vmfeq(Instruction* i, VM* vm) {
  int64_t* tar = _GetRef(vm, &(i->opd[0]));
  int32_t l = (int32_t)_GetVal(vm, &(i->opd[1]));
  int32_t r = (int32_t)_GetVal(vm, &(i->opd[2]));
  float lf = *(float*)&l;
  float rf = *(float*)&r;
  *tar = lf == rf;
  vm->pc++;
}

void vmfne(Instruction* i, VM* vm) {
  int64_t* tar = _GetRef(vm, &(i->opd[0]));
  int32_t l = (int32_t)_GetVal(vm, &(i->opd[1]));
  int32_t r = (int32_t)_GetVal(vm, &(i->opd[2]));
  float lf = *(float*)&l;
  float rf = *(float*)&r;
  *tar = lf != rf;
  vm->pc++;
}

void vmlt(Instruction* i, VM* vm) {
  int64_t* tar = _GetRef(vm, &(i->opd[0]));
  int32_t l = (int32_t)_GetVal(vm, &(i->opd[1]));
  int32_t r = (int32_t)_GetVal(vm, &(i->opd[2]));
  *tar = l < r;
  vm->pc++;
}

void vmle(Instruction* i, VM* vm) {
  int64_t* tar = _GetRef(vm, &(i->opd[0]));
  int32_t l = (int32_t)_GetVal(vm, &(i->opd[1]));
  int32_t r = (int32_t)_GetVal(vm, &(i->opd[2]));
  *tar = l <= r;
  vm->pc++;
}

void vmgt(Instruction* i, VM* vm) {
  int64_t* tar = _GetRef(vm, &(i->opd[0]));
  int32_t l = (int32_t)_GetVal(vm, &(i->opd[1]));
  int32_t r = (int32_t)_GetVal(vm, &(i->opd[2]));
  *tar = l > r;
  vm->pc++;
}

void vmge(Instruction* i, VM* vm) {
  int64_t* tar = _GetRef(vm, &(i->opd[0]));
  int32_t l = (int32_t)_GetVal(vm, &(i->opd[1]));
  int32_t r = (int32_t)_GetVal(vm, &(i->opd[2]));
  *tar = l >= r;
  vm->pc++;
}

void vmeq(Instruction* i, VM* vm) {
  int64_t* tar = _GetRef(vm, &(i->opd[0]));
  int32_t l = (int32_t)_GetVal(vm, &(i->opd[1]));
  int32_t r = (int32_t)_GetVal(vm, &(i->opd[2]));
  *tar = l == r;
  vm->pc++;
}

void vmne(Instruction* i, VM* vm) {
  int64_t* tar = _GetRef(vm, &(i->opd[0]));
  int32_t l = (int32_t)_GetVal(vm, &(i->opd[1]));
  int32_t r = (int32_t)_GetVal(vm, &(i->opd[2]));
  *tar = l != r;
  vm->pc++;
}

void vmsr(Instruction* i, VM* vm) {
  int64_t* tar = _GetRef(vm, &(i->opd[0]));
  int32_t l = (int32_t)_GetVal(vm, &(i->opd[1]));
  int32_t r = (int32_t)_GetVal(vm, &(i->opd[2]));
  *tar = l >> r;
  vm->pc++;
}

void vmsl(Instruction* i, VM* vm) {
  int64_t* tar = _GetRef(vm, &(i->opd[0]));
  int32_t l = (int32_t)_GetVal(vm, &(i->opd[1]));
  int32_t r = (int32_t)_GetVal(vm, &(i->opd[2]));
  *tar = l << r;
  vm->pc++;
}

void vmband(Instruction* i, VM* vm) {
  int64_t* tar = _GetRef(vm, &(i->opd[0]));
  int32_t l = (int32_t)_GetVal(vm, &(i->opd[1]));
  int32_t r = (int32_t)_GetVal(vm, &(i->opd[2]));
  *tar = l & r;
  vm->pc++;
}

void vmbor(Instruction* i, VM* vm) {
  int64_t* tar = _GetRef(vm, &(i->opd[0]));
  int32_t l = (int32_t)_GetVal(vm, &(i->opd[1]));
  int32_t r = (int32_t)_GetVal(vm, &(i->opd[2]));
  *tar = l | r;
  vm->pc++;
}

void vmbxor(Instruction* i, VM* vm) {
  int64_t* tar = _GetRef(vm, &(i->opd[0]));
  int32_t l = (int32_t)_GetVal(vm, &(i->opd[1]));
  int32_t r = (int32_t)_GetVal(vm, &(i->opd[2]));
  *tar = l ^ r;
  vm->pc++;
}

void vmand(Instruction* i, VM* vm) {
  int64_t* tar = _GetRef(vm, &(i->opd[0]));
  int32_t l = (int32_t)_GetVal(vm, &(i->opd[1]));
  int32_t r = (int32_t)_GetVal(vm, &(i->opd[2]));
  *tar = l && r;
  vm->pc++;
}

void vmor(Instruction* i, VM* vm) {
  int64_t* tar = _GetRef(vm, &(i->opd[0]));
  int32_t l = (int32_t)_GetVal(vm, &(i->opd[1]));
  int32_t r = (int32_t)_GetVal(vm, &(i->opd[2]));
  *tar = l || r;
  vm->pc++;
}

Executor ops[] = {
    vmexit,      vmmalloc, vmvar,  vmparam,  vmcopy, vmcopytoderef, vmcopyfromderef, vmgoto, vmjumpif,
    vmjumpifnot, vmarg,    vmcall, vmreturn, vmscan, vmprint,       vmbnot,          vmnot,  vmneg,
    vmfneg,      vmmul,    vmdiv,  vmmod,    vmadd,  vmsub,         vmfmul,          vmfdiv, vmfadd,
    vmfsub,      vmflt,    vmfle,  vmfgt,    vmfge,  vmfeq,         vmfne,           vmlt,   vmle,
    vmgt,        vmge,     vmeq,   vmne,     vmsr,   vmsl,          vmband,          vmbor,  vmbxor,
    vmand,       vmor,
};