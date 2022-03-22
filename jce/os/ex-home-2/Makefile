CC=gcc
CFLAGS=-Wall -g -fdiagnostics-color=always
BIN_DIR=bin

bin_dir_creator:
	-mkdir ${BIN_DIR}

ex2a.o:
	${CC} ${CFLAGS} -c ex2a.c -o ${BIN_DIR}/ex2a.o

my_shell: ex2a.o
	-${CC} ${CFLAGS} $(BIN_DIR)/*.o -o ${BIN_DIR}/my_shell

.PHONY: clean all

clean:
	rm ${BIN_DIR}/*.o

all: bin_dir_creator my_shell clean
	@echo "------- End Of Compiliation -------"


