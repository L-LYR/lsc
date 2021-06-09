#include "../include/arena.h"

#include <stdlib.h>  // malloc() & free()
#include <string.h>  // memset()

#include "../include/align.h"
#include "../include/assert.h"
#include "../include/except.h"

// extra size for new chunk
#define NEW_CHUNK_EXTRA_SIZE 10240

// threshold for free chunk list
#define THRESHOLD 10
// Make sure that arena->avail is set to a properly
// aligned address for the first allocation in this
// new chunk.

struct arena_t {
  struct arena_t *prev;  // previous chunk
  char *avail;           // begin of chunk
  char *limit;           // end of the chunk
};

union header {
  struct arena_t a;
  union align dummy;
};

static struct arena_t *GlobalAllocator;
// free chunk list
static struct arena_t *FreeChunkList = NULL;
static int NFree = 0;

static const struct except_t ArenaNewFailed = {"Arena Creation Failed"};

static const struct except_t ArenaFailed = {"Arena Allocation Failed"};

static struct arena_t *ArenaNew(void) {
  struct arena_t *arena = malloc(sizeof(*arena));
  if (arena == NULL) RAISE(ArenaNewFailed);
  arena->prev = NULL;
  arena->avail = arena->limit = NULL;
  return arena;
}

static void *ArenaAllocImpl(struct arena_t *arena, long nbytes, const char *file, int line) {
  ASSERT(arena != NULL);
  ASSERT(nbytes > 0);

  nbytes = ROUND_UP_TO_ALIGN_BOUND(nbytes);

  // original version

  while (nbytes > (arena->limit - arena->avail)) {
    // get a new chunk
    struct arena_t *newArena = FreeChunkList;
    char *limit;

    if (newArena != NULL) {
      FreeChunkList = FreeChunkList->prev;
      NFree--;
      limit = newArena->limit;
    } else {
      long m = sizeof(union header) + nbytes + NEW_CHUNK_EXTRA_SIZE;
      newArena = malloc(m);
      memset(newArena, 0, m);
      if (newArena == NULL) {
        if (file == NULL)
          RAISE(ArenaFailed);
        else
          ExceptRaise(&ArenaFailed, file, line);
      }
      limit = (char *)newArena + m;
    }

    *newArena = *arena;
    arena->avail = (char *)((union header *)newArena + 1);
    arena->limit = limit;
    arena->prev = newArena;
  }

  arena->avail += nbytes;
  return (arena->avail - nbytes);
}

static void *ArenaCallocImpl(struct arena_t *arena, long count, long nbytes, const char *file, int line) {
  ASSERT(count > 0);
  ASSERT(nbytes > 0);
  void *ptr = ArenaAllocImpl(arena, count * nbytes, file, line);
  memset(ptr, 0, count * nbytes);
  return ptr;
}

static void ArenaCollectImpl(struct arena_t *arena) {
  ASSERT(arena != NULL);
  struct arena_t tmp;
  while (arena->prev != NULL) {
    tmp = *(arena->prev);
    if (NFree < THRESHOLD) {
      arena->prev->prev = FreeChunkList;
      FreeChunkList = arena->prev;
      NFree++;
      FreeChunkList->limit = arena->limit;
    } else
      free(arena->prev);
    *arena = tmp;
  }
  ASSERT(arena->limit == NULL);
  ASSERT(arena->avail == NULL);
}

static void ArenaDisposeImpl(struct arena_t **ap) {
  ASSERT(ap && *ap);
  ArenaCollectImpl(*ap);
  free(*ap);
  *ap = NULL;
}

static void ArenaClearImpl() {
  struct arena_t *tmp, *ap;
  ap = FreeChunkList;
  while (ap != NULL) {
    tmp = ap->prev;
    free(ap);
    ap = tmp;
  }
  FreeChunkList = NULL;
  NFree = 0;
}

void ArenaInit() { GlobalAllocator = ArenaNew(); }

void ArenaFree() { ArenaDisposeImpl(&(GlobalAllocator)); }

void ArenaClear() {
  ArenaFree();
  ArenaClearImpl();
}

void *ArenaAlloc(long nbytes, const char *file, int line) {
  return ArenaAllocImpl(GlobalAllocator, nbytes, file, line);
}

void *ArenaCalloc(long count, long nbytes, const char *file, int line) {
  return ArenaCallocImpl(GlobalAllocator, count, nbytes, file, line);
}