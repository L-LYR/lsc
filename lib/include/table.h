/*
    Associative table is a set of key-value pairs.
    This table is a unordered_map actually.
*/

#ifndef TABLE_INCLUDE
#define TABLE_INCLUDE
#include <stdbool.h>
typedef _Bool (*equal_t)(const void *, const void *);
typedef unsigned long (*hash_t)(const void *);

struct binding {
  struct binding *link;
  const void *key;
  void *value;
};

struct table_t {
  // features
  int capacity;
  int size;
  unsigned long timeStamp;

  // function pointers
  equal_t equal;
  hash_t hash;
  // flexible array members
  struct binding **buckets;
};

/*
    TableCreate:
        1. table_t will be allocated by TableCreate().
        2. hint is an estimate of the number of entries that the new
        table is expected to hold. But all tables can hold an arbitrary
        number of entries ragardless of the value of hint. hint > 0.
        3. Both equal() and hash() are function pointers which manipulate
        client-specific keys.
            1) equal() must return an integer less than zero, equal to zero, or
            greater than zero, if, respectively, x is less than y, x equals y,
            or x is greater than y. strequal() is an example.
            2) hash() must return a hash number for key.
            3) Each table can have its own equal() and hash().
            4) In default, it will use Atom_hash() and Atom_equal().
*/
extern struct table_t *TableCreate(int hint, equal_t equal, hash_t hash);

/*
    TableFree:
        1. Free the table itself and set it to NULL.
        2. Won't free the key-value pairs.
*/
extern void TableFree(struct table_t **table);

/*
    Basic operations for table.
*/

/*
    TablePut:
        1. If key exists, it will overwrite the previous value and return it.
        If not, return NULL.
*/
extern void *TablePut(struct table_t *table, const void *key, void *value);

/*
    TableGet:
        1. If key exists, return the value. If not, return NULL. But if the
   value is NULL, the meaning of return value is ambiguous.
*/
extern void *TableGet(struct table_t *table, const void *key);

/*
    TableRemove:
        1. If key exists, remove the key-value pair, and return the value. If
   not, return NULL.
*/
extern void *TableRemove(struct table_t *table, const void *key);

extern int TableSize(struct table_t *table);

/*
    Table_to_array:
        1. Build an array with 2n+1 elements for an n elements table
        and returns a pointer to the first element.
        2. The index of key is 2i+1 which the index of respective value is 2i.
        3. table can’t be changed while Table_map is visiting its bindings.
        4. Other features are like List_to_array() 2&3&4.
*/
extern void **TableToArray(struct table_t *table, void *end);

#endif