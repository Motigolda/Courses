CC=gcc
CFLAGS=-Wall -g -fdiagnostics-color=always
BIN_DIR=bin

bin_dir_creator:
	-mkdir ${BIN_DIR}

ex2.o:
	${CC} ${CFLAGS} -c ex2.c -o ${BIN_DIR}/ex2.o

my_shell: ex2.o
	-${CC} ${CFLAGS} $(BIN_DIR)/*.o -o ${BIN_DIR}/my_shell

.PHONY: clean all

clean:
	rm ${BIN_DIR}/*.o

all: bin_dir_creator my_shell clean
	@echo "------- End Of Compiliation -------"


