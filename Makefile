.PHONY:
	all clean
all:
	cd src && make lexer && make st-parser && make ast-parser

clean:
	cd src && make clean