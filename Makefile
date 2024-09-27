DIR = libs
CC = gcc
CFLAGS = -I$(DIR) -c

output: main.o
	$(MAKE) -C $(DIR) all
	$(CC) $^ $(DIR)/*.o -o main

main.o: main.c
	$(CC) $(CFLAGS) $^

build:
	$(CC) $(BUILD)/*.o -o $(BIN)/output

run:
	./bin/output

clean:
	del $(BUILD)/.o $(BIN)./output