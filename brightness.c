#include "image.h"

void adjustBrightness(Image *image, int adjustment) {
    for (int i = 0; i < image->height; ++i) {
        for (int j = 0; j < image->width; ++j) {
            int index = i * image->width + j;
            int newValue = image->pixels[index] + adjustment;
            image->pixels[index] = (newValue < 0) ? 0 : (newValue > image->maxPixelValue) ? image->maxPixelValue : newValue;
        }
    }
}