CC=gcc
CFLAGS=-I.
HEADERS_SRC = wordfreqq.h wordfreq.c
OBJ = wordfreqq.o wordfreq.o
PROG = wordfreak

%.o: %.c $(HEADERS_SRC)
	$(CC) -c -o $@ $< $(CFLAGS)

$(PROG): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)