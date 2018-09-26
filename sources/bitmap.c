#include <stdio.h>
#include <stdlib.h>
#include "../headers/bitmap.h"

void initBitmap(Bitmap* bitmap)
{
	bitmap->filename = NULL;
	bitmap->size = 0;
	bitmap->offset = 0;
	
	for(int i = 0; i < BITMAP_HEADER_LENGTH; i++)
	{
		bitmap->header[i] = 0;
	}
	bitmap->content = NULL;
}

int* extractHeader(int fullBmp[])
{
	int *header = malloc(BITMAP_HEADER_LENGTH * sizeof(int));
	
	for(int i = 0; i < BITMAP_HEADER_LENGTH; i++)
	{
		header[i] = fullBmp[i];
	}
	
	return header;
}

int* extractPixels(int fullBmp[], int bmpSize)
{
	int *pixels = malloc((bmpSize - BITMAP_HEADER_LENGTH) * sizeof(int));
	
	for(int i = BITMAP_HEADER_LENGTH; i < bmpSize; i++)
	{
		pixels[i] = fullBmp[i];
	}
	
	return pixels;
}

Bitmap readBitmap(char *input)
{
	Bitmap bitmap;
	initBitmap(&bitmap);
	
	bitmap.filename = input;
	
	FILE *in;

    in = fopen(input, "rb");

    fseek(in, 0L, SEEK_END);
    int size = ftell(in);
    
    bitmap.size = size;
    bitmap.content = malloc(size*sizeof(int));
    
    fseek(in, 0L, SEEK_SET);

    for(int i = 0; i < size; i++){
        char c = fgetc(in);
        bitmap.content[i] = (signed int) c;
    }
    
    int *temp = extractHeader(bitmap.content);
    for(int i = 0; i < BITMAP_HEADER_LENGTH; i++)
    {
    	bitmap.header[i] = temp[i];
    }
    bitmap.content = extractPixels(bitmap.content, size);

    fclose(in);
	
	return bitmap;
}

int writeBitmap(char *output, Bitmap* bitmap)
{
    FILE *out;
    out = fopen(output, "wb");
    
    for(int i = 0; i < BITMAP_HEADER_LENGTH; i++)
    {
        fprintf(out, "%c", bitmap->header[i]);
    }
    
    for(int i = BITMAP_HEADER_LENGTH; i < bitmap->size; i++)
    {
        fprintf(out, "%c", bitmap->content[i]);
    }

    fclose(out);
    
	return bitmap->size;
}
