.PHONY:
	lexer ast-parser st-parser clean

cc := clang
LLSC := ../lib/lib/llsc.a

warning := -Wall -Wextra -Wno-unused-function -Wno-unneeded-internal-declaration

lexer: lsc.yy.c lscl.c exception.c
	clang $(warning) -g $^ $(LLSC)  -o ../bin/lscl

parser: lsc.yy.c lsc.tab.c ast.c lscp.c exception.c display.c symbol_table.c 
	clang $(warning) -g $^ $(LLSC) -o ../bin/lscp;
	cp ./*.py ../bin/;
	chmod +x ../bin/*.py;

lsc.yy.c: lsc.l lsc.tab.c
	flex -o lsc.yy.c lsc.l
lsc.tab.c: lsc.y
	bison -v -d lsc.y
clean:
	rm -rf ../bin/*