VPATHS=libs

SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)
DEPS = $(wildcard *.h)
CC = gcc

all: output

output: $(OBJS)
	$(CC) -o $@ $^

%.o: %.c $(DEPS)
	$(CC) -c $< -o $@

clean:
	del *.o output.exe