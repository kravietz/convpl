CFLAGS=-DNDEBUG -DNO_LINE_CNT -O2
LDFLAGS=-s -O2

cpl: cpl.o polish.o disph.o
	$(CC) $(LDFLAGS) -o cpl $^

clean:
	-rm *.o cpl
