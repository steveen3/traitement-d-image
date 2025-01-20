#include "image.h"

Image resizeImage(const Image *image, double scaleFactor) {
    Image newImage;
    newImage.width = (int)(image->width * scaleFactor);
    newImage.height = (int)(image->height * scaleFactor);
    newImage.maxPixelValue = image->maxPixelValue;
    newImage.pixels = (unsigned char *)malloc(newImage.width * newImage.height * sizeof(unsigned char));

    for (int i = 0; i < newImage.height; ++i) {
        for (int j = 0; j < newImage.width; ++j) {
            int originalX = (int)(j / scaleFactor);
            int originalY = (int)(i / scaleFactor);
            newImage.pixels[i * newImage.width + j] = image->pixels[originalY * image->width + originalX];
        }
    }

    return newImage;
}