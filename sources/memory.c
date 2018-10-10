#include <stdlib.h>
#include <stdio.h>
#include "../headers/memory.h"

size_t allocated[MAX_ALLOCATION];
char* labels[MAX_ALLOCATION];

int allocationCount = 0;

extern int debug = 0;

void* labelMalloc(int size, char* label)
{
	void* ptr = malloc(size);
	
	if(debug == 1)
	{
		allocated[allocationCount] = (size_t) ptr;
		labels[allocationCount] = label;
		allocationCount++;
	}
	
	return ptr;
}

void freeLabel(void* ptr)
{
	if(debug == 1)
	{
		removeFromAllocated((size_t) ptr);
	}
	
	free(ptr);
}

void removeFromAllocated(size_t address)
{
	int i = 0;
	int find = 0;
	
	while(i < allocationCount && find == 0)
	{
		if(allocated[i] == address)
		{
			find = 1;
			allocationCount--;
			
			allocated[i] = allocated[allocationCount];
			labels[i] = labels[allocationCount];
			
			if(allocationCount > 1)
			{
				allocated[allocationCount] = 0;
				labels[allocationCount] = NULL;
			}
			
		}
		
		i++;
	}
	
}

void printUnfreeAlloc()
{
	if(debug == 1)
	{
		if(allocationCount > 0)
		{
			printf("===============================\nUnfree Memory : %i pointers :\n", allocationCount);
			for(int i = 0; i < allocationCount; i++)
			{
				if(allocated[i] != 0)
				{
					printf("\tThe pointer n°%i (%lu) : %s is not free\n", i, allocated[i], labels[i]);
				}
			}
		}
		else
		{
			printf("===================\nNo Unfree Memory !!\n");
		}
	}
}
