#ifndef H_PIXEL
#define H_PIXEL

/**
 * Structure representing a Pixel with its three color values
 */
typedef struct Pixel Pixel;
struct Pixel
{
	unsigned char r;// The value of the red color
	unsigned char g;// The value of the green color
	unsigned char b;// The value of the blue color
};

/**
 * Initialize a Pixel to its default value
 * @param Pixel* pixel : the Pixel to be initialized
 */
void initPixel(Pixel* pixel);

/**
 * Create a pixel from a RGB color
 * @param unsigned char r : the red color value
 * @param unsigned char g : the green color value
 * @param unsigned char b : the blue color value
 *
 * @return the newly created Pixel
 */
Pixel* getRGB(unsigned char r, unsigned char g, unsigned char b);

/**
 * Retrieve the Red value of the given Pixel
 * @param Pixel* pixel : the Pixel to be analyzed
 *
 * @return the red color value
 */
unsigned char getRed(Pixel* pixel);

/**
 * Retrieve the Green value of the given Pixel
 * @param Pixel* pixel : the Pixel to be analyzed
 *
 * @return the green color value
 */
unsigned char getGreen(Pixel* pixel);

/**
 * Retrieve the Blue value of the given Pixel
 * @param Pixel* pixel : the Pixel to be analyzed
 *
 * @return the blue color value
 */
unsigned char getBlue(Pixel* pixel);

/**
 * Change the color values of the given Pixel
 * @param unsigned char r : the new red value
 * @param unsigned char g : the new green value
 * @param unsigned char b : the new blue value
 */
void modifyPixel(Pixel* pixel, unsigned char r, unsigned char g, unsigned char b);

/**
 * Increase the color values of the given Pixel
 * @param unsigned char r : the increment red value
 * @param unsigned char g : the increment green value
 * @param unsigned char b : the increment blue value
 */
void increasePixel(Pixel* pixel, unsigned char r, unsigned char g, unsigned char b);

/**
 * Substract the color values of the given Pixel
 * @param unsigned char r : the red value to substract
 * @param unsigned char g : the green value to substract
 * @param unsigned char b : the blue value to substract
 */
void substractPixel(Pixel* pixel, unsigned char r, unsigned char g, unsigned char b);

/**
 * Multiply the color values of the given Pixel
 * @param unsigned char r : the red value factor
 * @param unsigned char g : the green value factor
 * @param unsigned char b : the blue value factor
 */
void multiplyPixel(Pixel* pixel, unsigned char r, unsigned char g, unsigned char b);

/**
 * Divide the color values of the given Pixel
 * @param unsigned char r : the red value to divide by
 * @param unsigned char g : the green value to divide by
 * @param unsigned char b : the blue value to divide by
 */
void dividePixel(Pixel* pixel, unsigned char r, unsigned char g, unsigned char b);

/**
 * Create a new Pixel with the same color as the given one
 * @param Pixel* pixel : the Pixel to be copied
 *
 * @return the newly created Pixel
 */
Pixel* copyPixel(Pixel* pixel);

/**
 * Remove the Pixel from the memory
 * @param Pixel* pixel : the Pixel to be deleted
 */
void removePixel(Pixel* pixel);

#endif
