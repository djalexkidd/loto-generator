CC = gcc
CFLAGS = -Wall -Werror

all: loto

loto: loto.c
	$(CC) $(CFLAGS) -o loto loto.c

clean:
	rm -f loto
