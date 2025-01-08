
CC = gcc
CFLAGS = -std=c99 -Wall -g 

# Compiler inputs
OBJECTS = beale.o functions.o file.o
OUTPUT = beale
all: beale.o
	$(CC) $(CFLAGS) -o beale beale.c functions.c file.c

beale.o: beale.c
	$(CC) $(CFLAGS) -c beale.c

functions.o: functions.c functions.h
	$(CC) $(CFLAGS) -c functions.c functions.h

file.o: 
	$(CC) $(CFLAGS) -c file.c file.h

clean: 
	rm *.o

purge: clean
	rm beale
