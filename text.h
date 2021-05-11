#ifndef TEXT_H
#define TEXT_H
/*
  CopyStr will copy a NULL-terminated string.
  It will return a const char*.
  The caller must remember to free the return value.
*/

const char *CopyStr(const char *src);

/*
  AppendStr will append a NULL-terminated string to another one.
  It will return a const char*.
  The caller must remember to free the return value.
*/

const char *AppendStr(const char *dst, const char *src);

/*
  ConcatenateStr will concatenate NULL-terminated strings.
  It will return a const char*.
  The caller must remember to free the return value.
  The last arguement must be NULL.
*/

const char *ConcatenateStr(const char *str, ...);

#endif