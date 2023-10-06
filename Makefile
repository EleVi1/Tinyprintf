FILE_C= src/tinyprintf.c
FILE_O= src/tinyprintf.o
FILE_EXEC= src/tinyprintf

CC=gcc
CFLAGS=-std=c99 -Wall -Wextra -Werror -Wvla -pedantic
LDLIBS=-lcriterion

all: $(FILE_C)
	$(CC) -c -o $(FILE_O) $(FILE_C)

$(FILE_O): $(FILE_C)
	$(CC) $(CFLAGS) -c -o $(FILE_O) $(FILE_C)

test.o: tests/test.c
	$(CC) $(CFLAGS) -c -o tests/test.o tests/test.c

check: tests/test.o $(FILE_O)
	$(CC) -o check tests/test.o $(FILE_O) ${LDLIBS}

clean:
	rm -rf src/*.o tests/test tests/*.o
