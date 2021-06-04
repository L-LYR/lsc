#include "exception.h"

#include "../lib/llsc.h"
struct except_t Unreachable = {"Unreachable!"};
struct except_t InFileOpenErr = {"Can not open input file!"};
struct except_t OutFileOpenErr = {"Can not open output file!"};
struct except_t UnknownNodeType = {"Unknown Node Type!"};
struct except_t UnexpectedNodeType = {"Unexcepted Node Type!"};
struct except_t UnknownBaseType = {"Unknown Base Type!"};
struct except_t InvalidArraySize = {"Invalid Array Size!"};
