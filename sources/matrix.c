#include <stdlib.h>
#include <stdio.h>
#include "../headers/matrix.h"
#include "../headers/memory.h"

void initMatrix(Matrix* matrix)
{
    matrix->lines = 0;// by default there are 0 line
    matrix->columns = 0;// by default there are 0 column

    matrix->matrix = NULL;// By default the matrix is empty
}

Matrix* createMatrix(int columns, int lines)
{
    Matrix* matrix = labelMalloc(sizeof(Matrix), "Matrix Creation");// labelMalloc memory for Matrix
    initMatrix(matrix);// Init an empty Matrix

    matrix->matrix = (Pixel***) labelMalloc(lines * sizeof(Pixel**), "Matrix Lines Array"); // labelMalloc the array of columns
    for(int y = 0; y < lines; y++)
    {
        matrix->matrix[y] = (Pixel**) labelMalloc(columns * sizeof(Pixel*), "Matrix Column Array");// labelMalloc the lines for the column y
        for(int x = 0; x < columns; x++)
        {
            matrix->matrix[y][x] = getRGB(255, 255, 255);// Set a default white pixel at each position
        }
    }
    
    matrix->columns = columns;
    matrix->lines = lines;
    
    return matrix;
}

void changeMatrix(Matrix* matrix, int lines, int columns)
{
	removeMatrix(matrix);// Remove the old Matrix
    matrix = createMatrix(lines, columns);// Create the new Matrix
}

int matrixLines(Matrix* matrix)
{
    return matrix->lines;// Return the stored value in the Matrix
}

int matrixColumns(Matrix* matrix)
{
    return matrix->columns;// Return the stored value in the Matrix
}

int matrixSize(Matrix* matrix)
{
    return matrixLines(matrix) * matrixColumns(matrix);// Return the mult of the width and the height (line * columns = quantity)
}

void setLines(Matrix* matrix, int lines)
{
	matrix->lines = lines;
}

void setColumns(Matrix* matrix, int columns)
{
	matrix->columns = columns;
}

Pixel* select(Matrix* matrix, int x, int y)
{
    return matrix->matrix[y][x];// Select the Pixel at the given coordinates
}

void set(Matrix* matrix, int x, int y, Pixel* pixel)
{
	removePixel(matrix->matrix[y][x]);
    matrix->matrix[y][x] = pixel;// Modify the Pixel at the given coordinates
}

void removeMatrix(Matrix* matrix)
{
	if(matrix != NULL) // If the pointer is labelMalloc
	{
		if(matrix->matrix != NULL)// If the matrix is labelMalloc
		{
			for(int y = 0; y < matrix->lines; y++)//Delete each columns
			{
				for(int x = 0; x < matrix->columns; x++)
				{
					removePixel(matrix->matrix[y][x]);
				}
				freeLabel(matrix->matrix[y]);
			}
			freeLabel(matrix->matrix);// Delete the Matrix
		}
		freeLabel(matrix);// Delete the pointer
	}
}
