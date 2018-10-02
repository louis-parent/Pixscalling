#include <stdlib.h>
#include "../headers/pixel.h"
#include "../headers/matrix.h"
#include "../headers/filter.h"

void obscurate(PPM* ppm)
{
	for(int y = 0; y < ppm->header->height; y++)
	{
		for(int x = 0; x < ppm->header->width; x++)
		{
			dividePixel(getPixel(ppm, x, y), 2, 2, 2);
		}
	}
}

void toGrayMap(PPM* ppm)
{
	for(int y = 0; y < ppm->header->height; y++)
	{
		for(int x = 0; x < ppm->header->width; x++)
		{
			char grayLevel = 0.299 * getRed(getPixel(ppm, x, y)) +  0.587 * getGreen(getPixel(ppm, x, y)) + 0.114 * getBlue(getPixel(ppm, x, y));
			setPixel(ppm, x, y, getRGB(grayLevel, grayLevel, grayLevel));
		}
	}
}

void negative(PPM* ppm)
{
	for(int y = 0; y < ppm->header->height; y++)
	{
		for(int x = 0; x < ppm->header->width; x++)
		{
			setPixel(ppm, x, y, getRGB(255 - getRed(getPixel(ppm, x, y)), 255 - getGreen(getPixel(ppm, x, y)), 255 - getBlue(getPixel(ppm, x, y))));
		}
	}
}

void growup(PPM* ppm, int mult){
	Matrix* in = getContent(ppm);

	int inWidth = getWidth(ppm);
	int inHeight = getHeight(ppm);

	Matrix* out = createMatrix(inWidth * mult, inHeight * mult);

	for(int y = 0; y < inHeight; y++){
		for(int i = 0; i < mult; i++){
			for(int x = 0; x < inWidth; x++){
				for(int j = 0; j < mult; j++){
				
					set(out, mult*x+j, mult*y+i, copyPixel(getPixel(ppm, x, y)));
				}
			}
		}

	}
	
	setContent(ppm, out);
	setWidth(ppm, inWidth * mult);
	setHeight(ppm, inHeight * mult);
}

void scale2x(PPM* ppm)
{
	int mult = 2;
	Matrix* in = getContent(ppm);

	int inWidth = getWidth(ppm);
	int inHeight = getHeight(ppm);

	Matrix* out = createMatrix(inWidth * mult, inHeight * mult);

	for(int y = 0; y < inHeight; y++){
		for(int x = 0; x < inWidth; x++){
			
			set(out, 2*x, 2*y, copyPixel(getPixel(ppm, x, y)));
			set(out, 2*x+1, 2*y, copyPixel(getPixel(ppm, x, y)));
			set(out, 2*x, 2*y+1, copyPixel(getPixel(ppm, x, y)));
			set(out, 2*x+1, 2*y+1, copyPixel(getPixel(ppm, x, y)));

			// UP
			Pixel* up = select(in, x, y);
			if(y > 0){
				up = select(in, x, y-1);
			}

			// Down
			Pixel* down = select(in, x, y);
			if(y < inHeight-1){
				down = select(in, x, y+1);
			}

			// Left
			Pixel* left = select(in, x, y);
			if(x > 0){
				left = select(in, x-1, y);
			}
			
			// Right
			Pixel* right = select(in, x, y);
			if(x < inWidth-1){
				right = select(in, x+1, y);
			}

			if(comparePixel(up, left)){
				set(out, 2*x, 2*y, up);
			}

			if(comparePixel(up, right)){
				set(out, 2*x+1, 2*y, up);
			}

			if(comparePixel(down, left) && y+1 < inHeight){
				set(out, 2*x, 2*y+1, left);
			}

			if(comparePixel(down, right)){
				set(out, 2*x+1, 2*y+1, down);
			}
		}
	}

	setWidth(ppm, inWidth*mult);
	setHeight(ppm, inHeight*mult);
	setContent(ppm, out);
}
