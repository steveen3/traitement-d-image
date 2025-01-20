#include "image.h"

void adjustContrast(Image *image, double factor) {
    for (int i = 0; i < image->height; ++i) {
        for (int j = 0; j < image->width; ++j) {
            int index = i * image->width + j;
            int newValue = (int)((image->pixels[index] - 128) * factor + 128);
            image->pixels[index] = (newValue < 0) ? 0 : (newValue > image->maxPixelValue) ? image->maxPixelValue : newValue;
        }
    }
}