CFLAGS=-std=c11 -g -static -fno-common
SRCS=$(wildcard *.c)
OBJS=$(SRCS:.c=.o)

tinycc: $(OBJS)
	$(CC) -o $@ $(OBJS) $(LDFLAGS)

$(OBJS): tiny.h

test: tinycc
	./tinycc tests > tmp.s
	gcc -static -o tmp tmp.s
	./tmp

clean:
	rm -f tinycc *.o *~ tmp*

.PHONY: test clean
