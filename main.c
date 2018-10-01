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
#include "headers/matrix.h"
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

	PPM* outPPM = createPPM(out, inWidth*mult, inHeight*mult);
	writePPM(OUTPUT_FILE, outPPM);
	
	removePPM(inPPM);
	removePPM(outPPM);
}

void upscale(){
	growup(5);
}

Pixel* arroUp(Matrix* matrice, int x, int y){
	if(y <= 0){
		return select(matrice, x, y);
	}
	return select(matrice, x, y-1);
}

Pixel* arroDown(Matrix* matrice, int x, int y){
	return select(matrice, x, y+1);
}

Pixel* arroLeft(Matrix* matrice, int x, int y){
	if(x <= 0){
		return select(matrice, x, y);
	}
	return select(matrice, x-1, y);
}

Pixel* arroRight(Matrix* matrice, int x, int y){
	if(x >= getWidth(matrice)){
		return select(matrice, x, y);
	}
	return select(matrice, x+1, y);
}

int comparePixel(Pixel* a, Pixel* b){
	return getRed(a) == getRed(b) && getGreen(a) == getGreen(b) && getBlue(a) == getBlue(b);
}





	void test()
{
	printf("Begining Test :\n");
    printf("\t- Simple Copy Test : %f\n", timeCounterAverage(copyFile, 100));
   	printf("\t- Obscurate Test : %f\n", timeCounterAverage(obscurate, 100));
   	printf("\t- Shade of Grey Test : %f\n", timeCounterAverage(toGrayMap, 100));
    printf("\t- Negative Test : %f\n", timeCounterAverage(negative, 100));
    printf("\t- Simple Upscale Test : %f\n", timeCounterAverage(upscale, 1));
}

int main()
{
	int mult = 2;
	PPM* inPPM = readPPM(INPUT_FILE);
	Matrix* in = getContent(inPPM);

	int inWidth = getWidth(inPPM);
	int inHeight = getHeight(inPPM);

	Matrix* out = createMatrix(inWidth * mult, inHeight * mult);

	for(int y = 0; y < inHeight; y++){
		for(int x = 0; x < inWidth; x++){

			set(out, 2*x, 2*y, copyPixel(getPixel(inPPM, x, y)));
			set(out, 2*x+1, 2*y, copyPixel(getPixel(inPPM, x, y)));
			set(out, 2*x, 2*y+1, copyPixel(getPixel(inPPM, x, y)));
			set(out, 2*x+1, 2*y+1, copyPixel(getPixel(inPPM, x, y)));

			// UP
			Pixel* up = select(in, x, y);
			if(y > 0){
				up = select(in, x, y-1);
			}

			// Down
			Pixel* down = select(in, x, y);
			if(y < inWidth-1){
				down = select(in, x, y+1);
			}

			// Left
			Pixel* left = select(in, x, y);
			if(x > 0){
				left = select(in, x-1, y);
			}

			// Right
			Pixel* right = select(in, x, y);
			if(x < inHeight-1){
				right = select(in, x+1, y);
			}


			if(comparePixel(up, left)){
				set(out, 2*x, 2*y, up);
			}

			if(comparePixel(up, right)){
				set(out, 2*x+1, 2*y, up);
			}
/* A CORRIGER !!!
			if(comparePixel(down, left) && y+1 < inHeight){
				set(out, 2*x, 2*y+1, left);
			}

			if(comparePixel(down, right)){
				set(out, 2*x+1, 2*y+1, down);
			}
*/
			//set(out, mult*x+j, mult*y+i, copyPixel(getPixel(inPPM, x, y)));
				
			
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

    return EXIT_SUCCESS;
}

/*
					Pixel* up = arroUp(in, x, y);
					Pixel* down = arroDown(in, x, y);
					Pixel* left = arroLeft(in, x, y);
					Pixel* right = arroRight(in, x, y);
*/