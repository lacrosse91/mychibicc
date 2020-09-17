CFLAGS=-std=c11 -g -static -fno-common
SRCS=$(wildcard *.c)
OBJS=$(SRCS:.c=.o)

tinycc-gen2: tinycc $(SRCS) tiny.h
	./self.sh

extern.o: tests-extern
	gcc -xc -c -o extern.o tests-extern

tinycc: $(OBJS)
	$(CC) -o $@ $(OBJS) $(LDFLAGS)

$(OBJS): tiny.h

test: tinycc extern.o
	./tinycc tests > tmp.s
	gcc -static -o tmp tmp.s extern.o
	./tmp

test-gen2: tinycc-gen2 extern.o
	./chibicc-gen2 tests > tmp.s
	gcc -static -o tmp tmp.s extern.o
	./tmp

clean:
	rm -rf tinycc tinycc-gen* *.o *~ tmp*

.PHONY: test clean
