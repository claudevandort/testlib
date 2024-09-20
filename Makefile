.PHONY: all run clean

CC = clang
CFLAGS = -Wall -Wextra -Werror -std=c99

all: run

run: test
	./test

test: sample.c unit_test.h
	$(CC) $(CFLAGS) -o test sample.c

clean:
	rm -f test
