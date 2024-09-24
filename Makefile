.PHONY: all run clean

CC = clang
CFLAGS = -Wall -Wextra -Werror -std=c99

all: run

run: build
	./build/example

build: example.c testlib.h testlib.c
	$(CC) $(CFLAGS) -o ./build/example example.c testlib.c

clean:
	rm -f build/example
