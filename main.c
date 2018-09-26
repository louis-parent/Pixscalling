#include <stdio.h>
#include <stdlib.h>
#include <time.h>
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
        if(i < 34){
            fputc(fgetc(in), out);
        }else{
            fputc(fgetc(in)+19000000, out);
        }
    }

    fclose(in);
    fclose(out);
}

/*int convert2(){

}*/

int main() {

    clock_t start, end;
    double cpu_time_used;

    start = clock();

    convert1();

    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

    printf("%f\n", cpu_time_used);
    
    return EXIT_SUCCESS;
}

