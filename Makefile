CFLAGS=-std=c11 -g -static -fno-common
SRCS=$(wildcard *.c)
OBJS=$(SRCS:.c=.o)

tinycc: $(OBJS)
	$(CC) -o $@ $(OBJS) $(LDFLAGS)

$(OBJS): tiny.h

test: tinycc
	./tinycc tests > tmp.s
	echo 'int ext1; int *ext2; int char_fn() { return 257; }' \
		'int static_fn() { return 5; }' | \
		gcc -xc -c -o tmp2.o -
	gcc -static -o tmp tmp.s tmp2.o
	./tmp

clean:
	rm -f tinycc *.o *~ tmp*

.PHONY: test clean
