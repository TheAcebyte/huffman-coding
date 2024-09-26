SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)
CC = gcc

all: $(OBJS)

%.o: %.c %.h
	$(CC) -c $<

clean:
	del *.o