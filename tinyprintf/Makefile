CC=gcc
CFLAGS=-std=c99 -Wall -Wextra -Werror -Wvla -pedantic
LDLIBS=-lcriterion

all: src/tinyprintf.o
	$(CC) $(LDFLAGS) -o src/tinyprintf.o

check: tests/test.c tests/test.o src/tinyprintf.c src/tinyprintf.o
	$(CC) $(LDFLAGS) -o check src/tinyprintf.o tests/test.o ${LDLIBS}

tinyprintf.o: tests/test.c
	$(CC) $(CFLAGS) -c -o src/tinyprintf.o tests/test.c

clean:
	rm -f *.o
