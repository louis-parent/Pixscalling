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

    Pixel*** matrix;
};

/**
 * Initialize a matrix to its default value
 * @param Matrix* matrix : the matrix to be initialized
 */
void initMatrix(Matrix* matrix);

/**
 * Create a empty matrix with the given number of lines and columns
 * @param int lines : the amount of line to be created
 * @param int columns : the amount of columns to be created
 *
 * @return The newly created Matrix Struct
 */
Matrix* createMatrix(int lines, int columns);

/**
 * Replace the given matrix by a new sized empty matrix
 * @param Matrix* matrix : the pointer on the old Matrix
 * @param int lines : the new amount of line
 * @param int columns : the new amount of column
 */
void changeMatrix(Matrix* matrix, int lines, int columns);

/**
 * Retrieve the number of lines of the matrix
 * @param Matrix* matrix : the Matrix to be analyzed
 *
 * @return the number of line in the Matrix
 */
int matrixLines(Matrix* matrix);

/**
 * Retrieve the number of columns of the matrix
 * @param Matrix* matrix : the Matrix to be analyzed
 *
 * @return the number of column in the Matrix
 */
int matrixColumns(Matrix* matrix);

/**
 * Retrieve th quantity of pixel in the matrix
 * @param Matrix* matrix : the Matrix to be analyzed
 *
 * @return the amount of Pixel in the Matrix
 */
int matrixSize(Matrix* matrix);

/**
 * Select the pixel of the matrix at the given position
 * @param Matrix* matrix : the Matrix where the pixel is
 * @param int x : the x coordinate of the Pixel
 * @param int y : the y coordinate of the Pixel
 */
Pixel* select(Matrix* matrix, int x, int y);

/**
 * Set the pixel of the matrix at the given position
 * @param Matrix* matrix : the Matrix where the pixel will be
 * @param int x : the x coordinate of the Pixel
 * @param int y : the y coordinate of the Pixel
 * @param Pixel* pixel : the Pixel to be set
 */
void set(Matrix* matrix, int x, int y, Pixel* pixel);

/**
 * Remove the matrix from the memory
 * @param Matrix* matrix : the Matrix to be deleted
 */
void removeMatrix(Matrix* matrix);

#endif
