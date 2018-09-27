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
#include "headers/timer.h"

#define INPUT_FILE "in.ppm"
#define OUTPUT_FILE "out.ppm"

void copyFile()
{
	PPM* ppm = readPPM(INPUT_FILE);
	writePPM(OUTPUT_FILE, ppm);
}

void obscurate()
{
	PPM* ppm = readPPM(INPUT_FILE);
	for(int y = 0; y < ppm->header.height; y++)
	{
		for(int x = 0; x < ppm->header.width; x++)
		{
			dividePixel(getPixel(ppm, x, y), 2, 2, 2);
		}
	}	
	writePPM(OUTPUT_FILE, ppm);
}

int main()
{
    printf("First Test : %f\n", timeCounterAverage(copyFile, 100));
    printf("Second Test : %f\n", timeCounterAverage(obscurate, 100));

    return EXIT_SUCCESS;
}



