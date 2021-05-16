.PHONY:
	lib clean

lib:
	clang -Wall -c -g ./*.c && llvm-ar -rc ../lib/llsc.a ./*.o

clean:
	rm -rf *.o ../lib/*.a