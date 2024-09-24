.PHONY: all run clean

CC = clang
CFLAGS = -Wall -Wextra -Werror -std=c99

all: run

run: test
	./test

test: main.c testlib.h testlib.c
	$(CC) $(CFLAGS) -o test main.c testlib.c

clean:
	rm -f test
