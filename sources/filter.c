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
	int mult = 3;

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

Matrix* epx(Matrix* matrix) {
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
			
			if(comparePixel(left, up) && !comparePixel(left, down) && !comparePixel(up, right)){
				set(out, 2*x, 2*y, copyPixel(up));
			}

			if(comparePixel(up, right) && !comparePixel(up, left) && !comparePixel(right, down)){
				set(out, 2*x+1, 2*y, copyPixel(right));
			}

			if(comparePixel(down, left) && !comparePixel(down, right) && !comparePixel(left, up)){
				set(out, 2*x, 2*y+1, copyPixel(left));
			}

			if(comparePixel(right, down) && !comparePixel(right, up) && !comparePixel(left, down)){
				set(out, 2*x+1, 2*y+1, copyPixel(down));
			}
		}
	}
	return out;
}

Matrix* scale3x(Matrix* matrix) {
	int mult = 3;

	int inWidth = matrixColumns(matrix);
	int inHeight = matrixLines(matrix);

	Matrix* out = createMatrix(inWidth * mult, inHeight * mult);

	for(int y = 0; y < inHeight; y++){
		for(int x = 0; x < inWidth; x++){
			
			set(out, mult*x, mult*y, copyPixel(select(matrix, x, y)));
			set(out, mult*x+1, mult*y, copyPixel(select(matrix, x, y)));
			set(out, mult*x+2, mult*y, copyPixel(select(matrix, x, y)));
			set(out, mult*x, mult*y+1, copyPixel(select(matrix, x, y)));
			set(out, mult*x, mult*y+2, copyPixel(select(matrix, x, y)));
			set(out, mult*x+1, mult*y+1, copyPixel(select(matrix, x, y)));
			set(out, mult*x+2, mult*y+2, copyPixel(select(matrix, x, y)));
			set(out, mult*x+2, mult*y+1, copyPixel(select(matrix, x, y)));
			set(out, mult*x+1, mult*y+2, copyPixel(select(matrix, x, y)));

			// A
			Pixel* a = select(matrix, x, y);
			if(y > 0 && x > 0){
				a = select(matrix, x-1, y-1);
			}

			// B
			Pixel* b = select(matrix, x, y);
			if(y > 0){
				b = select(matrix, x, y-1);
			}

			// C
			Pixel* c = select(matrix, x, y);
			if(y > 0 && x < inWidth-1){
				c = select(matrix, x+1, y-1);
			}

			// D
			Pixel* d = select(matrix, x, y);
			if(x > 0){
				d = select(matrix, x-1, y);
			}

			// E
			Pixel* e = select(matrix, x, y);

			// F
			Pixel* f = select(matrix, x, y);
			if(x < inWidth-1){
				f = select(matrix, x+1, y);
			}

			// G
			Pixel* g = select(matrix, x, y);
			if(y < inHeight-1 && x > 0){
				g = select(matrix, x-1, y+1);
			}

			// H
			Pixel* h = select(matrix, x, y);
			if(y < inHeight-1){
				h = select(matrix, x, y+1);
			}

			// I
			Pixel* i = select(matrix, x, y);
			if(y < inHeight-1 && x < inWidth-1){
				i = select(matrix, x+1, y+1);
			}

			if(comparePixel(d, b) && !comparePixel(d, h) && !comparePixel(b, f)){
				set(out, mult*x, mult*y, copyPixel(d));
			}

			if((comparePixel(d, b) && !comparePixel(d, h) && !comparePixel(b, f) && !comparePixel(e, c)) || (comparePixel(b, f) && !comparePixel(b, d) && !comparePixel(f, h) && !comparePixel(e, a))){
				set(out, mult*x+1, mult*y, copyPixel(b));
			}

			if(comparePixel(b, f) && !comparePixel(b, d) && !comparePixel(f, h)){
				set(out, mult*x+2, mult*y, copyPixel(f));
			}

			if((comparePixel(h, d) && !comparePixel(h, f) && !comparePixel(d, b) && !comparePixel(e, a)) || (comparePixel(d, b) && !comparePixel(d, h) && !comparePixel(b, f) && !comparePixel(e, g))){
				set(out, mult*x, mult*y+1, copyPixel(d));
			}

			set(out, mult*x+1, mult*y+1, copyPixel(e));

			// ICI
			if((comparePixel(b, f) && !comparePixel(b, d) && !comparePixel(f, h) && !comparePixel(e, i)) || (comparePixel(f, h) && !comparePixel(f, b) && !comparePixel(h, d) && !comparePixel(e, c))){
				set(out, mult*x+2, mult*y+1, copyPixel(f));
			}

			if(comparePixel(h, d) && !comparePixel(h, f) && !comparePixel(d, b)){
				set(out, mult*x, mult*y+2, copyPixel(d));
			}

			if((comparePixel(f, h) && !comparePixel(f, b) && !comparePixel(h, d) && !comparePixel(e, g)) || (comparePixel(h, d) && !comparePixel(h, f) && !comparePixel(d, b) && !comparePixel(e, i))){
				set(out, mult*x+1, mult*y+2, copyPixel(h));
			}

			if(comparePixel(h, f) && !comparePixel(f, b) && !comparePixel(h, d)){
				set(out, mult*x+2, mult*y+2, copyPixel(f));
			}
/*
			if(comparePixel(left, up) && !comparePixel(left, down) && !comparePixel(up, right)){
				set(out, 2*x, 2*y, copyPixel(up));
			}

			if(comparePixel(up, right) && !comparePixel(up, left) && !comparePixel(right, down)){
				set(out, 2*x+1, 2*y, copyPixel(right));
			}

			if(comparePixel(down, left) && !comparePixel(down, right) && !comparePixel(left, up)){
				set(out, 2*x, 2*y+1, copyPixel(left));
			}

			if(comparePixel(right, down) && !comparePixel(right, up) && !comparePixel(left, down)){
				set(out, 2*x+1, 2*y+1, copyPixel(down));
			}
*/
		}
	}
	return out;
}

Matrix* eagle(Matrix* matrix) {
	int mult = 2;

	int inWidth = matrixColumns(matrix);
	int inHeight = matrixLines(matrix);

	Matrix* out = createMatrix(inWidth * mult, inHeight * mult);

	for(int yCursor = 0; yCursor < inHeight; yCursor++){
		for(int xCursor = 0; xCursor < inWidth; xCursor++){
			
			set(out, mult*xCursor, mult*yCursor, copyPixel(select(matrix, xCursor, yCursor)));
			set(out, mult*xCursor+1, mult*yCursor, copyPixel(select(matrix, xCursor, yCursor)));
			set(out, mult*xCursor, mult*yCursor+1, copyPixel(select(matrix, xCursor, yCursor)));
			set(out, mult*xCursor+1, mult*yCursor+1, copyPixel(select(matrix, xCursor, yCursor)));

			// S
			Pixel* s = select(matrix, xCursor, yCursor);
			if(yCursor > 0 && xCursor > 0){
				s = select(matrix, xCursor-1, yCursor-1);
			}

			// T
			Pixel* t = select(matrix, xCursor, yCursor);
			if(yCursor > 0){
				t = select(matrix, xCursor, yCursor-1);
			}

			// U
			Pixel* u = select(matrix, xCursor, yCursor);
			if(yCursor > 0 && xCursor < inWidth-1){
				u = select(matrix, xCursor+1, yCursor-1);
			}

			// V
			Pixel* v = select(matrix, xCursor, yCursor);
			if(xCursor > 0){
				v = select(matrix, xCursor-1, yCursor);
			}

			// C
			Pixel* c = select(matrix, xCursor, yCursor);

			// W
			Pixel* w = select(matrix, xCursor, yCursor);
			if(xCursor < inWidth-1){
				w = select(matrix, xCursor+1, yCursor);
			}

			// X
			Pixel* x = select(matrix, xCursor, yCursor);
			if(yCursor < inHeight-1 && xCursor > 0){
				x = select(matrix, xCursor-1, yCursor+1);
			}

			// Y
			Pixel* y = select(matrix, xCursor, yCursor);
			if(yCursor < inHeight-1){
				y = select(matrix, xCursor, yCursor+1);
			}

			// Z
			Pixel* z = select(matrix, xCursor, yCursor);
			if(yCursor < inHeight-1 && xCursor < inWidth-1){
				z = select(matrix, xCursor+1, yCursor+1);
			}

			if(comparePixel(v, s) && comparePixel(s, t) && comparePixel(v, t)){
				set(out, mult*xCursor, mult*yCursor, copyPixel(s));
			}

			if(comparePixel(t, u) && comparePixel(u, w) && comparePixel(t, w)){
				set(out, mult*xCursor+1, mult*yCursor, copyPixel(u));
			}

			if(comparePixel(v, x) && comparePixel(x, y) && comparePixel(v, y)){
				set(out, mult*xCursor, mult*yCursor+1, copyPixel(x));
			}

			if(comparePixel(w, z) && comparePixel(z, y) && comparePixel(w, y)){
				set(out, mult*xCursor+1, mult*yCursor+1, copyPixel(z));
			}

		}
	}
	return out;
}

void applyFilter(PPM* ppm, Matrix* (*filter)(Matrix*), int count)
{
	for(int i = 0; i < count ; i++)
	{
		Matrix* newMatrix = (*filter)(getContent(ppm));
		
		setContent(ppm, newMatrix);
		setWidth(ppm, matrixColumns(getContent(ppm)));
		setHeight(ppm, matrixLines(getContent(ppm)));		
	}
}
