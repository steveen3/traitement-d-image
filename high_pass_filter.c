#include "image.h"
#include <math.h>

void applyPrewittFilter(Image *image) {
    unsigned char *newPixels = (unsigned char *)malloc(image->width * image->height * sizeof(unsigned char));

    int Gx[3][3] = {
        {-1, 0, 1},
        {-1, 0, 1},
        {-1, 0, 1}
    };

    int Gy[3][3] = {
        {1, 1, 1},
        {0, 0, 0},
        {-1, -1, -1}
    };

    for (int i = 1; i < image->height - 1; ++i) {
        for (int j = 1; j < image->width - 1; ++j) {
            int sumX = 0, sumY = 0;
            for (int x = -1; x <= 1; ++x) {
                for (int y = -1; y <= 1; ++y) {
                    sumX += image->pixels[(i + x) * image->width + (j + y)] * Gx[x + 1][y + 1];
                    sumY += image->pixels[(i + x) * image->width + (j + y)] * Gy[x + 1][y + 1];
                }
            }
            int magnitude = (int)sqrt(sumX * sumX + sumY * sumY);
            newPixels[i * image->width + j] = (magnitude > 255) ? 255 : magnitude;
        }
    }

    free(image->pixels);
    image->pixels = newPixels;
}