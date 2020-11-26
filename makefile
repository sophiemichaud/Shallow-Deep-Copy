CFLAGS = -std=c99 -pedantic -Wall
CC = gcc -g

all: shallow_and_deep_copy

shallow_and_deep_copy:shallow_and_deep_copy.o
	$(CC) $(CFLAGS) shallow_and_deep_copy.o -o shallow_and_deep_copy

shallow_and_deep_copy.o:shallow_and_deep_copy.c shallow_and_deep_copy.h
	$(CC) $(CFLAGS) -c shallow_and_deep_copy.c -o shallow_and_deep_copy.o

clean:
	rm -i *.o shallow_and_deep_copy
