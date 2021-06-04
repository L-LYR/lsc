#include "../include/stack.h"

#include "../include/assert.h"
#include "../include/mem.h"

struct stack_t *StackCreate(void) {
  struct stack_t *stk;
  NEW(stk);
  stk->count = 0;
  stk->head = NULL;
  return stk;
}

_Bool StackEmpty(const struct stack_t *stk) {
  ASSERT(stk != NULL);
  return stk->count == 0;
}

void StackPush(struct stack_t *stk, void *x) {
  struct elem *t;
  ASSERT(stk != NULL);
  NEW(t);
  t->x = x;
  t->link = stk->head;
  stk->head = t;
  stk->count++;
}

void *StackPop(struct stack_t *stk) {
  void *x;
  struct elem *t;
  ASSERT(stk != NULL);
  ASSERT(stk->count > 0);
  t = stk->head;
  stk->head = t->link;
  stk->count--;
  x = t->x;
  FREE(t);

  return x;
}
void *StackTop(const struct stack_t *stk) {
  ASSERT(stk != NULL);
  ASSERT(!StackEmpty(stk));
  return stk->head->x;
}
void StackFree(struct stack_t **stkp) {
  struct elem *t, *u;
  ASSERT(stkp != NULL);
  ASSERT(*stkp != NULL);
  for (t = (*stkp)->head; t != NULL; t = u) {
    u = t->link;
    FREE(t);
  }
  FREE(*stkp);
}