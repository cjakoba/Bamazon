CC=gcc
CFLAGS=-Wall

CFILES=main.c bamazon.c
OBJECTS=main.o bamazon.o
HEADERS=bamazon.h

# Final executable filename
BINARY=bamazon

all: $(BINARY)

$(BINARY): $(OBJECTS)
	$(CC) -o $@ $^

%.o:%.c $(HEADERS)
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -rf $(BINARY) *.o
