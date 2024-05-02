#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include "lib/pgm.h"
#include "lib/utils.h"

void AlgTest(char* diretorio){
    DIR *d;
    struct dirent *dir;

    d = opendir(diretorio);

    FILE *file_ptr = fopen("alg.txt","w");

    if(!(file_ptr)){
        puts("Erro ao abrir criar o arquivo.");
        exit(1);
    }

    if(!d){
        printf("Erro ao abrir o diretório '%s'.\n", diretorio);
        exit(1);
    }

    struct Image img;
    struct Image *img_filt;

    if(!(img_filt = malloc(sizeof(struct Image)))){
        puts("Erro ao alocar memória.");
        exit(1);
    }

    while ((dir = readdir(d)) != NULL){
        if (strcmp(dir->d_name, ".") == 0 || strcmp(dir->d_name, "..") == 0) {
            continue;
        }

        char name[400];
        sprintf(name,"%s/%s", diretorio, dir->d_name);

        readPGMImage(&img, name);

        ImageFilter(img, img_filt);

        fprintf(file_ptr, "%s, %d, %d\n", dir->d_name);
    }
    fclose(file_ptr);
    closedir(d);
}

void ImageFilter(struct Image src, struct Image *des){
    des->type = src.type;
    des->height = src.height;
    des->width = src.width;
    des->maxval = src.maxval;

    if (!(des->Data = (unsigned char *) calloc(src.width * src.height, sizeof(unsigned char)))){
        printf("Falta de memória.\n");
        exit(1);
    }

    for(int i = 0; i < src.height * src.width; i++){
        src.Data[i] = src.Data[i];
    }

    for(int i = 0; i < src.height; i++){
        for(int j = 0; j < src.width; j++){
            des->Data[i*src.width + j] = kernel_mean(src, i, j, 3);
        }
    }
}