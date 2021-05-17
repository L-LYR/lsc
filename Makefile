.PHONY:
	all clean tests
all:
	cd lib && make all;
	cd src && make lexer && make parser;
clean:
	cd src && make clean;
	cd lib && make clean;
	rm -rf ./res/*;

valgrind_flags := --leak-check=full
valgrind_flags += --show-leak-kinds=all
valgrind_flags += --track-origins=yes
valgrind_flags += --log-file="./res/memcheck.log"

test_input := ./test/test.lsc
lexer_output := ./res/test.la
ast_output := ./res/test.ast

tests:
	@echo "test lexer";
	valgrind $(valgrind_flags) ./bin/lscl -v -i $(test_input) -o $(lexer_output);
	@echo "test ast generator";
	valgrind $(valgrind_flags) ./bin/lscp -v -i $(test_input) -o $(ast_output);
