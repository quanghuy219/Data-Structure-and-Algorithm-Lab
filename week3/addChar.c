#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{

  FILE *fp1;
  char filebuff[100];
  char a[80];
  int i;
  printf("Syntax: filename\n");

  fp1 = fopen(argv[1],"a+");
  if (fp1 == NULL) {
    printf("Couldnt open file\n");
    return 1;
  }
  i = 0;
  while (fgets(filebuff,100,fp1) != NULL) {
    a[i] = filebuff[0];
    i++;
  }
  a[i] = '\0';

  
    fprintf(fp1,"%s",a);
  

  fclose(fp1);
  return 0;
}
