/*
    Production Implementation
    In the production implementation, the routines encapsulate calls to the
    memory-management functions in the standard library in the safer package
    specified by the Mem interface
*/

#include "../include/mem.h"

#include <stdlib.h>  // malloc() & free()
#include <string.h>

#include "../include/assert.h"
#include "../include/except.h"

const struct except_t MemAllocFailed = {"Allocation Failed"};

/*
    All the implementation is simple.
*/

void *MemAlloc(long nbytes, const char *file, int line) {
  ASSERT(nbytes > 0);
  void *ptr = malloc(nbytes);
  if (ptr == NULL) {
    if (file == NULL) {
      RAISE(MemAllocFailed);
    } else {
      ExceptRaise(&MemAllocFailed, file, line);
    }
  }

  memset(ptr, 0, nbytes);
  return ptr;
}

void MemFree(void *ptr, const char *file, int line) {
  if (ptr != NULL) {
    free(ptr);
  }
}

void *MemResize(void *ptr, long nbytes, const char *file, int line) {
  ASSERT(ptr != NULL);
  ASSERT(nbytes > 0);

  ptr = realloc(ptr, nbytes);
  if (ptr == NULL) {
    if (file == NULL) {
      RAISE(MemAllocFailed);
    } else {
      ExceptRaise(&MemAllocFailed, file, line);
    }
  }

  return ptr;
}