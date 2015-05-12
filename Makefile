CC=gcc

fvm: fvm.o
	$(CC) -o fvm fvm.o -std=c99 -I
	./fvm examples/example.pot
