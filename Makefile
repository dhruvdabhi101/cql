CC      = gcc
CFLAGS  = -g
RM      = rm -f


default: all

all: main

main: main.c
	$(CC) -o main main.c

clean veryclean:
	$(RM) main
