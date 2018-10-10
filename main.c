#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>

#include "headers/ppm.h"
#include "headers/pixel.h"
#include "headers/matrix.h"
#include "headers/timer.h"
#include "headers/filter.h"
#include "headers/memory.h"

#define INPUT_FILE "in.ppm"
#define OUTPUT_FILE "out.ppm"

int makeSpeedTest = 0;

void copyFile()
{
	PPM* ppm = readPPM(INPUT_FILE);
	writePPM(OUTPUT_FILE, ppm);
	removePPM(ppm);
}
	
void test()
{
	/*printf("Begining Test :\n");
    printf("\t- Simple Copy Test : %f\n", timeCounterAverage(copyFile, 100));
   	printf("\t- Obscurate Test : %f\n", timeCounterAverage(obscurate, 100));
   	printf("\t- Shade of Grey Test : %f\n", timeCounterAverage(toGrayMap, 100));
    printf("\t- Negative Test : %f\n", timeCounterAverage(negative, 100));
    printf("\t- Simple Upscale Test : %f\n", timeCounterAverage(upscale, 1));*/
}

int main(int argc, char* argv[])
{
	if(argc != 5 && argc != 6)
	{
		printf("Usage : ./pixscalling <options -s m> [Input File] [Output File] [Filter] [Scale]\n");
		return EXIT_FAILURE;
	}
	
	if(argc == 6)
	{
		if(argv[1][0] == '-')
		{
			for(int i = 1; i < strlen(argv[1]); i++)
			{
				if(argv[1][i] == 's')
				{
					makeSpeedTest = 1;
				}
				else if(argv[1][i] == 'm')
				{
					setDebug();
				}
			}
		}
		else
		{
			printf("Usage : ./pixscalling <options -s m> [Input File] [Output File] [Filter] [Scale]\n");
			return EXIT_FAILURE;
		}
	}
	
	int scale = atoi(argv[argc - 1]);
	
	if(scale < 1)
	{
		printf("Incorrect Scale\n");
		return EXIT_FAILURE;
	}
	
	char command[80];
	sprintf(command, "convert %s %s", argv[argc - 4], INPUT_FILE);
	system(command);
	
	double executionTime = 0;

	PPM* ppm = readPPM(INPUT_FILE);
	
	if (strcmp(argv[argc - 2], "epx") == 0)
	{
		executionTime = timeCounter(ppm, epx, scale);
	} 
	else if (strcmp(argv[argc - 2], "scale2x") == 0) 
	{
		executionTime = timeCounter(ppm, scale2x, scale);
	} 
	else if (strcmp(argv[argc - 2], "scale3x") == 0) 
	{
		executionTime = timeCounter(ppm, scale3x, scale);
	} 
	else if (strcmp(argv[argc - 2], "upscale") == 0) 
	{
		executionTime = timeCounter(ppm, growup, scale);
	} 
	else if (strcmp(argv[argc - 2], "eagle") == 0) 
	{
		executionTime = timeCounter(ppm, eagle, scale);
	} 
	else
	{
		removePPM(ppm);
		printf("Unknow filter\n");
		return EXIT_FAILURE;
	}
	
	writePPM(OUTPUT_FILE, ppm);
	removePPM(ppm);
	
	sprintf(command, "convert %s %s", OUTPUT_FILE, argv[argc - 3]);
	system(command);
	
	remove(OUTPUT_FILE);
	remove(INPUT_FILE);
	
	if(makeSpeedTest == 1)
	{
		printf("\n================================\nExecution Time : %fs\n", executionTime);
	}
	
	printUnfreeAlloc();
	
    return EXIT_SUCCESS;
}
