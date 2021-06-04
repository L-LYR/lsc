#include "to_str.h"

#include <stdio.h>

static char InnerStrBuffer[16];

const char* Itoa(int i) {
  sprintf(InnerStrBuffer, "%d", i);
  return InnerStrBuffer;
}
const char* Itox(int i) {
  sprintf(InnerStrBuffer, "0x%X", i);
  return InnerStrBuffer;
}

const char* Ftox(float f) {
  sprintf(InnerStrBuffer, "0x%X", *(int*)&f);
  return InnerStrBuffer;
}