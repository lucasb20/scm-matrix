#include <dirent.h>
#include "library.h"

#define QTDIMG 1312
#define FOLDER "./oncotex_pgm"
 
int main(){
  
	clock_t begin, end;
	double time_per_img, time_total=0;
  
  DIR *d;
  struct dirent *dir;
  d = opendir(FOLDER);

  FILE *fp;

  if (!(fp = fopen("matrixOrder.txt","a+"))){
		perror("Erro.");
		exit(1);
	}

  if (d){
    int level = menu();
    printf("Nivel: %d\n\n", level);
    
    
    while (((dir = readdir(d)) != NULL)){
      if (!strcmp(dir->d_name, ".") || !strcmp(dir->d_name,"..")){
        continue;
      }

      if(strstr(dir->d_name,"mean")){
        continue;
      }

      begin = clock();

      struct pgm img1, img2;

      readPGMImage(&img1,FOLDER,dir->d_name);
      
      quantize(&img1,level);

      for(int i=0;i<strlen(dir->d_name);i++){
        if(dir->d_name[i] == '.') {
          dir->d_name[i]='\0';
          fprintf(fp, "%s\n", dir->d_name);
        }
      }

      strcat(dir->d_name,"_mean.pgm");
      
      readPGMImage(&img2,FOLDER,dir->d_name);
      
      quantize(&img2,level);
      
      SCM(&img1, &img2, dir->d_name, level);
      

      end = clock();

      time_per_img = (double)(end - begin) / CLOCKS_PER_SEC;
		  time_total += time_per_img;
    }
    fclose(fp);
    closedir(d);
    
    printf("\nTempo médio: %lf\n",time_total/(QTDIMG/2));
    printf("Tempo Total: %lf\n",time_total);
  }

  return(0);
}
