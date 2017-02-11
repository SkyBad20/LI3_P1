# Makefile para o projecto de LI3
CFLAGS=-ansi -O2 -Wall -pedantic
OBJS=$(patsubst %.c,%.o,$(wildcard *.c))
LIBS=

prot: $(OBJS)
	$(CC) $(CFLAGS) -o prot $(OBJS) $(LIBS)

do: prot
	./prot

clean:
	rm prot *.o
