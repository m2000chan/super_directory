#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/stat.h>
#include <math.h>
#include <dirent.h>
#include <sys/types.h>

int main(){

  printf("Statistics for directory:\n\n");

  DIR * dir = opendir(".");
  struct dirent * curr;
  char * files = malloc(5000);
  char * direc = malloc(5000);

  
  while((curr = readdir(dir))){

    if (curr -> d_type == 4){
      strcat(direc, "\t");
      strcat(direc, curr -> d_name);
      strcat(direc, "\n");

    }

    else{
      strcat(files, "\t");
      strcat(files, curr -> d_name);
      strcat(files, "\n");
    }
  }

  printf("DIRECTORIES:\n\n%s",direc);
  printf("FILES:\n\n%s", files);

  int truesize = 0;

  closedir(dir);

  dir = opendir(".");

  while ((curr = readdir(dir))){

     struct stat storage;
     stat(curr -> d_name, &storage);

     truesize += storage.st_size;

  }

  int i = 0;

  while ((int)(truesize / pow(1024, i)) > 0){ //raises the power of 1024 to i
    printf("Truesize: %d\n", truesize);
    printf("Denominator: %lf\n", pow(1024, i));
    
    i++;
  }

  i--;
  
  float human_read = truesize / pow(1024, i);

  //printf("Truesize: %d\n", truesize);
  //printf("power: %lf\n", pow(1024, i));
  //printf("i: %d\n", i);
  
  char * size = malloc(2);

  if (i == 0){size = "B";};
  if (i == 1){size = "KB";};
  if (i == 2){size = "MB";};
  if (i == 3){size = "GB";};
  
  printf("\nSize of Directory:  %d %s\n", (int)round(human_read), size);
  
  return 0;

}
