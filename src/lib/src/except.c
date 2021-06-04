#include "../include/except.h"

#include <stdio.h>   // fprintf() & stderr & fflush()
#include <stdlib.h>  // abort()

#include "../include/assert.h"

struct ExceptFrame *ExceptStack = NULL;

void ExceptRaise(const struct except_t *e, const char *file, int line) {
  struct ExceptFrame *p = ExceptStack;
  ASSERT(e);
  if (p == NULL) {
    /*
        If clients don’t handle Assert_Failed, then an assertion failure
        causes the program to abort with a message like
            Uncaught exception Assertion failed raised at stmt.c:201
            aborting...
        which is functionally equivalent to the diagnostics issued by
        machine-specific versions of assert.h.
    */
    fprintf(stderr, "Uncaught exception: ");
    if (e->reason)
      fprintf(stderr, "%s", e->reason);
    else
      fprintf(stderr, " at 0x%p", e);
    if (file != NULL && line > 0) fprintf(stderr, " raised at %s:%d\n", file, line);
    fprintf(stderr, "aborting...\n");
    fflush(stderr);
    abort();
  }
  p->exception = e;
  p->file = file;
  p->line = line;
  ExceptStack = ExceptStack->prev;
  longjmp(p->env, EXCEPT_RAISED);
}