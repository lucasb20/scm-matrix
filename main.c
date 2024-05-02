#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <time.h>
 
int main(int argc,char **argv){
  if(argc != 2){
      printf("Formato: %s <diretório>\n", *argv);
      exit(1);
  }

  clock_t begin,end;

  begin = clock();
  alg();
  end = clock();
  double tempo_total = (double)(end - begin)/CLOCKS_PER_SEC;
  printf("Tempo total: %lfs\n(%lf min)", tempo_total,tempo_total/60);

  return 0;
}
