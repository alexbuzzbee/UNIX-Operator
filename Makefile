ifndef CC
	CC = gcc
endif
CCFLAGS = -std=gnu99
LD = ${CC} # Using compiler as linker, for reasons of failed local builds.
LDFLAGS = -o uop -lc

default: uop

test: uop
	bash test.sh

uop: main.o lib/util.o lib/menu.o
	${LD} ${LDFLAGS} main.o lib/util.o lib/menu.o

main.o: main.c lib/util.h lib/menu.h
	${CC} ${CCFLAGS} -c main.c

lib/util.o: lib/util.c
	${CC} ${CCFLAGS} -c lib/util.c -o lib/util.o

lib/menu.o: lib/menu.c
	${CC} ${CCFLAGS} -c lib/menu.c -o lib/menu.o
