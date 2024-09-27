CC = gcc
CFLAGS = -Ilib -c

LIBS = $(wildcard lib/*.c)
OBJS= $(patsubst lib/%.c,build/%.o,$(LIBS)) build/main.o

all: build

build: $(OBJS)
	$(CC) build/*.o -o bin/main

build/main.o: src/main.c
	$(CC) $(CFLAGS) -c $^ -o $@

build/%.o: lib/%.c lib/%.h
	$(CC) -c $< -o $@

run: build
	./bin/main

clean: clean-windows

clean-linux:
	rm -f bin/* build/*

clean-windows:
	del /S /Q bin\* build\*