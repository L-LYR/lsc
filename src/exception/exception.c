#include "exception.h"

#include "../lib/llsc.h"
struct except_t Unreachable = {"Unreachable!"};
struct except_t InFileOpenErr = {"Can not open input file!"};
struct except_t OutFileOpenErr = {"Can not open output file!"};
struct except_t UnknownNodeType = {"Unknown Node Type!"};
struct except_t UnexpectedNodeType = {"Unexcepted Node Type!"};
struct except_t UnknownBaseType = {"Unknown Base Type!"};
struct except_t InvalidArraySize = {"Invalid Array Size!"};
struct except_t BufferOverflow = {"Buffer Overflow!"};
struct except_t UnknownSegment = {"Unknown Segment!"};
struct except_t UnexpectedEOF = {"Unexpected EOF!"};
struct except_t UnexpectedDelim = {"Unexpected Delimiter!"};
struct except_t FileReadError = {"File Reading Error!"};
struct except_t UnknownAttrType = {"Unknown Attribute Type!"};
struct except_t UnknownInsType = {"Unknown Instruction Type!"};