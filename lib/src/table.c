#include "../include/table.h"

#include <limits.h> // INT_MAX
#include <string.h> // memset()

#include "../include/assert.h"
#include "../include/mem.h"

// Size of table
// Table_create will choose the greatest value which is less than hint
static int primes[] = {
    32,    //
    32,    //
    64,    //
    128,   //
    256,   //
    509,   // 512   = 2 ^ 9
    1021,  // 1025  = 2 ^ 10
    2039,  // 2048  = 2 ^ 11
    4093,  // 4096  = 2 ^ 12
    8191,  // 8192  = 2 ^ 13
    16381, // 16384 = 2 ^ 14
    32771, // 32768 = 2 ^ 15
    65521, // 65535 = 2 ^ 16
    INT_MAX,
};

struct table_t *TableCreate(int hint, equal_t equal, hash_t hash) {
  ASSERT(hint >= 0);
  ASSERT(equal != NULL);
  ASSERT(hash != NULL);

  int i;
  for (i = 1; primes[i] < hint; i++)
    ;
  hint = primes[i - 1];

  struct table_t *table =
      ALLOC(sizeof(*table) + hint * sizeof(table->buckets[0]));
  table->capacity = hint;
  table->equal = equal;
  table->hash = hash;
  table->buckets = (struct binding **)(table + 1);
  memset(table->buckets, 0, sizeof(table->buckets[0]) * hint);
  table->size = 0;
  table->timeStamp = 0;

  return table;
}

void TableFree(struct table_t **table) {
  ASSERT(table != NULL);
  ASSERT(*table != NULL);

  if ((*table)->size > 0) {
    struct binding *p, *q;
    for (int i = 0; i < (*table)->capacity; i++) {
      for (p = (*table)->buckets[i]; p != NULL; p = q) {
        q = p->link;
        FREE(p);
      }
    }
  }
  FREE(*table);
}

void *TablePut(struct table_t *table, const void *key, void *value) {
  ASSERT(table != NULL);
  ASSERT(key != NULL);
  struct binding *p;
  void *prev;
  unsigned long h = table->hash(key) % table->capacity;
  for (p = table->buckets[h]; p != NULL; p = p->link) {
    if (table->equal(key, p->key))
      break;
  }
  if (p == NULL) {
    NEW(p);
    p->key = key;
    p->link = table->buckets[h];
    table->buckets[h] = p;
    table->size++;
    prev = NULL;
  } else
    prev = p->value;
  p->value = value; // overwrite or initialize
  table->timeStamp++;
  return prev;
}

void *TableGet(struct table_t *table, const void *key) {
  ASSERT(table != NULL);
  ASSERT(key != NULL);

  struct binding *p;
  unsigned long h = table->hash(key) % table->capacity;
  for (p = table->buckets[h]; p != NULL; p = p->link) {
    if (table->equal(key, p->key))
      break;
  }

  return (p == NULL) ? NULL : p->value;
}

void *TableRemove(struct table_t *table, const void *key) {
  ASSERT(table != NULL);
  ASSERT(key != NULL);

  struct binding **pp, *p;
  void *prev = NULL;
  unsigned long h = table->hash(key) % table->capacity;
  for (pp = &table->buckets[h]; *pp != NULL; pp = &(*pp)->link) {
    if (table->equal(key, (*pp)->key)) {
      p = *pp;
      prev = p->link;
      FREE(p);
      table->size--;
      break;
    }
  }
  table->timeStamp++;
  return prev;
}

int TableSize(struct table_t *table) {
  ASSERT(table != NULL);
  return table->size;
}

void **TableToArray(struct table_t *table, void *end) {
  int i, j;
  void **arr;
  struct binding *p;

  ASSERT(table != NULL);

  arr = ALLOC((2 * table->size + 1) * sizeof(*arr));
  for (i = 0, j = 0; i < table->capacity; i++) {
    for (p = table->buckets[i]; p != NULL; p = p->link) {
      arr[j++] = (void *)p->key; // cast const
      arr[j++] = p->value;
    }
  }
  arr[j] = end;
  return arr;
}