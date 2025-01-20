#include <stdio.h>
#include "image.h"

// Prototypes des nouvelles fonctions
void adjustBrightness(Image *image, int adjustment);
void adjustContrast(Image *image, double factor);
void applyThreshold(Image *image, int threshold);
void applyMeanFilter(Image *image);
void applyPrewittFilter(Image *image);
Image resizeImage(const Image *image, double scaleFactor);
Image subtractImages(const Image *image, const Image *image1);
Image addImages(const Image *image, const Image *image1);
void applyOtsuThreshold(Image *image); // Ajout
void applyHoughTransform(const Image *image, Image *image1); // Ajout du prototype


void printMenu() {
    printf("Menu:\n");
    printf("1. Adjust Brightness\n");
    printf("2. Adjust Contrast\n");
    printf("3. Apply Threshold\n");
    printf("4. Apply Mean Filter\n");
    printf("5. Apply Prewitt Filter\n");
    printf("6. Resize Image\n");
    printf("7. Subtract Images\n");
    printf("8. Add Images\n");
    printf("9. Apply Otsu Threshold\n"); // Ajout
    printf("10. Apply Hough Transform\n"); // Ajout
    printf("11. Exit\n");
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Veuillez fournir le chemin relatif de l'image en argument\n");
        return 1;
    }

    const char *filename = argv[1];
    Image image = loadImage(filename);

    const char *filename1 = argv[2];
    Image image1 = loadImage(filename1);

    int choice;
    do {
        printMenu();
        printf("Entrez votre choix: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                int adjustment;
                printf("Entrez le niveau d'ajustement de la luminosité: ");
                scanf("%d", &adjustment);
                adjustBrightness(&image, adjustment);
                saveImage(&image);
                
                break;
            }
            case 2: {
                double factor;
                printf("Entrez le facteur de contraste: ");
                scanf("%lf", &factor);
                adjustContrast(&image, factor);
                saveImage(&image);
                
                break;
            }
            case 3: {
                int threshold;
                printf("Entrez le seuil: ");
                scanf("%d", &threshold);
                applyThreshold(&image, threshold);
                saveImage(&image);
                //freeImage(&image);
                break;
            }
            case 4:
                applyMeanFilter(&image);
                saveImage(&image);
                //freeImage(&image);
                break;
            case 5:
                applyPrewittFilter(&image);
                saveImage(&image);
                //freeImage(&image);
                break;
            case 6: {
                double scaleFactor;
                printf("Entrez le facteur d'échelle: ");
                scanf("%lf", &scaleFactor);
                Image resizedImage = resizeImage(&image, scaleFactor);
                saveImage(&resizedImage);
                //freeImage(&resizedImage);
                break;
            }
            case 7: {
                Image subImage = subtractImages(&image, &image1);
                saveImage(&subImage);
                freeImage(&subImage);
                break;
            }
            case 8: {
                Image addImage = addImages(&image, &image1);
                saveImage(&addImage);
                //freeImage(&addImage);
                break;
            }
            case 9: { // Appliquer Otsu
                applyOtsuThreshold(&image);
                saveImage(&image);
                break;
            }
            case 10: {
                    Image image1; // Image de sortie pour Hough
                    applyHoughTransform(&image, &image1);
                    saveImage(&image1); // Sauvegarde de l'image transformée
                    freeImage(&image1);  // Libération de la mémoire
                    break;
                }
                case 11:
                    printf("Sortie du programme.\n");
                    break;
                default:
                    printf("Choix invalide. Veuillez réessayer.\n");
            }

    } while (choice != 9);

    freeImage(&image);
    freeImage(&image1);

    return 0;
}