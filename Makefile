CFLAGS=-std=c11 -g -static -fno-common

tinycc: main.o
	$(CC) -o tinycc main.o $(LDFLAGS)

test: tinycc
	./test.sh

clean:
	rm -f tinycc *.o *~ tmp*

.PHONY: test clean
