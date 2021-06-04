/*
    An atom is a pointer to a unique, immutable sequence of zero or more
    arbitrary bytes. Atoms are pointers to null-terminated strings.
    Two atoms are identical if they point to the same location.
*/

#ifndef ATOM_INCLUDE
#define ATOM_INCLUDE
#include <stdbool.h>
/*
    AtomReseve:
        1. Change the atom table capacity.
        2. hint must be bigger than the current size of atom table.
*/
extern void AtomReserve(int hint);

/*
    AtomString:
        1. Accept a null-teminated string, adds a copy of that string to
        the atom table.
        2. Return the atom.
*/
extern const char *AtomString(const char *str);

/*
    AtomLength:
        1. Return the length of its atom argument.
*/
extern int AtomLength(const char *str);

/*
    AtomLoad:
        1. Accept an array of pinters to strings.
        2. The last element of strs must be NULL.
*/
extern void AtomLoad(const char *strs[]);

/*
    AtomFree:
        1. Free the atom given by str.
*/
extern void AtomFree(const char *str);

/*
    AtomReset:
        1. Clear the atom table.
*/
extern void AtomReset(void);

/*
    AtomCmp:
        1. Atom is unique.
        2. It is simple, lhs != rhs.

*/
extern int AtomCmp(const char *lhs, const char *rhs);

/*
  AppendStr will append a NULL-terminated string to another one.
  It will return a const char*.
  The caller must remember to free the return value.
*/

extern const char *AtomAppend(const char *dst, const char *src);

/*
  ConcatenateStr will concatenate NULL-terminated strings.
  It will return a const char*.
  The caller must remember to free the return value.
  The last arguement must be NULL.
*/

extern const char *AtomConcatenate(const char *str, ...);

extern unsigned long AtomHash(const char *str);
extern _Bool AtomEqual(const char *l, const char *r);

#endif