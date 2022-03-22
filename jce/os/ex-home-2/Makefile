CC=gcc
CFLAGS=-Wall -g -fdiagnostics-color=always
BIN_DIR=bin

bin_dir_creator:
	-mkdir ${BIN_DIR}

ex2a.o:
	${CC} ${CFLAGS} -c ex2a.c -o ${BIN_DIR}/ex2a.o

my_shell: ex2a.o
	-${CC} ${CFLAGS} $(BIN_DIR)/*.o -o ${BIN_DIR}/my_shell

ex2b.o: clean
	${CC} ${CFLAGS} -c ex2b.c -o ${BIN_DIR}/ex2b.o

ex2b: ex2b.o
	-${CC} ${CFLAGS} $(BIN_DIR)/*.o -o ${BIN_DIR}/ex2b

.PHONY: clean all

clean:
	rm ${BIN_DIR}/*.o

all: bin_dir_creator my_shell ex2b clean
	@echo "------- End Of Compiliation -------"


