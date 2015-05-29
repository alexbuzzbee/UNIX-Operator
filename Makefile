ifndef CC
	CC = gcc
endif
CCFLAGS = -std=gnu99
LD = ${CC} # Using compiler as linker, for reasons of failed local builds.
LDFLAGS = -o uop -lc

default: uop

test: uop
	bash test.sh

uop: main.o util.o
	${LD} ${LDFLAGS} main.o util.o

main.o: main.c util.h
	${CC} ${CCFLAGS} -c main.c

util.o: util.c
	${CC} ${CCFLAGS} -c util.c
