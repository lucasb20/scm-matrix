#include "lib/pgm.h"

int kernel_mean(struct Image obj, int x, int y, int dim){
    int m = 0;

    int piv = dim / 2;

    for (int i = -piv; i <= piv; i++)
    {
        for (int j = -piv; j <= piv; j++)
        {
            if(i > 0 && j > 0 && i < obj.height && j < obj.width){
                m += obj.Data[(x + i) * obj.width + (y + j)];
            }
        }    
    }

    m /= 9;

    return m;
}

int PowerOf2(int x){
    if(x == 0){
        return 1;
    }
    return PowerOf2(x - 1)*2;
}