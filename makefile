CC=gcc
CFLAGS=-W -Wall -ansi -pedantic -std=c99
LDFLAGS=
EXEC=pixscalling

all: $(EXEC)

pixscalling: bin/main.o bin/bitmap.o bin/timer.o
	@$(CC) -o $@ $^ $(LDFLAGS)

bin/bitmap.o: sources/bitmap.c headers/bitmap.h
	@$(CC) -o bin/bitmap.o -c sources/bitmap.c $(CFLAGS)
	
bin/timer.o: sources/timer.c headers/timer.h
	@$(CC) -o bin/timer.o -c sources/timer.c $(CFLAGS)

bin/main.o: main.c headers/bitmap.h headers/timer.h
	@$(CC) -o bin/main.o -c main.c $(CFLAGS)

clean:
	@rm -rf bin/*.o

mrproper: clean
	@rm -rf $(EXEC)
