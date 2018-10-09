#include <stdlib.h>
#include "../headers/pixel.h"

void initPixel(Pixel* pixel)
{
	pixel->r = NULL;// By default all the value are set to 255 (Color white)
	pixel->g = NULL;
	pixel->b = NULL;
}

Pixel* getRGB(unsigned char r, unsigned char g, unsigned char b)
{
	Pixel* pixel = malloc(sizeof(Pixel));// Allocate the memory for a Pixel
	initPixel(pixel);// Init a pixel to its default value
	
	pixel->r = malloc(sizeof(unsigned char));
	pixel->g = malloc(sizeof(unsigned char));
	pixel->b = malloc(sizeof(unsigned char));
		
	*(pixel->r) = r;// Change the red value to the given one
	*(pixel->g) = g;// Change the green value to the given one
	*(pixel->b) = b;// Change the blue value to the given one

	return pixel;
}

unsigned char getRed(Pixel* pixel)
{
	return *(pixel->r);// Return the red value of the Pixel
}

unsigned char getGreen(Pixel* pixel)
{
	return *(pixel->g);// Return the green value of the Pixel
}

unsigned char getBlue(Pixel* pixel)
{
	return *(pixel->b);// Return the blue value of the Pixel
}

void modifyPixel(Pixel* pixel, unsigned char r, unsigned char g, unsigned char b)
{
	*(pixel->r) = r;// Set the value of each color to the given one
	*(pixel->g) = g;
	*(pixel->b) = b;
}

void increasePixel(Pixel* pixel, unsigned char r, unsigned char g, unsigned char b)
{
	*(pixel->r) += r;// Increase the value of each color with the given increment
	*(pixel->g) += g;
	*(pixel->b) += b;
}

void substractPixel(Pixel* pixel, unsigned char r, unsigned char g, unsigned char b)
{
	*(pixel->r) -= r;// Substract the value of each color with the given value
	*(pixel->g) -= g;
	*(pixel->b) -= b;
}

void multiplyPixel(Pixel* pixel, unsigned char r, unsigned char g, unsigned char b)
{
	*(pixel->r) *= r;// Multiply the value of each color with the given factor
	*(pixel->g) *= g;
	*(pixel->b) *= b;
}

void dividePixel(Pixel* pixel, unsigned char r, unsigned char g, unsigned char b)
{
	*(pixel->r) /= r;// Divide the value of each color with the given value
	*(pixel->g) /= g;
	*(pixel->b) /= b;
}

Pixel* copyPixel(Pixel* pixel)
{
	return getRGB(getRed(pixel), getGreen(pixel), getBlue(pixel));// Create a Pixel with the value of the color of the given Pixel
}

int comparePixel(Pixel* a, Pixel* b)
{
	return getRed(a) == getRed(b) && getGreen(a) == getGreen(b) && getBlue(a) == getBlue(b);
}

void removePixel(Pixel* pixel)
{
	if(pixel != NULL)
	{
		if(pixel->r != NULL)
		{
			free(pixel->r);
		}
		
		if(pixel->g != NULL)
		{
			free(pixel->g);
		}
		
		if(pixel->b != NULL)
		{
			free(pixel->b);
		}
	
		free(pixel);//Free the pixel pointer
	}
}
