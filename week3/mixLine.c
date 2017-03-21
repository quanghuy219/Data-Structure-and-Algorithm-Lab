#include <stdio.h>

#define MAX_LEN 100
 char str1[MAX_LEN],str2[MAX_LEN];

void mixLine(FILE *f1, FILE *f2, FILE *f3){
 
  void *t1,*t2;
  do
    {
      if((t1= fgets(str1,MAX_LEN,f1)) != NULL){
      fprintf(f3,"%s",str1);
      printf("%s",str1);
      }
      if(( t2  = fgets(str2,MAX_LEN,f2))!= NULL){
      fprintf(f3,"%s",str2);
      printf("%s",str2);
      }
    }
  while (t1 != NULL || t2 != NULL);
}

int main(int argc, char *argv[])
{
  printf("Syntax: merge file1 file2 file3\n");
  if (argc != 5) {
    printf("Invalid Input!!!\n");
    return -1;
  }

  
FILE *f1, *f2, *f3;
  f1 = fopen(argv[2],"r");
  if (f1 == NULL) {
    printf("Cannot open file %s\n",argv[2]);
    return -1;
  }

  f2 = fopen(argv[3],"r");
  if (f2 == NULL) {
    printf("Cannot open file %s\n",argv[3]);
    return -1;
  }

  f3 = fopen(argv[4],"w");
  if (f3 == NULL) {
    printf("Cannot write file %s\n",argv[4]);
    return -1;
  }

  mixLine(f1,f2,f3);

  fclose(f1);
  fclose(f2);
  fclose(f3);
  return 0;
}
