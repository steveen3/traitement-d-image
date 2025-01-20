#ifndef IMAGE_H
#define IMAGE_H

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    const char *filename;
    int width;
    int height;
    int maxPixelValue;
    unsigned char *pixels;
} Image;

Image loadImage(const char *filename);
void saveImage(const Image *image);
void freeImage(Image *image);


#endif // IMAGE_H