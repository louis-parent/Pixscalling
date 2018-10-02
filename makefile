CC=gcc
CFLAGS=-W -Wall -ansi -pedantic -std=c99
LDFLAGS=
EXEC=pixscalling

all: $(EXEC)

bin/pixel.o: sources/pixel.c headers/pixel.h 
	@$(CC) -o bin/pixel.o -c sources/pixel.c $(CFLAGS)

bin/matrix.o: sources/matrix.c headers/matrix.h headers/pixel.h 
	@$(CC) -o bin/matrix.o -c sources/matrix.c $(CFLAGS)

bin/ppm.o: sources/ppm.c headers/ppm.h headers/matrix.h headers/pixel.h 
	@$(CC) -o bin/ppm.o -c sources/ppm.c $(CFLAGS)

bin/filter.o: sources/filter.c headers/filter.h headers/pixel.h headers/ppm.h headers/matrix.h 
	@$(CC) -o bin/filter.o -c sources/filter.c $(CFLAGS)

bin/timer.o: sources/timer.c headers/timer.h 
	@$(CC) -o bin/timer.o -c sources/timer.c $(CFLAGS)

bin/main.o: main.c headers/pixel.h headers/matrix.h headers/ppm.h headers/filter.h headers/timer.h 
	@$(CC) -o bin/main.o -c main.c $(CFLAGS)

pixscalling: bin/pixel.o bin/matrix.o bin/ppm.o bin/filter.o bin/timer.o bin/main.o 
	@$(CC) -o $@ $^ $(LDFLAGS)

clean:
	@rm -rf bin/*.o

mrproper: clean
	@rm -rf $(EXEC)

