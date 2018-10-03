#include <stdlib.h>
#include "../headers/matrix.h"

void initMatrix(Matrix* matrix)
{
    matrix->lines = 0;// by default there are 0 line
    matrix->columns = 0;// by default there are 0 column

    matrix->matrix = NULL;// By default the matrix is empty
}

Matrix* createMatrix(int columns, int lines)
{
    Matrix* matrix = malloc(sizeof(Matrix));// Allocate memory for Matrix
    initMatrix(matrix);// Init an empty Matrix

    matrix->matrix = (Pixel***) malloc(lines * sizeof(Pixel**)); // Allocate the array of columns
    for(int y = 0; y < lines; y++)
    {
        matrix->matrix[y] = (Pixel**) malloc(columns * sizeof(Pixel*));// Allocate the lines for the column y
        for(int x = 0; x < columns; x++)
        {
        	matrix->matrix[y][x] = malloc(sizeof(Pixel*));
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
	if(matrix != NULL) // If the pointer is allocate
	{
		if(matrix->matrix != NULL)// If the matrix is allocate
		{
			for(int y = 0; y < matrix->lines; y++)//Delete each columns
			{
				for(int x = 0; x < matrix->columns; x++)
				{
					removePixel(matrix->matrix[y][x]);
				}
				free(matrix->matrix[y]);
			}
			free(matrix->matrix);// Delete the Matrix
		}
		free(matrix);// Delete the pointer
	}
}
