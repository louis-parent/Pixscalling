#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>

#include "headers/ppm.h"
#include "headers/pixel.h"
#include "headers/timer.h"

#define INPUT_FILE "in.ppm"
#define OUTPUT_FILE "out.ppm"

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

/*void bmpToInt()
{
    FILE *in;
    FILE *out;

    in = fopen(INPUT_FILE, "rb");
    out = fopen("out1.bmp", "wb");

    fseek(in, 0L, SEEK_END);
    int size = ftell(in);
    fseek(in, 0L, SEEK_SET);

    for(int i = 0; i < size; i++){
       	unsigned char bgrpix[3];
       	fread(&bgrpix,1,3,in);
       	printf("%s -> r:%x, g:%x, b:%x\n", bgrpix, bgrpix[0], bgrpix[1], bgrpix[2]);
    }

    fclose(in);
    fclose(out);
}*/

void copyFile()
{
	PPM* ppm = readPPM(INPUT_FILE);
	writePPM(OUTPUT_FILE, ppm);
}

/*void obscurate()
{
	PPM* ppm = readPPM(INPUT_FILE);
	for(int y = 0; y < ppm->header.height; y++)
	{
		for(int x = 0; x < ppm->header.width; x++)
		{
			for(int z = 0; z < 3; z++)
			{
				ppm->content[y][x][z] = ppm->content[y][x][z]/2;
			}
		}
	}	
	writePPM(OUTPUT_FILE, ppm);
}*/

int main()
{
    printf("First Test : %f\n", timeCounterAverage(copyFile, 100));
    //printf("Second Test : %f\n", timeCounterAverage(obscurate, 100));
	//copyFile();

    return EXIT_SUCCESS;
}



