ifndef CC
	CC = gcc
endif
CCFLAGS = -std=gnu99
ifndef LD
	LD = ${CC} # Using compiler as linker, for... reasons.
endif
LDFLAGS = -o uop

uop: main.o util.o
	${LD} ${LDFLAGS} main.o util.o

main.o: main.c util.h
	${CC} ${CCFLAGS} -c main.c

util.o: util.c
	${CC} ${CCFLAGS} -c util.c
