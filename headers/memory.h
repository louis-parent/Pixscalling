#ifndef H_MEMORY
#define H_MEMORY

#define MAX_ALLOCATION 500000

void setDebug();

void* labelMalloc(int size, char* label);
void freeLabel(void* ptr);

void removeFromAllocated(size_t address);

void printUnfreeAlloc();

#endif
