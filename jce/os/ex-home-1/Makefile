CC=gcc
CFLAGS=-Wall -g -fdiagnostics-color=always
BIN_DIR=bin

main.o:
	${CC} ${CFLAGS} -c main.c -o ${BIN_DIR}/main.o

word_counter: main.o
	-${CC} ${CFLAGS} $(BIN_DIR)/*.o -o ${BIN_DIR}/word_counter

.PHONY: clean

clean:
	rm ${BIN_DIR}/*.o

all: word_counter clean
	@echo "------- End Of Compiliation -------"


