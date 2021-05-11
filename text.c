#include "panic.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char *CopyStr(const char *src) {
  int len = strlen(src);
  char *dst = (char *)calloc(sizeof(char), len + 1);
  if (dst == NULL) {
    PANIC("bad calloc!");
  }
  strcpy(dst, src);
  return dst;
}

const char *AppendStr(const char *dst, const char *src) {
  if (dst == NULL) {
    return CopyStr(src);
  }
  if (src == NULL) {
    return CopyStr(dst);
  }
  int dstLen = strlen(dst);
  int srcLen = strlen(src);
  char *ret = (char *)calloc(sizeof(char), dstLen + srcLen + 1);
  if (ret == NULL) {
    PANIC("bad calloc!");
  }
  strcpy(ret, dst);
  strcpy(ret + dstLen, src);
  return ret;
}

const char *ConcatenateStr(const char *str, ...) {
  va_list strs;
  const char *s;
  int dstLen = 0;
  va_start(strs, str);
  for (s = str; s != NULL; s = va_arg(strs, const char *)) {
    dstLen += strlen(s);
  }
  va_end(strs);
  char *dst = (char *)calloc(sizeof(char), dstLen + 1);
  if (dst == NULL) {
    PANIC("bad calloc!");
  }
  va_start(strs, str);
  for (s = str; s != NULL; s = va_arg(strs, const char *)) {
    strcat(dst, s);
  }
  va_end(strs);
  return dst;
}