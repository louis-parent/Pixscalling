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
	removePPM(ppm);
}

void obscurate()
{
	PPM* ppm = readPPM(INPUT_FILE);
	for(int y = 0; y < ppm->header->height; y++)
	{
		for(int x = 0; x < ppm->header->width; x++)
		{
			dividePixel(getPixel(ppm, x, y), 2, 2, 2);
		}
	}
	writePPM(OUTPUT_FILE, ppm);
	removePPM(ppm);
}

void toGrayMap()
{
	PPM* ppm = readPPM(INPUT_FILE);
	for(int y = 0; y < ppm->header->height; y++)
	{
		for(int x = 0; x < ppm->header->width; x++)
		{
			char grayLevel = 0.299 * getRed(getPixel(ppm, x, y)) +  0.587 * getGreen(getPixel(ppm, x, y)) + 0.114 * getBlue(getPixel(ppm, x, y));
			setPixel(ppm, x, y, getRGB(grayLevel, grayLevel, grayLevel));
		}
	}
	writePPM(OUTPUT_FILE, ppm);
	removePPM(ppm);
}

void negative()
{
	PPM* ppm = readPPM(INPUT_FILE);
	for(int y = 0; y < ppm->header->height; y++)
	{
		for(int x = 0; x < ppm->header->width; x++)
		{
			setPixel(ppm, x, y, getRGB(255 - getRed(getPixel(ppm, x, y)), 255 - getGreen(getPixel(ppm, x, y)), 255 - getBlue(getPixel(ppm, x, y))));
		}
	}
	writePPM(OUTPUT_FILE, ppm);
	removePPM(ppm);
}

void growup(int mult){
	PPM* inPPM = readPPM(INPUT_FILE);
	Matrix* in = getContent(inPPM);

	int inWidth = getWidth(inPPM);
	int inHeight = getHeight(inPPM);

	Matrix* out = createMatrix(inWidth * mult, inHeight * mult);

	for(int y = 0; y < inHeight; y++){
		for(int i = 0; i < mult; i++){
			for(int x = 0; x < inWidth; x++){
				for(int j = 0; j < mult; j++){
				
					set(out, mult*x+j, mult*y+i, copyPixel(getPixel(inPPM, x, y)));
				}
			}
		}

	}

	PPM* outPPM = malloc(sizeof(PPM));
	initPPM(outPPM);
	setWidth(outPPM, inWidth*mult);
	setHeight(outPPM, inHeight*mult);
	setContent(outPPM, out);
	writePPM(OUTPUT_FILE, outPPM);
	
	removePPM(inPPM);
	removePPM(outPPM);
}

void upscale(){
	growup(5);
}

void test()
{
	printf("Begining Test :\n");
    printf("\t- Simple Copy Test : %f\n", timeCounterAverage(copyFile, 100));
   	printf("\t- Obscurate Test : %f\n", timeCounterAverage(obscurate, 100));
   	printf("\t- Shade of Grey Test : %f\n", timeCounterAverage(toGrayMap, 100));
    printf("\t- Negative Test : %f\n", timeCounterAverage(negative, 100));
    printf("\t- Simple Upscale Test : %f\n", timeCounterAverage(upscale, 10));
}

int main()
{
	//test();
	toGrayMap();
    return EXIT_SUCCESS;
}
