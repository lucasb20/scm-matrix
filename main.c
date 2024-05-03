#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <time.h>
#include "lib/funcs.h"
 
int main(int argc,char **argv){
  if(argc != 3){
      printf("Formato: %s <diretório> <nível de quantização>\n", *argv);
      puts("Níveis de Quantização: 8, 16, 32, 64, 128, 256");
      exit(1);
  }

  char *dir = argv[1];
  int level = atoi(argv[2]);

  clock_t begin,end;

  begin = clock();
  algTest(dir, level);
  end = clock();
  double tempo_total = (double)(end - begin)/CLOCKS_PER_SEC;
  printf("Tempo total: %lfs\n(%lf min)", tempo_total, tempo_total/60);

  return 0;
}
