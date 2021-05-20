#include "limit.h"

#include <stdlib.h>
#include <string.h>

#include "../lib/llsc.h"
#include "exception.h"

#define BUFFER_SIZE 128
static char buffer[BUFFER_SIZE];

static int _CalArrSize(const char *t) {
  if (t == NULL) {
    RAISE(UnknownBaseType);
  }
  const char *p = (t + strlen(t) - 1);
  int sz = 1;
  while (p != t) {
    if (*p == ']') {
      const char *q = p - 1;
      while (*q != '[') {
        q--;
      }
      int len = p - q - 1;
      strncpy(buffer, q + 1, len);
      buffer[len] = '\0';
      sz *= atoi(buffer);
      p = q - 1;
    } else {
      int len = p - t + 1;
      if (buffer == t) {
        RAISE(UnknownBaseType);
      }
      strncpy(buffer, t, len);
      buffer[len] = '\0';
      sz *= SizeOf(buffer);
      p = t;
    }
  }
  if (sz <= 0) {
    RAISE(InvalidArraySize);
  }
  return sz;
}

int SizeOf(const char *t) {
  if (strcmp(t, "i32") == 0) {
    return i32_size;
  } else if (strcmp(t, "f32") == 0) {
    return f32_size;
  } else if (strcmp(t, "bool") == 0) {
    return bool_size;
  } else if (strcmp(t, "string") == 0) {
    return string_size;
  } else {
    int len = strlen(t);
    if (t[len - 1] == ']') {
      return _CalArrSize(t);
    } else {
      return 0;
    }
  }
}