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

void copyFile()
{
	PPM* ppm = readPPM(INPUT_FILE);
	writePPM(OUTPUT_FILE, ppm);
}

void obscurate()
{
	PPM* ppm = readPPM(INPUT_FILE);
	for(int y = 0; y < ppm->header.height; y++)
	{
		for(int x = 0; x < ppm->header.width; x++)
		{
			dividePixel(getPixel(ppm, x, y), 2, 2, 2);
		}
	}	
	writePPM(OUTPUT_FILE, ppm);
}

int main1()
{
    printf("First Test : %f\n", timeCounterAverage(copyFile, 100));
    printf("Second Test : %f\n", timeCounterAverage(obscurate, 100));

    return EXIT_SUCCESS;
}

void growup(int mult){
	PPM* inPPM = readPPM(INPUT_FILE);
	Pixel** in = inPPM->content;

	int inWidth = getWidth(inPPM);
	int inHeight = getHeight(inPPM);

	Pixel** out;
	out = (Pixel**)malloc(sizeof(Pixel*));

	for(int y = 0; y < inHeight; y++){
		out[y] = (Pixel*)malloc(sizeof(Pixel));
		for(int i = 0; i < mult; i++){
			for(int x = 0; x < inWidth; x++){
				for(int j = 0; j < mult; j++){
					//printf("y = %i; i = %i; x = %i; j = %i\n", y, i, x, j);
					out[0][0] = *getRGB(getRed(getPixel(inPPM, x, y)), getGreen(getPixel(inPPM, x, y)), getBlue(getPixel(inPPM, x, y)));
					//out[mult*y+i][mult*x+j] = *getRGB(getRed(getPixel(inPPM, x, y)), getGreen(getPixel(inPPM, x, y)), getBlue(getPixel(inPPM, x, y)));
				}
			}	
		}

	}

	PPM outPPM;
	initPPM(&outPPM);
	setWidth(&outPPM, 1);
	//setWidth(&outPPM, inWidth*mult);
	setHeight(&outPPM, 1);
	//setHeight(&outPPM, inHeight*mult);
	setContent(&outPPM, out);
	writePPM(OUTPUT_FILE, &outPPM);	
}

int main(){
	growup(5);
}



