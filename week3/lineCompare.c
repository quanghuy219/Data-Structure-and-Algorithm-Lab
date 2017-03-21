#include <stdio.h>
#include <string.h>

#define MAX_LEN 100


void lineCompare(FILE *f1, FILE *f2, char *filename1, char *filename2){
  int line = 0;
  char filebuff1[MAX_LEN];
  char filebuff2[MAX_LEN];
  int count = 0;
  int arr[300];
  //printf("2 files differ at line(s): ");
  while (  (fgets(filebuff1,MAX_LEN,f1)) && (fgets(filebuff2,MAX_LEN,f2)) != NULL  ) {
    line++;
    if (strcmp(filebuff1,filebuff2) != 0) {
      arr[count] = line;
      count++;
      //printf("%d\n",line);
      // printf("%s: %s\n",filename1,filebuff1);
      //printf("%s: %s\n",filename2,filebuff2);
    }
  }
  printf("First line 2 files differ: %d\n",arr[0]);
  printf("2 files differ at line(s): ");
  for ( int i = 0; i < count; i++) {
    printf("%d   ",arr[i]);
  }
  printf("\n");
}

int main(int argc, char *argv[])
{
  if (argc != 3) {
    printf("Syntax Error!!!\n");
    printf("Syntax: file1 file2\n");
    return 1;
  }

  FILE *f1, *f2;
  char *filename1, *filename2;

  filename1 = argv[1];
  filename2 = argv[2];

  f1 = fopen(argv[1],"r");
  if (f1 == NULL) {
    printf("Cannot open file %s\n",argv[1]);
    return 1;
  }

  f2 = fopen(argv[2],"r");
  if (f2 == NULL) {
    printf("Cannot open file %s\n",argv[2]);
    return 1;
  }

  lineCompare(f1,f2,filename1,filename2);
  fclose(f1);
  fclose(f2);

  
  return 0;
}
