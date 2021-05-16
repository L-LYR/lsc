#ifndef MEM_INCLUDE
#define MEM_INCLUDE

#include <stdio.h> // FILE

/*
    MemAlloc:
        1. Accept the size of required memory space and where it is called.
        2. Return the address of allocated memory space.
        3. nbytes > 0
        4. This function will not return a NULL, so is Mem_calloc().
        5. nbytes is not size_t type, but long type. This can avoid errors when
        negative numbers are passed to unsigned arguments, which will be a
        checked runtime error.
*/
extern void *MemAlloc(long nbytes, const char *file, int line);

/*
    MemResize:
        1. Changes the size of the block allocated by a previous call to
        Mem_alloc, Mem_calloc, or Mem_resize.
        2. nbytes > 0
        3. Mem_resize expands or contracts the block so that it holds at
        least nbytes of memory, suitably aligned, and returns a pointer
        to the resized block.
        4. If Mem_resize cannot allocate the new block, it raises Mem_Failed,
        with file and line as the exception coordinates.
*/
extern void *MemResize(void *ptr, long nbytes, const char *file, int line);

/*
    MemFree:
        1. Accept a pointer to allocated space and where it is called.
        2. If ptr is NULL, Mem_free will do nothing.
        3. Mem_free will be packaged by FREE(ptr).
        4. In that implementation, it is a checked runtime error to pass
        Mem_free a nonnull ptr that was not returned by a previous call
        to Mem_alloc, Mem_calloc, or Mem_resize, or a ptr that has already
        been passed to Mem_free or Mem_resize. The values of Mem_free()'s
        file and line arguments are used to report these checked runtime
        errors.
*/
extern void MemFree(void *ptr, const char *file, int line);

#define ALLOC(nbytes) MemAlloc((nbytes), __FILE__, __LINE__)

/*
    When using malloc(), we always write codes like below:
        struct T* p;
        p = (struct T*)malloc(sizeof(struct T));
    In pure C, cast is redundant:
        p = malloc(sizeof(struct T));
    A better version of this idiom is:
        p = malloc(sizeof(*p));
    This can be used for any pointer type. More specifically, it is a template.
    So we get a further capsulation for ALLOC and CALLOC.
*/
#define NEW(p) ((p) = ALLOC((long)sizeof(*(p))))

#define RESIZE(ptr, nbytes)                                                    \
  ((ptr) = MemResize((ptr), (nbytes), __FILE__, __LINE__))

// After being freed, ptr will be set to NULL for avoiding dangling pointers.
#define FREE(ptr) ((void)(MemFree((ptr), __FILE__, __LINE__), (ptr) = 0))

#endif