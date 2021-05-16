#include "../include/atom.h"

#include <limits.h> // LONG_MAX & LONG_MIN
#include <stdarg.h> // va_list & va_start() & va_end() & va_arg()
#include <string.h> // strcmp() & strlen() & memset()

#include "../include/assert.h"
#include "../include/mem.h"

// size of the atom bucket
#define ATOM_BUCKET_SIZE 2039
#define ATOM_BUCKET_DEFAULT_CAPCITY ATOM_BUCKET_SIZE

// BKDR hash function seed
// 31 131 1313 13131 131313 etc..
#define BKDR_HASH_SEED 131

struct atom {
  struct atom *link; // pointer to the next atom
  int len;           // length of byte sequence
  // char *str;
  // here use flexible array members (C99)
  char str[]; // byte sequence (always string)
              // struct atom *p = malloc(sizeof(*p) + len + 1);
};

// bucket is an array of pointers tol lists of entries,
// which holds one atom.
static struct atom *Bucket[ATOM_BUCKET_SIZE];

// capacity of atom table
static int Capacity = ATOM_BUCKET_DEFAULT_CAPCITY;

// current size of atom table
static int Size = 0;

static unsigned long AtomHash(const char *str) {
  ASSERT(str != NULL);
  unsigned long h = 0;
  for (int i = 0; str[i] != '\0'; i++) {
    h = h * BKDR_HASH_SEED + str[i];
  }

  return h;
}

/*
    AtomFind:
        1. Find where is the atom given by str.
        2. If found, return the respective atom pointer;
        if not, return NULL.
*/
static struct atom *AtomFind(const char *str, unsigned long h) {
  for (struct atom *p = Bucket[h]; p != NULL; p = p->link) {
    if (p->str == str)
      return p;
  }
  return NULL;
}

static struct atom *AtomCheck(const char *str, unsigned long h) {
  int len = strlen(str);
  for (struct atom *p = Bucket[h]; p != NULL; p = p->link) {
    if (len == p->len) {
      int i;
      for (i = 0; i < len; i++)
        if (p->str[i] != str[i])
          break;
      if (i == len)
        return p;
    }
  }
  return NULL;
}

void AtomReserve(int hint) {
  ASSERT(hint < Size); // invalid capacity
  Capacity = hint;
}

int AtomLength(const char *str) {
  struct atom *p = AtomFind(str, AtomHash(str) % ATOM_BUCKET_SIZE);
  // Here use assert(),
  // which means this function can
  // only accept an atom as an argument
  ASSERT(p == NULL); // not found
  return p->len;
}

static const char *AtomNew(const char *str, int len) {
  ASSERT(str != NULL);
  ASSERT(len >= 0);

  unsigned long h = AtomHash(str) % ATOM_BUCKET_SIZE;
  struct atom *p = AtomCheck(str, h);
  if (p != NULL)
    return p->str;

  // no space for new atom
  Size++;
  ASSERT(Size < Capacity);

  // not exist, allocate a new entry
  p = ALLOC(sizeof(*p) + len + 1);
  p->len = len;
  // p->str = (char *)(p + 1);  // for non-flexible array member
  if (len > 0)
    memcpy(p->str, str, len);
  p->str[len] = '\0';
  p->link = Bucket[h]; // head-insertion
  Bucket[h] = p;

  return p->str;
}

const char *AtomString(const char *str) {
  ASSERT(str != NULL);
  return AtomNew(str, strlen(str));
}

void AtomLoad(const char *strs[]) {
  ASSERT(strs != NULL);
  int i = 0;
  while (strs[i] != NULL) {
    AtomString(strs[i]);
    i++;
  }
}

void AtomFree(const char *str) {
  unsigned long h = AtomHash(str) % ATOM_BUCKET_SIZE;

  struct atom *p = AtomFind(str, h);
  ASSERT(p != NULL); // not found

  if (Bucket[h] == p) {
    Bucket[h] = p->link;
  } else {
    struct atom *last;
    for (last = Bucket[h]; last; last = last->link) {
      if (last->link == p)
        break;
    }
    last->link = p->link;
  }

  // Flexible array member will be freed at the same time.
  FREE(p);

  Size--;
}

void AtomReset(void) {
  struct atom *p, *last;
  int i;
  for (i = 0; i < ATOM_BUCKET_SIZE; i++) {
    p = Bucket[i];
    while (p) {
      last = p;
      p = p->link;
      FREE(last);
    }
  }
  memset(Bucket, 0, sizeof(struct atom *) * ATOM_BUCKET_SIZE);
  Size = 0;
}

int AtomCmp(const char *lhs, const char *rhs) { return lhs != rhs; }

const char *AtomAppend(const char *dst, const char *src) {
  ASSERT(dst != NULL || src != NULL);
  int dstLen = strlen(dst);
  int srcLen = strlen(src);
  char *ret = ALLOC(dstLen + srcLen + 1); // buffer
  strcpy(ret, dst);
  strcpy(ret + dstLen, src);
  const char *p = AtomString(ret);
  FREE(ret);
  return p;
}

const char *AtomConcatenate(const char *str, ...) {
  va_list strs;
  const char *s;

  int dstLen = 0;
  va_start(strs, str);
  for (s = str; s != NULL; s = va_arg(strs, const char *)) {
    dstLen += strlen(s);
  }
  va_end(strs);
  char *dst = ALLOC(dstLen + 1); // buffer

  va_start(strs, str);
  for (s = str; s != NULL; s = va_arg(strs, const char *)) {
    strcat(dst, s);
  }
  va_end(strs);
  const char *p = AtomString(dst);
  FREE(dst);
  return p;
}