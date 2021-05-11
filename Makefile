.PHONY:
	lexer parser clean

lexer: lsc.yy.c lscl.c
	clang -g -o ./bin/lscl $^

parser: lsc.yy.c lsc.tab.c ast.c text.c
	clang -g -o ./bin/lscp $^

lsc.yy.c: lsc.l lsc.tab.c
	flex -o lsc.yy.c lsc.l
lsc.tab.c: lsc.y
	bison -v -d lsc.y

clean:
	rm -rf *.o *.output ./bin/* lsc.yy.c lsc.tab.c lsc.tab.h