#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "image.h"

void applyHoughTransform(const Image *image, Image *image1) {
    // Exemple de taille pour l'accumulateur
    int thetaRes = 180; // Résolution angulaire
    int rhoRes = 2;     // Résolution en pixels
    int width = image->width;
    int height = image->height;

    // Calculer la taille de l'accumulateur
    int maxRho = sqrt(width * width + height * height);
    int rhoCount = (2 * maxRho) / rhoRes;
    int **accumulator = (int **)malloc(rhoCount * sizeof(int *));
    for (int i = 0; i < rhoCount; i++) {
        accumulator[i] = (int *)calloc(thetaRes, sizeof(int));
    }

    // Remplir l'accumulateur
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            // Supposons que l'image est binaire (0 ou 255)
            if (image->pixels[y * width + x] == 255) {
                for (int theta = 0; theta < thetaRes; theta++) {
                    double thetaRad = theta * M_PI / 180;
                    int rho = (int)(x * cos(thetaRad) + y * sin(thetaRad));
                    rho += maxRho; // Décalage pour les indices positifs
                    accumulator[rho / rhoRes][theta]++;
                }
            }
        }
    }

    // Vous pouvez appliquer une technique pour extraire les lignes ici, par exemple, en utilisant un seuil.

    // Libérer la mémoire de l'accumulateur
    for (int i = 0; i < rhoCount; i++) {
        free(accumulator[i]);
    }
    free(accumulator);
}