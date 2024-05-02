#ifndef PGM_H
#define PGM_H

struct Image {
    char type;
    int width;
    int height;
    unsigned char maxval;
    unsigned char *Data;
};

void readPGMImage(struct Image *, char *);
void viewPGMImage(struct Image *);
void writePGMImage(struct Image *, char *);

#endif