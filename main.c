#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "headers/bitmap.h"

#define INPUT_FILE "in.bmp"

void convert1(){
    FILE *in;
    FILE *out;

    in = fopen(INPUT_FILE, "rb");
    out = fopen("out.bmp", "wb");

    fseek(in, 0L, SEEK_END);
    int size = ftell(in);
    fseek(in, 0L, SEEK_SET);

    for(int i = 0; i < size; i++){
        char c = fgetc(in);
        if(i < 34){
            fputc(c, out);
        }else{
            fputc(c, out);
        }
    }

    fclose(in);
    fclose(out);
}

void bmpToInt(){
    FILE *in;
    FILE *out;

    in = fopen(INPUT_FILE, "rb");
    out = fopen("out1.bmp", "wb");

    fseek(in, 0L, SEEK_END);
    int size = ftell(in);
    fseek(in, 0L, SEEK_SET);

    for(int i = 0; i < size; i++){
        char c = fgetc(in);
        fprintf(out, "%i\n", c);
    }

    fclose(in);
    fclose(out);
}

void intToBmp(){
    FILE *in;
    FILE *out;

    in = fopen("out1.bmp", "rb");
    out = fopen("out2.bmp", "wb");

    fseek(in, 0L, SEEK_END);
    int size = ftell(in);
    fseek(in, 0L, SEEK_SET);

    int count = 0;
    char c;

    while((c = fgetc(in)) != EOF){
        char buffer[4];
        do{
            buffer[count] = c;
            count++;
        }while((c = fgetc(in)) != '\n');
        buffer[count] = ' ';
        fprintf(out, "%c", (signed int) atoi(buffer));
        count = 0;
    }

    fclose(in);
    fclose(out);
}



double timeCounter(void (*ptr)()){
    clock_t start, end;

    start = clock();

    (*ptr)();

    end = clock();
    return ((double) (end - start)) / CLOCKS_PER_SEC;
}

double timeCounterAverage(void (*ptr)(), int n){
    double sum = .0;
    for(int i = 0; i < n; i++){
        sum += timeCounter(ptr);
    }
    return sum/n;
}

int main() {
    bmpToInt();
    intToBmp();

    return EXIT_SUCCESS;
}



