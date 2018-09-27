#ifndef H_PIXEL
#define H_PIXEL

typedef struct Pixel Pixel;
struct Pixel
{
	unsigned char r;
	unsigned char g;
	unsigned char b;
};

void initPixel(Pixel* pixel);
Pixel* getRGB(unsigned char r, unsigned char g, unsigned char b);

unsigned char getRed(Pixel* pixel);
unsigned char getGreen(Pixel* pixel);
unsigned char getBlue(Pixel* pixel);

#endif
