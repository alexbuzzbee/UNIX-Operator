CC = gcc
CCFLAGS = -std=gnu99
LD = gcc
LDFLAGS = -o uop

uop: main.o util.o
	${LD} ${LDFLAGS} main.o util.o

main.o: main.c util.h
	${CC} ${CCFLAGS} -c main.c

util.o: util.c
	${CC} ${CCFLAGS} -c util.c
