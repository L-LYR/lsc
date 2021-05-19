.PHONY:
	lexer ast-parser st-parser clean

cc := clang
LLSC := ../lib/lib/llsc.a

lexer: lsc.yy.o lscl.o exception.o 
	clang -Wall -g $^ $(LLSC)  -o ../bin/lscl

parser: lsc.yy.o lsc.tab.o ast.o lscp.o limit.o exception.o symbol_table.o 
	clang -Wall -g $^ $(LLSC) -o ../bin/lscp;
	cp ./*.py ../bin/;
	chmod +x ../bin/*.py;

%.o: %.c
	clang -g -c $^

lsc.yy.c: lsc.l lsc.tab.c
	flex -o lsc.yy.c lsc.l
lsc.tab.c: lsc.y
	bison -v -d lsc.y
clean:
	rm -rf *.o *.output ../bin/* *.yy.c *.tab.*