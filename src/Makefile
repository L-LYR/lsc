.PHONY:
	lexer ast-parser st-parser clean

cc := clang
LLSC := ../lib/lib/llsc.a

lexer: lsc.yy.o lscl.o exception.o symbol_table.o
	clang -Wall -g $^ $(LLSC)  -o ../bin/lscl

python_ldflags = $(shell python3-config --ldflags)
parser: lsc.yy.o lsc.tab.o ast.o lscp.o symbol_table.o exception.o
	clang -Wall -g -lpython3.8 -L/usr/lib -I/usr/include/python3.8 -L/usr/lib $^ $(LLSC) -o ../bin/lscp;
	cp ./BeautifyAST.py ../bin/;

%.o: %.c
	clang -g -c -I/usr/include/python3.8 $^

lsc.yy.c: lsc.l lsc.tab.c
	flex -o lsc.yy.c lsc.l
lsc.tab.c: lsc.y
	bison -v -d lsc.y
clean:
	rm -rf *.o *.output ../bin/* *.yy.c *.tab.*