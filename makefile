all: main.o shell.o
	gcc -o main.o shell.o

main.o: main.c shell.c shell.h
	gcc -c main.c shell.c

shell.o: shell.c shell.h
	gcc -c shell.c

run:
	./a.out