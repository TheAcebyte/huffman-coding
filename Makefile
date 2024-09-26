DIR = libs
CC = gcc
CFLAGS = -I$(DIR) -c

all: output

output: main.o
	$(MAKE) -C $(DIR) all
	$(CC) $^ $(DIR)/*.o -o main

main.o: main.c
	$(CC) $(CFLAGS) $^

clean:
	$(MAKE) -C $(DIR) clean
	del *.o main.exe