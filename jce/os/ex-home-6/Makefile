CC=gcc
CFLAGS=-Wall -g -Iinclude
BUILDDIR=build
BINDIR=${BUILDDIR}/bin
OBJDIR=${BUILDDIR}/obj
TESTDIR=test

main.o:
	${CC} ${CFLAGS} -c src/main.c -o ${OBJDIR}/main.o

main: main.o
	${CC} ${CFLAGS} ${OBJDIR}/*.o -o ${BINDIR}/main

.PHONY: clean

clean:
	rm -r ${OBJDIR}/*.o