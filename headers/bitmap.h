#ifndef H_BITMAP
#define H_BITMAP

#define BITMAP_HEADER_LENGTH 14

typedef struct Bitmap Bitmap;
struct Bitmap
{
	char *filename;
	
	int size;
	int offset;
	
	int header[BITMAP_HEADER_LENGTH];
	signed int *content;
};

void initBitmap(Bitmap* bitmap);

Bitmap readBitmap(char *input);
int writeBitmap(char *output, Bitmap* bitmap);

#endif
