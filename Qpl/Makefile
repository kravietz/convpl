CFLAGS=-DNDEBUG -O2
LDFLAGS=-s -O2

qpl: Qpl.o polish.o
	$(CC) $(LDFLAGS) -o qpl $^

clean:
	-rm *.o qpl
