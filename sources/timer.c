#include <time.h>
#include "../headers/timer.h"

double timeCounter(void (*ptr)())
{
    clock_t start, end;

    start = clock();

    (*ptr)();

    end = clock();
    return ((double) (end - start)) / CLOCKS_PER_SEC;
}

double timeCounterAverage(void (*ptr)(), int n)
{
    double sum = .0;
    for(int i = 0; i < n; i++){
        sum += timeCounter(ptr);
    }
    return sum/n;
}
