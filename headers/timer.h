#ifndef H_TIMER
#define H_TIMER

//Calculate the time of execution of a function
double timeCounter(void (*ptr)());

//Calculate the average time of n-th executions of a function
double timeCounterAverage(void (*ptr)(), int n);

#endif
