CFLAGS=-I.

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

fvm: fvm.o
	$(CC) -o fvm fvm.o -I.

clean:
	rm -rf *.o

all: fvm
