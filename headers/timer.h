#ifndef H_TIMER
#define H_TIMER

#include "../headers/ppm.h"
#include "../headers/matrix.h"

//Calculate the time of execution of a function
double timeCounter(PPM* ppm, Matrix* (*filter)(Matrix*), int count);

//Calculate the average time of n-th executions of a function
double timeCounterAverage(int n, PPM* ppm, Matrix* (*filter)(Matrix*), int count);

#endif
