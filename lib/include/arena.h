#ifndef ARENA_INCLUDE
#define ARENA_INCLUDE

extern void ArenaInit(void);
extern void ArenaFree(void);
extern void ArenaClear(void);
extern void *ArenaAlloc(long nbytes, const char *file, int line);
extern void *ArenaCalloc(long count, long nbytes, const char *file, int line);

#define ArenaAllocFor(nbytes) ArenaAlloc((nbytes), __FILE__, __LINE__)
#define ArenaCallocFor(count, nbytes) ArenaCalloc((count), (nbytes), __FILE__, __LINE__)

#endif