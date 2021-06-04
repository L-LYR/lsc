#ifndef STACK_INCLUDED
#define STACK_INCLUDED

#include <stdbool.h>
struct elem {
  void *x;
  struct elem *link;
};

struct stack_t {
  int count;
  struct elem *head;
};

extern struct stack_t *StackCreate(void);
extern _Bool StackEmpty(const struct stack_t *stk);
extern void *StackTop(const struct stack_t *stk);
extern void StackPush(struct stack_t *stk, void *x);
extern void *StackPop(struct stack_t *stk);
extern void StackFree(struct stack_t **stk);

#endif