.PHONY:
	lexer parser clean

lexer: lsc.yy.c lscl.c
	clang -g -o ./bin/lscl $^

parser: lsc.yy.c lsc.tab.c ast.c text.c lscp.c
	clang -g -o ./bin/lscp $^

st-parser: lsc.yy.c lsc-st.tab.c st.c text.c lscp-st.c
	clang -g -o ./bin/lscp-st $^

lsc.yy.c: lsc.l lsc.tab.c lsc-st.tab.c
	flex -o lsc.yy.c lsc.l
lsc.tab.c: lsc.y
	bison -v -d lsc.y

lsc-st.tab.c: lsc-st.y
	bison -v -d lsc-st.y

clean:
	rm -rf *.o *.output ./bin/* *.yy.c *.tab.*