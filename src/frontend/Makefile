.PHONY:
	lexer ast-parser st-parser clean all

LLSC := ../lib/lib/llsc.a

LFRONT := ../../bin/lfront.a

warning := -Wall -Wextra

all: lfront lexer parser

lfront:	lsc.yy.c lsc.tab.c
	clang $(warning) -Wno-unused-function -Wno-unneeded-internal-declaration -c -g $^ && \
	llvm-ar -rc $(LFRONT) *.o && \
	rm *.o
lexer: lscl.c ../exception/exception.c
	clang $(warning) -g $^ $(LLSC) $(LFRONT) -o ../../bin/lscl

parser: ast.c lscp.c ../exception/exception.c display.c symbol_table.c to_str.c generate_code.c
	clang $(warning) -g $^ $(LLSC) $(LFRONT) -o ../../bin/lscp;
	cp ./*.py ../../bin/;
	chmod +x ../../bin/*.py;

lsc.yy.c: lsc.l lsc.tab.c
	flex -o lsc.yy.c lsc.l
lsc.tab.c: lsc.y
	bison -v -d lsc.y

