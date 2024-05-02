#include <stdio.h>
#include <stdlib.h>
#include "lib/pgm.h"

void readPGMImage(struct Image *img, char *filename) {

    FILE *fp;
    char ch;

    if (!(fp = fopen(filename, "r"))) {
        perror("Erro.");
        exit(1);
    }

    if ((ch = getc(fp)) != 'P') {
        puts("A imagem fornecida não está no formato pgm");
        exit(1);
    }

    img->type = getc(fp);
    if (img->type != '2' && img->type != '5') {
        puts("Formato de imagem PGM não suportado.");
        exit(1);
    }

    fseek(fp, 1, SEEK_CUR);

    while ((ch = getc(fp)) == '#') {
        while ((ch = getc(fp)) != '\n');
    }

    fseek(fp, -1, SEEK_CUR);

    fscanf(fp, "%d %d", &img->width, &img->height);
    if (ferror(fp)) {
        perror(NULL);
        exit(3);
    }
    fscanf(fp, "%hhu", &img->maxval);
    fseek(fp, 1, SEEK_CUR);

    img->Data = (unsigned char *)malloc(img->width * img->height * sizeof(unsigned char));
    if (img->Data == NULL) {
        perror("Erro ao alocar memória.");
        exit(1);
    }

    switch (img->type) {
        case '2':
            puts("Lendo imagem PGM (dados em texto)");
            for (int i = 0; i < img->width * img->height; i++) {
                fscanf(fp, "%hhu", &img->Data[i]);
            }
            break;
        case '5':
            puts("Lendo imagem PGM (dados em binário)");
            fread(img->Data, sizeof(unsigned char), img->width * img->height, fp);
            break;
    }

    fclose(fp);
}

void writePGMImage(struct Image *img, char *filename) {
    FILE *fp;

    if (!(fp = fopen(filename, "wb"))) {
        perror("Erro.");
        exit(1);
    }

    fprintf(fp, "%s\n", "P5");
    fprintf(fp, "%d %d\n", img->width, img->height);
    fprintf(fp, "%hhu\n", img->maxval);

    fwrite(img->Data, sizeof(unsigned char), img->width * img->height, fp);

    fclose(fp);
}

void viewPGMImage(struct Image *img) {
    printf("Tipo: P%c\n", img->type);
    printf("Dimensões: [%d %d]\n", img->width, img->height);
    printf("Max: %hhu\n", img->maxval);

    for (int i = 0; i < img->height; i++) {
        for (int j = 0; j < img->width; j++) {
            printf("%3d ", img->Data[i * img->width + j]);
        }
        printf("\n");
    }
}