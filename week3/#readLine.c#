#include <stdio.h>
#include <string.h>

#define MAX_LEN 100

void readLine(FILE *fin, FILE *fout){
  char str[MAX_LEN];
  int line_len;

  while ( fgets(str,MAX_LEN,fin) != 0) {
    line_len = strlen(str);
    fprintf(fout,"%d %s",line_len,str);
  }
}

int main(int argc, char *argv[])
{

  printf("Syntax: filename\n");
  if (argc != 2) {
    printf("Invalid syntax!!!\n");
    return -1;
  }

  FILE *f1;
  FILE *f2;
  char *filename = argv[1];

  f1 = fopen(filename,"r");
  if (f1 == NULL) {
    printf("Cannot open file\n");
    return -1;
  }

  f2 = fopen("txtfile.txt","w");
  if (f2 == NULL) {
    printf("Cannot write\n");
    return -1;
  }

  readLine(f1,f2);
  fclose(f1);
  fclose(f2);
  return 0;
}
