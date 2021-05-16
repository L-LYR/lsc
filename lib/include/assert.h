/*
    This implementation is similar to the C standard library assert.h.
*/

#undef ASSERT
#ifdef NDEBUG
#define ASSERT(e) ((void)0);
#else
#include "except.h"
extern void ASSERT(int e);
#define ASSERT(e) ((void)((e) || (RAISE(assert_failed), 0)))

// terminate the process with exit code 0.
// inform the user about the correct usage.
#define notify(str)                                                            \
  do {                                                                         \
    fprintf(stdout, "%s", str);                                                \
    exit(0);                                                                   \
  } while (0)

#endif