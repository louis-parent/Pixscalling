#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "headers/bitmap.h"
#include "headers/timer.h"

#define INPUT_FILE "in.bmp"
#define OUTPUT_FILE "out.bmp"

// FIRST VERSION FOR NEGATIVE
/*void convert1()
{
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
}*/

// OLD VERSION FOR CONVERTING FROM BMP TO INT ARRAY
/*void bmpToInt(){
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
}*/


// OLD VERSION FOR CONVERTING FROM INT ARRAY TO BMP
/*void intToBmp(){
    FILE *in;
    FILE *out;

    in = fopen("out1.bmp", "rb");
    out = fopen(OUTPUT_FILE, "wb");

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
}*/

void copyFile()
{
	Bitmap bitmap = readBitmap(INPUT_FILE);
	writeBitmap(OUTPUT_FILE, &bitmap);
}

int main()
{
    printf("First Test : %f\n", timeCounterAverage(copyFile, 100));

    return EXIT_SUCCESS;
}



