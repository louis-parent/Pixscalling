#ifndef H_PPM
#define H_PPM

#include "../headers/pixel.h"

#define PPM_MAGIC_NUMBER "P6"
#define PPM_MAGIC_NUMBER_LETTER "P"
#define PPM_MAGIC_NUMBER_NUMBER "6";

typedef struct PPMHeader PPMHeader;
struct PPMHeader
{
	char* magicNumber;

	int width;
	int height;
	
	int colorLevel;
};

typedef struct PPM PPM;
struct PPM
{
	char* filename;
	int size;
	
	PPMHeader header;
	Pixel** content;
};

void initHeader(PPMHeader* header);
void initPPM(PPM* ppm);

PPM* readPPM(char* input);
int writePPM(char* output, PPM* ppm);

Pixel* getPixel(PPM* ppm, int x, int y);

int getWidth(PPM* ppm);
int getHeight(PPM* ppm);

int getPixelQuantity(PPM* ppm);

void setWidth(PPM* ppm, int width);
void setHeight(PPM* ppm, int height);

void setContent(PPM* ppm, Pixel** content);

#endif
