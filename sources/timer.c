#include <time.h>
#include "../headers/timer.h"
#include "../headers/filter.h"

double timeCounter(PPM* ppm, Matrix* (*filter)(Matrix*), int count)
{
    clock_t start, end;

    start = clock();

	applyFilter(ppm, filter, count);

    end = clock();
    return ((double) (end - start)) / CLOCKS_PER_SEC;
}

double timeCounterAverage(int n, PPM* ppm, Matrix* (*filter)(Matrix*), int count)
{
    double sum = .0;
    for(int i = 0; i < n; i++){
        sum += timeCounter(ppm, filter, count);
    }
    return sum/n;
}
