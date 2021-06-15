.PHONY:
	all clean tests
all: backend frontend

frontend: lib
	cd ./src/frontend && make all
lib:
	cd ./src/lib/src && make lib -j 8;

backend: lib
	cd ./src/backend && make all

clean:
	-rm -rf ./res/* ./bin/*;
	cd ./src/frontend && rm lsc.output lsc.yy.c lsc.tab.c lsc.tab.h

valgrind_flags := --leak-check=full
valgrind_flags += --show-leak-kinds=all
valgrind_flags += --track-origins=yes

filename_prefix := add

test_input := ./test/$(filename_prefix).lsc
lexer_output := ./res/$(filename_prefix).la
ast_output := ./res/$(filename_prefix).ast
sym_output := ./res/$(filename_prefix).sym
ir_output := ./res/$(filename_prefix).ir
bb_output := ./res/$(filename_prefix).bb

lexer-test:
	@echo "Test Lexer";
	valgrind $(valgrind_flags) --log-file="./res/lexer-test-memcheck.log" ./bin/lscl -v -i $(test_input) -o $(lexer_output);
parser-test:
	@echo "Test AST & Symbol Table Generator & IR Generator";
	valgrind $(valgrind_flags) --log-file="./res/parser-test-memcheck.log" ./bin/lscp -v $(ast_output) -i $(test_input) -s $(sym_output) -g $(ir_output);
vm-test:
	@echo "Test VM";
	valgrind $(valgrind_flags) --log-file="./res/vm-test-memcheck.log" ./bin/lscvm -i $(ir_output) -b $(bb_output);
