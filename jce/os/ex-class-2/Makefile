CC=gcc
CFLAGS=-Wall -g
BIN_DIR=bin

word_count.o:
	@echo "Creating word_count.o"
	$(CC) $(CFLAGS) -c word_count.c -o $(BIN_DIR)/word_count.o

main.o:
	@echo "Creating main.o"
	$(CC) $(CFLAGS) -c main.c -o $(BIN_DIR)/main.o

word_counter: word_count.o main.o
	@echo "Creating word_counter"
	$(CC) $(CFLAGS) $(BIN_DIR)/*.o -o $(BIN_DIR)/word_counter

all: word_counter clean
	@echo "End of compilation"

clean:
	@echo "Deleting object files"
	rm $(BIN_DIR)/*.o
