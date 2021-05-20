#include "../include/assert.h"

const struct except_t assert_failed = {"Assertion Failed"};

void(ASSERT)(int e) { ASSERT(e); }  // Here use parentheses to avoid the macro expanding.