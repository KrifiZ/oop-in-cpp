CC = gcc
CFLAGS = -Wall -Wextra -pedantic -std=c11 -g

main: TestStack.c Stack.c Stack.h
	$(CC) $(CFLAGS) TestStack.c Stack.c -o main

test: main
	./main

clean:
	rm -f main

.PHONY: test clean
