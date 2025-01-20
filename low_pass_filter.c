#include "image.h"

void applyMeanFilter(Image *image) {
    unsigned char *newPixels = (unsigned char *)malloc(image->width * image->height * sizeof(unsigned char));
    
    for (int i = 1; i < image->height - 1; ++i) {
        for (int j = 1; j < image->width - 1; ++j) {
            int sum = 0;
            for (int x = -1; x <= 1; ++x) {
                for (int y = -1; y <= 1; ++y) {
                    sum += image->pixels[(i + x) * image->width + (j + y)];
                }
            }
            newPixels[i * image->width + j] = sum / 9; // Moyenne
        }
    }

    free(image->pixels);
    image->pixels = newPixels;
}