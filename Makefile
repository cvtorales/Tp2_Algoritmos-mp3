CC=gcc
CFLAGS=-Wall -ansi -pedantic -c 
LFLAGS=-Wall -ansi -pedantic

all: mp3explorer clean

mp3explorer: main.o vector.o track.o errors.o
	$(CC) $(LFLAGS) -o mp3explorer  main.o vector.o track.o errors.o

main.o: main.c main.h setup.h mp3.h errors.h types.h vector.h track.h
	$(CC) $(CFLAGS) -o main.o main.c 

vector.o: vector.c errors.h vector.h types.h
	$(CC) $(CFLAGS) -o vector.o vector.c

track.o: track.c errors.h track.h mp3.h types.h setup.h
	$(CC) $(CFLAGS) -o track.o track.c

errors.o: errors.c errors.h
	$(CC) $(CFLAGS) -o errors.o errors.c

clean:
	rm *.o