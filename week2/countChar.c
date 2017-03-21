#include <stdio.h>
#include <ctype.h>

int main(int argc, char *argv[])
{

  if (argc != 2) {
    printf("Syntax Error!!!\nSyntax: <filename>\n");
    return -1;
  }
  
  FILE *fp;
  char *filename = argv[1];
  int stats[256] = {0};
  int ch,i;
  

  fp = fopen(filename,"r");
  if (fp == NULL) {
    printf("Cannot open file\n");
    return -1;
  }

  while ( (ch = fgetc(fp)) != EOF) {
    stats[tolower(ch)]++;
  }

  fclose(fp);

  FILE *fout;

  fout = fopen("statsfile.txt","w");
  if (fout == NULL) {
    printf("Cannot create file\n");
  }

  

  for (i = 0; i < 256; i++) {
    if (stats[i] > 0) {
      fprintf(fout,"%c  :  %d\n",i,stats[i]);
      printf("%c  :   %d\n",i,stats[i]);
    }
  }
  fclose(fout);
 
  return 0;
}
