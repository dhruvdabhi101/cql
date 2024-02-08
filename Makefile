CC      = gcc
CFLAGS  = -g
RM      = rm -f
CFLAGS 	= -Wall -std=c99


default: all

all: main

main: main.c
	$(CC) -o main main.c $(CFLAGS)


clean veryclean:
	$(RM) main
