#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include "lib/pgm.h"
#include "lib/funcs.h"
#include "lib/utils.h"

void algTest(char* diretorio, int level){
    DIR *d;
    struct dirent *dir;
    FILE *fp;

    char archiveName[20];
    sprintf(archiveName, "SCM_%d.txt", level);

    if(!(fp = fopen(archiveName,"w"))){
        puts("Erro ao abrir o arquivo");
        exit(1);
    }

    d = opendir(diretorio);

    if(!d){
        printf("Erro ao abrir o diretório '%s'.\n", diretorio);
        exit(1);
    }

    struct Image img, img_filt;

    while ((dir = readdir(d)) != NULL){
        if (strcmp(dir->d_name, ".") == 0 || strcmp(dir->d_name, "..") == 0) {
            continue;
        }

        char name[400];
        sprintf(name,"%s/%s", diretorio, dir->d_name);

        readPGMImage(&img, name);

        imageFilter(img, &img_filt);

        quantizer(&img, level);
        quantizer(&img_filt, level);

        SCM(img, img_filt, dir->d_name[0], fp, level);

        free(img_filt.Data);
    }

    fclose(fp);
    closedir(d);
}

void imageFilter(struct Image src, struct Image *des){
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

void quantizer(struct Image *img, int level){
    int n = (img->maxval + 1) / level;
    int start = 0;
    int end = n - 1;

    for(int k = 0; k < level; k++){
        for (int i = 0; i < img->width * img->height; i++){
            if (img->Data[i] >= start && img->Data[i] <= end){
                img->Data[i] = k;
            }
        }

        start = end + 1;
        end = start + n - 1;
    }
}

void SCM(struct Image img, struct Image img_filt, char label, FILE *fp , int level){
    unsigned char *matrix = NULL;
  
    if(!(matrix = calloc(level*level, sizeof(unsigned char)))){
        puts("Memória insuficiente.");
        exit(1);
    }

    for(int i = 0; i < img.width * img_filt.height; i++){
        int index = img.Data[i]*level + img_filt.Data[i];
        matrix[index]++;
    }

    for(int i = 0; i < level * level; i++){
        fprintf(fp, "%hhu, ", matrix[i]);
    }

    free(matrix);
    fprintf(fp, "%s\n", label == '0'?"epithelium":"stroma");
}