CC = gcc
CFLAGS = -Ilib -c

# LIBS = $(wildcard lib/*.c)
LIBS = utils.c

# $(patsubst lib/%.c,build/%.o,$(LIBS))
OBJS = build/utils.o build/main.o

all: run

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