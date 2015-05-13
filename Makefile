CC=gcc

fvm: fvm.o
	$(CC) -std=c99 -o fvm fvm.o -I.
	./fvm examples/addition_cmprs.pot
