all: tests

tests: cyclebuf.c cyclebuf.h tests.c
	gcc -Wall -pedantic -g3 -gdwarf cyclebuf.c tests.c -o tests

.PHONY: clean

clean:
	rm -rf tests
