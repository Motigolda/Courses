CC=g++
CFLAGS=-Wall -g -I. -lstdc++
BUILDDIR=build
BINDIR=${BUILDDIR}/bin
OBJDIR=${BUILDDIR}/obj

.PHONY: directories

directories:
	mkdir ${BUILDDIR} ${BINDIR} ${OBJDIR} -p
	
main.o:
	${CC} ${CFLAGS} -c main.cpp -o ${OBJDIR}/main.o

sim_mem.o:
	${CC} ${CFLAGS} -c sim_mem.cpp -o ${OBJDIR}/sim_mem.o

main: directories sim_mem.o main.o
	${CC} ${CFLAGS} ${OBJDIR}/main.o -o ${BINDIR}/main

.PHONY: clean

clean:
	rm -r ${OBJDIR}/*.o


	