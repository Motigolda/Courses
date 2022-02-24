CC=gcc
CFLAGS=-Wall -g
BIN_DIR=bin

main.o:
	${CC} ${CFLAGS} -c main.c -o ${BIN_DIR}/main.o

main: main.o
	-${CC} ${CFLAGS} $(BIN_DIR)/*.o -o ${BIN_DIR}/main

clean:
	rm ${BIN_DIR}/*.o

all: main clean
	@echo "------- End Of Compiliation -------"


