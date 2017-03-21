#include <stdio.h>

void insertSpace(FILE *fin){
  int c;
  while ( (c = fgetc(fin)) != EOF) {
    if (c == '\n') {
      fputc('\n',fin);
    }
  }
}

int main()
{
  FILE *f1;

  f1 = fopen("class1EF.txt","r+");
  if (f1 == NULL) {
    printf("Cannot open file\n");
  }

  insertSpace(f1);
  fclose(f1);
  return 0;
}
