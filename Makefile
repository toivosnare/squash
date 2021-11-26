CC=gcc

all: main.o squash.o
	$(CC) $(LDFLAGS) -o squash $^

shared: squash.o
	$(CC) $(LDFLAGS) -shared -o squash.so $<

static: squash.o
	ar rcs squash.a $<

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f *.o *.a *.so squash
