#ifndef H_MATRIX
#define H_MATRIX

#include "../headers/pixel.h"

typedef struct Matrix Matrix;
struct Matrix
{
    int lines;
    int columns;

    Pixel** matrix;
};

void initMatrix(Matrix* matrix);
Matrix* createMatrix(int lines, int columns);
void changeMatrix(Matrix* matrix, int lines, int columns);

int matrixLines(Matrix* matrix);
int matrixColumns(Matrix* matrix);

int matrixSize(Matrix* matrix);

Pixel* select(Matrix* matrix, int x, int y);
void set(Matrix* matrix, int x, int y, Pixel* pixel);

void removeMatrix(Matrix* matrix);

#endif
