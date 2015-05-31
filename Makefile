UNAME_S = $(shell uname -s)

ifndef CC
	CC = gcc
endif
CCFLAGS = -std=gnu99 -fpic # -fpic set for reasons of library.
LD = ${CC} # Using compiler as linker, for reasons of failed local builds.
LDFLAGS = -lc

ifeq (${UNAME_S}, Darwin)
	SLIBEXT = dylib
else
	SLIBEXT = so
endif

default: uop libuop

test: uop
	bash test.sh

uop: main.o lib/util.o lib/menu.o
	${LD} ${LDFLAGS} main.o lib/util.o lib/menu.o -o uop

hello: apps/hello/main.o
	${LD} ${LDFLAGS} apps/hello/main.o lib/util.o lib/menu.o -o hello # Because libuop is broken.

libuop: libuop.${SLIBEXT}

libuop.so: lib/util.o lib/menu.o
	${LD} ${LDFLAGS} -shared -o libuop.so

libuop.dylib: lib/util.o lib/menu.o
	${LD} ${LDFLAGS} -shared -o libuop.dylib

main.o: main.c lib/util.h lib/menu.h
	${CC} ${CCFLAGS} -c main.c -o main.o

apps/hello/main.o: apps/hello/main.c lib/util.h lib/menu.h
	${CC} ${CCFLAGS} -c apps/hello/main.c -o apps/hello/main.o

lib/util.o: lib/util.c
	${CC} ${CCFLAGS} -c lib/util.c -o lib/util.o

lib/menu.o: lib/menu.c
	${CC} ${CCFLAGS} -c lib/menu.c -o lib/menu.o
