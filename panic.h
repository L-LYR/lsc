#ifndef PANIC_H
#define PANIC_H

#include <stdlib.h>

// terminate the process with exit code -1.
// infom the user about the error info and location.
#define PANIC(str)                                                             \
  do {                                                                         \
    fprintf(stderr, "File %s Line %d: %s\n", __FILE__, __LINE__, str);         \
    exit(-1);                                                                  \
  } while (0)

// terminate the process with exit code 0.
// inform the user about the correct usage.
#define NOTIFY(str)                                                            \
  do {                                                                         \
    fprintf(stdout, "%s", str);                                                \
    exit(0);                                                                   \
  } while (0)

#endif