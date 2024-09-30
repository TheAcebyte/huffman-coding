CC = gcc
CFLAGS = -Ilib -Wall

LIBS = $(wildcard lib/*.c)
OBJS= $(patsubst lib/%.c,build/%.o,$(LIBS)) build/main.o

all: build

build: $(OBJS)
	$(CC) build/*.o -o main

build/main.o: src/main.c
	$(CC) $(CFLAGS) -c $^ -o $@

build/%.o: lib/%.c lib/%.h
	$(CC) -c $< -o $@

clean: clean-linux

clean-linux:
	rm -f *.out build/*

clean-windows:
	del /S /Q *.exe
	del /S /Q build\*