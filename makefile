CC=gcc
CFLAGS=-W -Wall -ansi -pedantic -std=c99
LDFLAGS=
EXEC=pixscalling

all: $(EXEC)

pixscalling: bin/main.o bin/ppm.o bin/timer.o bin/pixel.o bin/matrix.o
	@$(CC) -o $@ $^ $(LDFLAGS)

bin/pixel.o: sources/pixel.c headers/pixel.h
	@$(CC) -o bin/pixel.o -c sources/pixel.c $(CFLAGS)

bin/matrix.o: sources/matrix.c headers/matrix.h headers/pixel.h
	@$(CC) -o bin/matrix.o -c sources/matrix.c $(CFLAGS)

bin/ppm.o: sources/ppm.c headers/ppm.h headers/pixel.h headers/matrix.h
	@$(CC) -o bin/ppm.o -c sources/ppm.c $(CFLAGS)

bin/timer.o: sources/timer.c headers/timer.h
	@$(CC) -o bin/timer.o -c sources/timer.c $(CFLAGS)

bin/main.o: main.c headers/ppm.h headers/timer.h headers/pixel.h headers/matrix.h
	@$(CC) -o bin/main.o -c main.c $(CFLAGS)

clean:
	@rm -rf bin/*.o

mrproper: clean
	@rm -rf $(EXEC)
