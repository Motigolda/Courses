CC=gcc
CFLAGS=-Wall -g -fdiagnostics-color=always
BIN_DIR=bin

wait.o:
	${CC} ${CFLAGS} -c wait.c -o ${BIN_DIR}/main.o

processes: wait.o
	-${CC} ${CFLAGS} $(BIN_DIR)/*.o -o ${BIN_DIR}/processes

.PHONY: clean

clean:
	rm ${BIN_DIR}/*.o

all: processes clean
	@echo "------- End Of Compiliation -------"
