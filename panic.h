#ifndef PANIC_H
#define PANIC_H

#include <stdlib.h>

#define PANIC(str)                                                             \
  do {                                                                         \
    fprintf(stderr, "File %s Line %d: %s\n", __FILE__, __LINE__, str);         \
    exit(-1);                                                                  \
  } while (0)

#define NOTIFY(str)                                                            \
  do {                                                                         \
    fprintf(stdout, "%s", str);                                                \
    exit(0);                                                                   \
  } while (0)

#endif