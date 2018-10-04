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

#define INPUT_FILE "in.ppm"
#define OUTPUT_FILE "out.ppm"

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
	if(argc != 3)
	{
		printf("Usage : ./pixscalling [Filter] [Scale]\n");
		return EXIT_FAILURE;
	}
	
	int scale = atoi(argv[2]);
	
	if(scale < 1)
	{
		printf("Incorrect Scale\n");
		return EXIT_FAILURE;
	}

	PPM* ppm = readPPM(INPUT_FILE);
	
	
	if (strcmp(argv[1], "epx") == 0) 
	{
		applyFilter(ppm, epx, scale);
	} 
	else if (strcmp(argv[1], "scale2x") == 0) 
	{
		applyFilter(ppm, scale2x, scale);
	} 
	else if (strcmp(argv[1], "scale3x") == 0) 
	{
		applyFilter(ppm, scale3x, scale);
	} 
	else
	{
		removePPM(ppm);
		printf("Unknow filter\n");
		return EXIT_FAILURE;
	}
	
	writePPM(OUTPUT_FILE, ppm);
	removePPM(ppm);
	
    return EXIT_SUCCESS;
}
