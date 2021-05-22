.PHONY:
	lib clean

CLANG_FLAG := -Wall -Wextra -Wno-unused-parameter

SRC := $(wildcard *.c)
OBJ := $(patsubst %.c, ../lib/%.o, $(SRC))

lib: $(OBJ)
	llvm-ar -rc ../lib/llsc.a $^

../lib/%.o: %.c
	clang $(CLANG_FLAG) -c -g $^ -o $@
clean:
	rm -rf ../lib/*