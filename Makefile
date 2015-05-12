CC=gcc
CFLAGS=-I.

fvm: fvm.o
	$(CC) -o fvm fvm.o $(CFLAGS)
	fvm
