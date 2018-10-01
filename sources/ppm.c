#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/ppm.h"

void initHeader(PPMHeader* header)
{
	header->magicNumber = PPM_MAGIC_NUMBER;


	header->width = 0;
	header->height = 0;

	header->colorLevel = 255;
}

void initPPM(PPM* ppm)
{
	PPMHeader* header = malloc(sizeof(PPMHeader));
	initHeader(header);

	Matrix* matrix = malloc(sizeof(Matrix));
	initMatrix(matrix);

	ppm->filename = NULL;
	ppm->size = 0;
	ppm->header = header;
	ppm->content = NULL;
}

PPM* createPPM(Matrix* matrix, int width, int height)
{
	PPM* ppm = malloc(sizeof(PPM));// Allocate a PPM in the memory
	initPPM(ppm);// Init the PPM to its default value
	
	setWidth(ppm, width);// Change the width with the given one
	setHeight(ppm, height);// Change the height with the given one
	setContent(ppm, matrix);// Set the Matrix as the content of the PPM
	
	return ppm;
}

PPM* readPPM(char *input)
{
	PPM* ppm = malloc(sizeof(PPM));//Create empty PPM
	initPPM(ppm);//Init PPM
	ppm->filename = malloc(sizeof(input));
	strcpy(ppm->filename, input);//Set the origin file name of the PPM

	FILE* in = fopen(input, "rb");//Open the orignal file

    fseek(in, 0L, SEEK_END);
    int size = ftell(in);//Calculate the file size
    ppm->size = size;//Set the file size of the PPM

    fseek(in, 0L, SEEK_SET);//Go Back to start

	char* tmp = malloc(sizeof(char) * 2);//Save the Magic number in a temp Buffer
	fread(tmp, 2*sizeof(char), 1, in);//read the Magic Number
	ppm->header->magicNumber = malloc(sizeof(char) *2);//Init the magic number
	ppm->header->magicNumber[0] = tmp[0];//Set the magic number
	ppm->header->magicNumber[1] = tmp[1];
	fseek(in, 1, SEEK_CUR);//Pass the end of line
	free(tmp);//Deleting temporary buffer

	char c;
	int length = 0;
	char buffer[12];// The theorical max length of this line is 5 (the width) + 5 (the height) + 1 (the space between) + 1 (The end of line char)

	do
	{
		fread(&buffer[length], sizeof(char), 1, in);
		c = buffer[length];
		length++;
	}while(c != '\n');//Read the dimension line

	buffer[length - 1] = ' ';//Replace the end of line for no interpreting by atoi
	ppm->header->width = atoi(strtok(buffer, " "));//Set the width Width
	ppm->header->height = atoi(strtok(NULL, " "));//Set the Height

	char color[3];//The color buffer
	fread(color, sizeof(char), 3, in);//Read the Color Level
	ppm->header->colorLevel = atoi(color);//Set the color level with cast to int
	fseek(in, 1, SEEK_CUR);//Pass the end of line

	ppm->content = createMatrix(ppm->header->width, ppm->header->height);//Init the first dimension of the matrix
	for(int y = 0; y < ppm->header->height; y++)
	{
		for(int x = 0; x < ppm->header->width; x++)
		{
			unsigned char bgrpix[3];//The RGB Buffer
       		fread(&bgrpix,sizeof(unsigned char),3,in);//Read the RGB values

       		Pixel* pixel = getRGB(bgrpix[0], bgrpix[1], bgrpix[2]);//Create the pixel from RGB
			setPixel(ppm,x, y, pixel);//Set the pixel

		}
	}

    fclose(in);
    return ppm;
}

int writePPM(char *output, PPM* ppm)
{
	int writed = 0;//The number of byte writed
	FILE* out = fopen(output, "wb");//Open the output file

	fprintf(out, "%c%c\n", ppm->header->magicNumber[0], ppm->header->magicNumber[1]);//Write the magic number
	writed += sizeof(char) * sizeof(ppm->header->magicNumber) + sizeof(char);//Add the magic number size to the writed file size

	fprintf(out, "%i %i\n", ppm->header->width, ppm->header->height);//Write the dimensions
	writed += sizeof(int) * 2 + sizeof(char) * 2;//add the dimension

	fprintf(out, "%i\n", ppm->header->colorLevel);
	writed += sizeof(int) + sizeof(char);

	for(int y = 0; y < ppm->header->height; y++)
	{
		for(int x = 0; x < ppm->header->width; x++)
		{
			fprintf(out, "%c%c%c", getRed(getPixel(ppm, x, y)), getGreen(getPixel(ppm, x, y)), getBlue(getPixel(ppm, x, y)));
			writed += sizeof(Pixel);
		}
	}

	fclose(out);
    return writed;
}

Pixel* getPixel(PPM* ppm, int x, int y)
{
	return select(ppm->content, x, y); //Select the pixel from the content Matrix
}

int getWidth(PPM* ppm)
{
	return ppm->header->width; // Return the width in the PPM header
}

int getHeight(PPM* ppm)
{
	return ppm->header->height; //Return the height in the PPM header
}

int getPixelQuantity(PPM* ppm)
{
	return matrixSize(ppm->content); // Return the amount of pixel in the matrix
}

void setWidth(PPM* ppm, int width)
{
	ppm->header->width = width; // Change the width in the PPM header
}

void setHeight(PPM* ppm, int height)
{
	ppm->header->height = height; // Change the height in the PPM header
}

Matrix* getContent(PPM* ppm)
{
	return ppm->content; // Return the content Matrix 
}

void setContent(PPM* ppm, Matrix* content)
{
	removeMatrix(ppm->content); //Remove the old Matrix
	ppm->content = content;// Change the pointer to the new matrix
}

void setPixel(PPM* ppm, int x, int y, Pixel* pixel)
{
	set(getContent(ppm), x, y, pixel);//Set pixel of the Matrix to a new pixel
}

void removePPMHeader(PPMHeader* header)
{
	if(header != NULL)
	{
		if(header->magicNumber != NULL && header->magicNumber != PPM_MAGIC_NUMBER)
		{
			free(header->magicNumber); // Remove the magic number pointer
		}
		
		free(header); // Remove the entiere header
	}
}

void removePPM(PPM* ppm)
{
	if(ppm != NULL)
	{
		removePPMHeader(ppm->header);// Remove the header
		removeMatrix(ppm->content);// Remove the content Matrix
		
		if(ppm->filename != NULL)
		{
			free(ppm->filename); // Remove the filename pointer
		}
		
		free(ppm);// Remove the PPM
	}
}
