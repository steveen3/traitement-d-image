#include <stdio.h>
#include <stdlib.h>
#include "image.h"

Image addImages(const Image *image, const Image *image1) {
    if (image->width != image1->width || image->height != image1->height) {
        fprintf(stderr, "Les dimensions des images doivent être identiques pour l'addition.\n");
        exit(EXIT_FAILURE);
    }

    Image result;
    result.width = image->width;
    result.height = image->height;
    result.maxPixelValue = 255;
    result.pixels = (unsigned char *)malloc(result.width * result.height * sizeof(unsigned char));
    
    if (!result.pixels) {
        perror("Erreur d'allocation de mémoire");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < result.height; ++i) {
        for (int j = 0; j < result.width; ++j) {
            int index = i * result.width + j;
            int sum = image->pixels[index] + image1->pixels[index];
            result.pixels[index] = (sum > result.maxPixelValue) ? result.maxPixelValue : sum;
        }
    }

    return result;
}