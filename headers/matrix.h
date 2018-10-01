#ifndef H_MATRIX
#define H_MATRIX

#include "../headers/pixel.h"
/**
 * Structure representing a matrix of pixel
 */
typedef struct Matrix Matrix;
struct Matrix
{
    int lines;// The amount of line in the Matrix
    int columns;// The amount of columns in the Matrix

    Pixel** matrix;
};

/**
 * Initialize a matrix to its default value
 * @param Matrix* matrix : the matrix to be initialized
 */
void initMatrix(Matrix* matrix);

/**
 * Create a empty matrix with the given number of lines and columns
 */
Matrix* createMatrix(int lines, int columns);

/**
 * Replace the given matrix by a new sized empty matrix
 */
void changeMatrix(Matrix* matrix, int lines, int columns);

/**
 * Retrieve the number of lines of the matrix
 */
int matrixLines(Matrix* matrix);

/**
 * Retrieve the number of columns of the matrix
 */
int matrixColumns(Matrix* matrix);

/**
 * Retrieve th quantity of pixel in the matrix
 */
int matrixSize(Matrix* matrix);

/**
 * Select the pixel of the matrix at the given position
 */
Pixel* select(Matrix* matrix, int x, int y);

/**
 * Set the pixel of the matrix at the given position
 */
void set(Matrix* matrix, int x, int y, Pixel* pixel);

/**
 * Remove the matrix from the memory
 */
void removeMatrix(Matrix* matrix);

#endif
