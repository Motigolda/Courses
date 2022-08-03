CC=g++
CFLAGS=-Wall -g -Iinclude
BUILDDIR=build
BINDIR=${BUILDDIR}/bin
OBJDIR=${BUILDDIR}/obj
TESTDIR=test

FileDescriptor.o:	
	${CC} ${CFLAGS} -c src/FileDescriptor.cpp -o ${OBJDIR}/$@

fsDisk.o:
	${CC} ${CFLAGS} -c src/fsDisk.cpp -o ${OBJDIR}/$@

FsFile.o:
	${CC} ${CFLAGS} -c src/FsFile.cpp -o ${OBJDIR}/$@

main.o:
	${CC} ${CFLAGS} -c src/main.cpp -o ${OBJDIR}/$@

main: FileDescriptor.o fsDisk.o FsFile.o main.o 
	${CC} ${CFLAGS} ${OBJDIR}/*.o -o ${BINDIR}/main

.PHONY: clean

clean:
	rm -r ${OBJDIR}/*.o