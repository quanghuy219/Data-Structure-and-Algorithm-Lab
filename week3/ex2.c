#include <stdio.h>

void insertSpace(FILE *fin, FILE *fout){
  char str[100];
  while ( fgets(str,100,fin) != NULL) {
    fputs(str,fout);
    printf("%s",str);
  }
}

int main()
{
  FILE *f1,*f2;

  f1 = fopen("class1EF.txt","r");
  if (f1 == NULL) {
    printf("Cannot open file\n");
    return -1;
  }

  f2 = fopen("newfile.txt","w");
  if (f2 == NULL) {
    printf("Cannot open file\n");
    return -1;
  }

  insertSpace(f1,f2);
  fclose(f1);
  fclose(f2);
  return 0;
}
