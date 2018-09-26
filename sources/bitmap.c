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

    fclose(in);
	
	return bitmap;
}

int writeBitmap(char *output, Bitmap* bitmap)
{
    FILE *out;
    out = fopen(output, "wb");
    
    for(int i = 0; i < bitmap->size; i++)
    {
        fprintf(out, "%c", bitmap->content[i]);
    }

    fclose(out);
    
	return bitmap->size;
}
