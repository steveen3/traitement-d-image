#include "image.h"

void applyThreshold(Image *image, int threshold) {
    for (int i = 0; i < image->height; ++i) {
        for (int j = 0; j < image->width; ++j) {
            int index = i * image->width + j;
            image->pixels[index] = (image->pixels[index] > threshold) ? 255 : 0;
        }
    }
}