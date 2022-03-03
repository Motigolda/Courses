CC=gcc
CFLAGS=-Wall -g -fdiagnostics-color=always
BIN_DIR=bin

bin_create:
	-mkdir ${BIN_DIR}

wait.o:
	${CC} ${CFLAGS} -c wait.c -o ${BIN_DIR}/wait.o

processes: bin_create wait.o
	-${CC} ${CFLAGS} $(BIN_DIR)/wait.o -o ${BIN_DIR}/processes

cmd.o:
	${CC} ${CFLAGS} -c cmd.c -o ${BIN_DIR}/cmd.o

cmd: bin_create cmd.o
	-${CC} ${CFLAGS} $(BIN_DIR)/cmd.o -o ${BIN_DIR}/cmd

all: processes cmd clean 
	@echo "------- End Of Compiliation -------"

.PHONY: clean

clean:
	rm ${BIN_DIR}/*.o