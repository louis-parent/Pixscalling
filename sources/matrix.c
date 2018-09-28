#include <stdlib.h>
#include "../headers/matrix.h"

void initMatrix(Matrix* matrix)
{
    matrix->lines = 0;
    matrix->columns = 0;

    matrix->matrix = NULL;
}

Matrix* createMatrix(int lines, int columns)
{
    Matrix* matrix = malloc(sizeof(Matrix));
    initMatrix(matrix);

    matrix->matrix = (Pixel**) malloc(columns * sizeof(Pixel*));

    for(int y = 0; y < columns; y++)
    {
        matrix->matrix[y] = (Pixel*) malloc(lines * sizeof(Pixel));
        for(int x = 0; x < lines; x++)
        {
            matrix->matrix[y][x] = *getRGB(255, 255, 255);
        }
    }
    
    return matrix;
}

void changeMatrix(Matrix* matrix, int lines, int columns)
{
    matrix = createMatrix(lines, columns);
}

int matrixLines(Matrix* matrix)
{
    return matrix->lines;
}

int matrixColumns(Matrix* matrix)
{
    return matrix->columns;
}

int matrixSize(Matrix* matrix)
{
    return matrixLines(matrix) * matrixColumns(matrix);
}

Pixel* select(Matrix* matrix, int x, int y)
{
    return &matrix->matrix[y][x];
}

void set(Matrix* matrix, int x, int y, Pixel* pixel)
{
    matrix->matrix[y][x] = *pixel;
}
