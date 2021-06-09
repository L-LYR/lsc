.PHONY:
	all clean

LLSC := ../lib/lib/llsc.a

warning := -Wall -Wextra -Wno-unused-parameter

all: *.c ../exception/exception.c
	clang $(warning) -g $^ $(LLSC) -o ../../bin/lscvm
