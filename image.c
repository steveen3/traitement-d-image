// image png
/* #include <stdio.h>
#include <stdlib.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include "image.h"

Image loadImage(const char *filename) {
    Image image;
    image.pixels = NULL;

    int channels;
    image.pixels = stbi_load(filename, &image.width, &image.height, &channels, 0);
    if (!image.pixels) {
        fprintf(stderr, "Erreur lors du chargement de l'image : %s\n", stbi_failure_reason());
        exit(EXIT_FAILURE);
    }

    // Ajustez maxPixelValue si nécessaire (par exemple, pour un format RGB)
    image.maxPixelValue = 255; // Pour des formats 8 bits
    return image;
}

void saveImage(const Image *image) {
    // Pour enregistrer au format PNG, par exemple
    if (stbi_write_png("image_modifiee.png", image->width, image->height, 1, image->pixels, image->width) == 0) {
        fprintf(stderr, "Erreur lors de l'enregistrement de l'image\n");
        exit(EXIT_FAILURE);
    }
}

void freeImage(Image *image) {
    stbi_image_free(image->pixels);
    image->pixels = NULL;
}

 */
// image pgm
#include "image.h"

Image loadImage(const char *filename) {
    Image image;
    image.pixels = NULL;

    FILE *file = fopen(filename, "rb");
    if (!file) {
        perror("Erreur lors de l'ouverture du fichier");
        exit(EXIT_FAILURE);
    }

    char buffer[1000];
    fgets(buffer, sizeof(buffer), file);
    if (buffer[0] != 'P' || buffer[1] != '2') {
        fprintf(stderr, "Format de fichier PGM invalide\n");
        exit(EXIT_FAILURE);
    }

    do {
        fgets(buffer, sizeof(buffer), file);
    } while (buffer[0] == '#');

    sscanf(buffer, "%d %d", &image.width, &image.height);
    fgets(buffer, sizeof(buffer), file);
    sscanf(buffer, "%d", &image.maxPixelValue);

    image.pixels = (unsigned char *)malloc(image.width * image.height * sizeof(unsigned char));
    if (!image.pixels) {
        perror("Erreur d'allocation de mémoire");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < image.height; ++i) {
        for (int j = 0; j < image.width; ++j) {
            fscanf(file, "%hhu", &(image.pixels[i * image.width + j]));
        }
    }

    fclose(file);
    return image;
}

void saveImage(const Image *image) {
    FILE *file = fopen("image_modifiee.pgm", "wb");
    if (!file) {
        perror("Erreur lors de l'ouverture du fichier pour écriture");
        exit(EXIT_FAILURE);
    }
    fprintf(file, "P2\n%d %d\n%d\n", image->width, image->height, image->maxPixelValue);
    for (int i = 0; i < image->height; ++i) {
        for (int j = 0; j < image->width; ++j) {
            fprintf(file, "%4u ", image->pixels[i * image->width + j]);
        }
        fprintf(file, "\n");
    }
    fclose(file);
}

void freeImage(Image *image) {
    free(image->pixels);
    image->pixels = NULL;
}

