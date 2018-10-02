#ifndef H_FILTER
#define H_FILTER

#include "../headers/ppm.h"

void obscurate(PPM* ppm);
void toGrayMap(PPM* ppm);
void negative(PPM* ppm);
void growup(PPM* ppm, int mult);
void scale2x(PPM* ppm);

#endif
