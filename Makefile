IDIR=.
CC = cc
CFLAGS=-I$(IDIR)
DEPS = renfa.h
OBJ = reNfa.o print.o stack.o list.o nfa.o memFree.o

%.o: %.c $(DEPS)
		$(CC) -c -o $@ $< $(CFLAGS)

renfa: $(OBJ)
		$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm reNfa.o nfa.o print.o stack.o list.o memFree.o renfa
