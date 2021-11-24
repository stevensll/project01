all: test.o
	gcc -o shell.out test.o shell.o

test.o: test.c shell.c shell.h
	gcc -c test.c shell.c

shell.o: shell.c shell.h
	gcc -c shell.c

run:
	./shell.out