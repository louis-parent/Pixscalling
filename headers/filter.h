#ifndef H_FILTER
#define H_FILTER

#include "../headers/ppm.h"
#include "../headers/matrix.h"

/**
 * Obscurate a Matrix
 * @param Matrix* matrix : the Matrix to modify
 */
void obscurate(Matrix* matrix);

/**
 * Turn a Matrix in black and white
 * @param Matrix* matrix : the Matrix to modify
 */
void toGrayMap(Matrix* matrix);

/**
 * Make the negative of a Matrix
 * @param Matrix* matrix : the Matrix to modify
 */
void negative(Matrix* matrix);

/**
 * Upscale by two a Matrix
 * @param Matrix* matrix : the Matrix to modify
 *
 * @return the new modified Matrix
 */
Matrix* growup(Matrix* matrix);

/**
 * Apply the Scale2X on a Matrix
 * @param Matrix* matrix : the Matrix to modify
 *
 * @return the new modified Matrix
 */
Matrix* scale2x(Matrix* matrix);

/**
 * Apply a filter on a PPM
 * @param PPM* ppm : The PPM to modify
 * @param void (*filter)(Matrix*) : The filter to apply
 */
void applyFilter(PPM* ppm, Matrix* (*filter)(Matrix*), int count);

#endif
