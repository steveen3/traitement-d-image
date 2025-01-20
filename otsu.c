#include <stdio.h>
#include <stdlib.h>
#include "image.h"

int otsuThreshold(const Image *image) {
    int histogram[256] = {0};
    int totalPixels = image->width * image->height;

    // Calculer l'histogramme
    for (int i = 0; i < totalPixels; i++) {
        histogram[image->pixels[i]]++;
    }

    float sum = 0;
    for (int t = 0; t < 256; t++) {
        sum += t * histogram[t];
    }

    float sumB = 0;
    int wB = 0;
    int wF = 0;
    float varMax = 0;
    int threshold = 0;

    for (int t = 0; t < 256; t++) {
        wB += histogram[t];               // Total des pixels de classe 1
        if (wB == 0) continue;

        wF = totalPixels - wB;            // Total des pixels de classe 2
        if (wF == 0) break;

        sumB += (float)(t * histogram[t]);

        float mB = sumB / wB;             // Moyenne de classe 1
        float mF = (sum - sumB) / wF;     // Moyenne de classe 2

        // Calculer la variance inter-classes
        float varBetween = (float)wB * (float)wF * (mB - mF) * (mB - mF);

        // Maximiser la variance inter-classes
        if (varBetween > varMax) {
            varMax = varBetween;
            threshold = t;
        }
    }

    return threshold;
}

void applyOtsuThreshold(Image *image) {
    int threshold = otsuThreshold(image);
    for (int i = 0; i < image->width * image->height; i++) {
        image->pixels[i] = (image->pixels[i] > threshold) ? 255 : 0;
    }
}