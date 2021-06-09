#ifndef EXCEPTION_H
#define EXCEPTION_H

extern struct except_t Unreachable;
extern struct except_t InFileOpenErr;
extern struct except_t OutFileOpenErr;
extern struct except_t UnknownNodeType;
extern struct except_t UnexpectedNodeType;
extern struct except_t UnknownBaseType;
extern struct except_t InvalidArraySize;
extern struct except_t BufferOverflow;
extern struct except_t UnknownSegment;
extern struct except_t UnexpectedEOF;
extern struct except_t UnexpectedDelim;
extern struct except_t FileReadError;
extern struct except_t UnknownInsType;
extern struct except_t UnknownAttrType;

#endif