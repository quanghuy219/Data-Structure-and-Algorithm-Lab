#include <stdio.h>
#include <string.h>


void displayContent(FILE *fin){
  int c;

  while ((c= fgetc(fin)) != EOF) {
    putchar(c);
  }
}


void pageByPage(FILE *fin){
  int c , count = 0;
  printf("Page 1 \n\n");
  while ((c = fgetc(fin))  != EOF) {
    
   
    if(c == '\n'){
      count++;

      if( (count % 25) == 0){
      printf("\n\nPage %d\n", count/25 + 1);
      }
      
    }
    putchar(c); 
  }
  
}


int main(int argc, char *argv[])
{
  printf("Syntax: \n");
  printf("1. cat <filename> : display content to the end\n");
  printf("2. cat <filename> -p : view pge by page\n");

  if (argc != 3 && argc != 4) {
    printf("Wrong syntax\n");
    printf("1. cat <filename> : display content to the end\n");
    printf("2. cat <filename> -p : view pge by page\n");
    return -1;
  }

  if (strcmp(argv[1] , "cat") != 0){
    printf("Wrong syntax\n");
    printf("1. cat <filename> : display content to the end\n");
    printf("2. cat <filename> -p : view pge by page\n");
    return -1;
  }

  if (argc == 4 && strcmp(argv[3],"-p") != 0) {
    printf("Wrong syntax\n");
    printf("1. cat <filename> : display content to the end\n");
    printf("2. cat <filename> -p : view pge by page\n");
    return -1;
  }

  
  FILE *f1;

  f1 = fopen(argv[2],"r");
  if (f1 == NULL) {
    printf("Cannot open file\n");
    return -1;
  }

  if(argc == 3) {
    displayContent(f1);
  }

  if (argc == 4) {
    pageByPage(f1);
  }

  fclose(f1);

  
  return 0;
}
