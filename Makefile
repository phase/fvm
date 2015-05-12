CC=gcc

fvm: fvm.o
	$(CC) -std=c99 -o fvm fvm.o -I.
	./fvm examples/example.pot
