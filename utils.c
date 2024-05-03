#include "lib/pgm.h"

int kernel_mean(struct Image obj, int x, int y, int size){
    int m = 0;

    int piv = size / 2;

    for (int i = -piv; i <= piv; i++)
    {
        for (int j = -piv; j <= piv; j++)
        {
            if(!(x + i < 0) && !(y + j < 0) && x + i < obj.height && y + j < obj.width){
                m += obj.Data[(x + i) * obj.width + (y + j)];
            }
        }
    }

    m /= size*size;

    return m;
}
