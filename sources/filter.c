#include <stdlib.h>
#include <stdio.h>
#include "../headers/pixel.h"
#include "../headers/filter.h"

void obscurate(Matrix* matrix)
{
	for(int y = 0; y < matrixLines(matrix); y++)
	{
		for(int x = 0; x < matrixColumns(matrix); x++)
		{
			dividePixel(select(matrix, x, y), 2, 2, 2);
		}
	}
}

void toGrayMap(Matrix* matrix)
{
	for(int y = 0; y < matrixLines(matrix); y++)
	{
		for(int x = 0; x < matrixColumns(matrix); x++)
		{
			char grayLevel = 0.299 * getRed(select(matrix, x, y)) +  0.587 * getGreen(select(matrix, x, y)) + 0.114 * getBlue(select(matrix, x, y));
			set(matrix, x, y, getRGB(grayLevel, grayLevel, grayLevel));
		}
	}
}

void negative(Matrix* matrix)
{
	for(int y = 0; y < matrixLines(matrix); y++)
	{
		for(int x = 0; x < matrixColumns(matrix); x++)
		{
			set(matrix, x, y, getRGB(255 - getRed(select(matrix, x, y)), 255 - getGreen(select(matrix, x, y)), 255 - getBlue(select(matrix, x, y))));
		}
	}
}

Matrix* growup(Matrix* matrix){
	int mult = 2;

	int inWidth = matrixColumns(matrix);
	int inHeight = matrixLines(matrix);

	Matrix* out = createMatrix(inWidth * mult, inHeight * mult);

	for(int y = 0; y < inHeight; y++){
		for(int i = 0; i < mult; i++){
			for(int x = 0; x < inWidth; x++){
				for(int j = 0; j < mult; j++){
				
					set(out, mult*x+j, mult*y+i, copyPixel(select(matrix, x, y)));
				}
			}
		}

	}
	return out;
}

Matrix* scale2x(Matrix* matrix) {
	int mult = 2;

	int inWidth = matrixColumns(matrix);
	int inHeight = matrixLines(matrix);

	Matrix* out = createMatrix(inWidth * mult, inHeight * mult);

	for(int y = 0; y < inHeight; y++){
		for(int x = 0; x < inWidth; x++){
			
			set(out, 2*x, 2*y, copyPixel(select(matrix, x, y)));
			set(out, 2*x+1, 2*y, copyPixel(select(matrix, x, y)));
			set(out, 2*x, 2*y+1, copyPixel(select(matrix, x, y)));
			set(out, 2*x+1, 2*y+1, copyPixel(select(matrix, x, y)));

			// UP
			Pixel* up = select(matrix, x, y);
			if(y > 0){
				up = select(matrix, x, y-1);
			}

			// Down
			Pixel* down = select(matrix, x, y);
			if(y < inHeight-1){
				down = select(matrix, x, y+1);
			}

			// Left
			Pixel* left = select(matrix, x, y);
			if(x > 0){
				left = select(matrix, x-1, y);
			}
			
			// Right
			Pixel* right = select(matrix, x, y);
			if(x < inWidth-1){
				right = select(matrix, x+1, y);
			}

			if(comparePixel(up, left)){
				set(out, 2*x, 2*y, copyPixel(up));
			}

			if(comparePixel(up, right)){
				set(out, 2*x+1, 2*y, copyPixel(up));
			}

			if(comparePixel(down, left) && y+1 < inHeight){
				set(out, 2*x, 2*y+1, copyPixel(left));
			}

			if(comparePixel(down, right)){
				set(out, 2*x+1, 2*y+1, copyPixel(down));
			}
		}
	}
	return out;
}

void applyFilter(PPM* ppm, Matrix* (*filter)(Matrix*))
{
	Matrix* newMatrix = (*filter)(getContent(ppm));
	
	setContent(ppm, newMatrix);
	setWidth(ppm, matrixColumns(getContent(ppm)));
	setHeight(ppm, matrixLines(getContent(ppm)));
}
