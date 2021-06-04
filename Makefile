.PHONY:
	all clean tests
all:
	cd lib && make all;
	cd src && make lexer -j 8 && make parser -j 8;
clean:
	cd src && make clean;
	cd lib && make clean;
	rm -rf ./res/*;

valgrind_flags := --leak-check=full
valgrind_flags += --show-leak-kinds=all
valgrind_flags += --track-origins=yes
valgrind_flags += --log-file="./res/memcheck.log"

test_input := ./test/sum.lsc
lexer_output := ./res/test.la
ast_output := ./res/test.ast
sym_output := ./res/test.sym
ir_output := ./res/test.ir

tests:
	@echo "Test Lexer";
	valgrind $(valgrind_flags) ./bin/lscl -v -i $(test_input) -o $(lexer_output);
	@echo "Test AST & Symbol Table Generator & IR Generator";
	valgrind $(valgrind_flags) ./bin/lscp -v $(ast_output) -i $(test_input) -s $(sym_output) -g $(ir_output);
