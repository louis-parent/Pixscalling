#ifndef H_PPM
#define H_PPM

#include "../headers/pixel.h"
#include "../headers/matrix.h"

#define PPM_MAGIC_NUMBER "P6"

/**
 * Structure representing a PPM Image Header
 */
typedef struct PPMHeader PPMHeader;
struct PPMHeader
{
	char* magicNumber;// The 2 char magic number

	int width;// The width of the image
	int height;// The height of the image

	int colorLevel;// The color level which correspond to white
};

/**
 * Structure representing a PPM Image
 */
typedef struct PPM PPM;
struct PPM
{
	char* filename;// The original filename (NULL if it's not read)
	int size;// The size of the original image (0 if it's not read)

	PPMHeader* header;// The header of the PPM
	Matrix* content;// The content Matrix of each pixel
};

/**
 * Create an empty PPMHeader
 * @param PPMHeader* header : the PPMHeader to be initialized
 */
void initHeader(PPMHeader* header);

/**
 * Create an empty PPM
 * @param PPM* ppm : the PPM to be initialized
 */
void initPPM(PPM* ppm);

/**
 * Create a PPM from a PPM file
 * @param char* input : The PPM file name
 *
 * @return The readed PPM Struct
 */
PPM* readPPM(char* input);

/**
 * Write the given in a PPM file
 * @param char* ouput : The PPM file name to be written
 * @param PPM* ppm : The PPM Struct to be written
 *
 * @return The number of byte writed
 */
int writePPM(char* output, PPM* ppm);

/**
 * Retrieve the pixel at the given coordinate in PPM
 * @param PPM* ppm : The PPM where the pixel is
 * @param int x : the x coordinate of the pixel
 * @param int y : the y coordinate of the pixel
 *
 * @return the Pixel Struct at the given (x, y)
 */
Pixel* getPixel(PPM* ppm, int x, int y);

/**
 * Retrieve the width of a PPM
 * @param PPM* ppm : the PPM to be analyzed
 *
 * @return the PPM width
 */
int getWidth(PPM* ppm);

/**
 * Retrieve the height of a PPM
 * @param PPM* ppm : the PPM to be analyzed
 *
 * @return the PPM height
 */
int getHeight(PPM* ppm);

/**
 * Retirieve the content Matrix of a PPM
 * @param PPM* ppm : the PPM to be analyzed
 *
 * @return the Matrix Struct of the PPM
 */
Matrix* getContent(PPM* ppm);

/**
 * Retrieve the pixel quantity in the PPM
 * @param PPM* ppm : the PPM to be analyzed
 *
 * @return the size of the content
 */
int getPixelQuantity(PPM* ppm);

/**
 * Change the width of the PPM
 * @param PPM* ppm : the PPM to be modified
 * @param int width : the new width
 */
void setWidth(PPM* ppm, int width);

/**
 * Change the height of the PPM
 * @param PPM* ppm : the PPM to be modified
 * @param int height : the new height
 */
void setHeight(PPM* ppm, int height);

/**
 * Change the content Matrix of the PPM
 * @param PPM* ppm : the PPM to be modified
 * @param Matrix* content : the new content
 */
void setContent(PPM* ppm, Matrix* content);



/**
 * Change a Pixel in the PPM
 * @param PPM* ppm : the PPM to be modified
 * @param int x : the x coordinate of the pixel
 * @param int y : the y coordinate of the pixel
 * @param Pixel* pixel : the new pixel
 */
void setPixel(PPM* ppm, int x, int y, Pixel* pixel);

/**
 * Remove a PPMHeader from the memory
 * @param PPMHeader* header : the PPMHeader to be removed
 */
void removePPMHeader(PPMHeader* header);

/**
 * Remove a PPM from the memory
 * @param PPM* ppm : the PPM to be removed
 */
void removePPM(PPM* ppm);

#endif
