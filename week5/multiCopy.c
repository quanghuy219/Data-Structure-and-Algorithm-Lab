#include <stdio.h>
#include <time.h>

#define MAX 1000


void copyCharacter(FILE* fin, FILE* fout){
  char c;
  while (  (c=fgetc(fin)) != EOF) {
    fputc(c,fout);
  }
}




void copyLine(FILE* fin, FILE* fout){
  char buff[MAX];
  
  while ( fgets(buff,MAX,fin) != NULL) {
    fputs(buff,fout);
  }
}





void copyBlock(FILE* fin, FILE* fout){
  int size;
  char buff[MAX];
  printf("Enter size of block: ");
  scanf("%d",&size);
  while (!feof(fin)) {
    fread(buff,sizeof(char),size,fin);
    buff[size * sizeof(char)] = '\0';
    fwrite(buff,sizeof(char),size,fout);
  }
}




int main()
{
  FILE* fp1, *fp2;
  int choice;
  clock_t start,end;
  double time;

  printf("1. Copy character\n");
  printf("2. Copy lines\n");
  printf("3. Copy block\n");
  scanf("%d",&choice);
  switch (choice) {
  case 1: {
    fp1 = fopen("filetext.txt","r");
    if (fp1 == NULL) {
      printf("Cannot open file\n");
      break;
    }
    fp2 = fopen("destination1.txt","w");
    if (fp2 == NULL) {
      printf("Cannot open destination file\n");
      break;
    }
    start = clock();
    copyCharacter(fp1,fp2);
    end = clock();
    time = ( (double)(end - start) )/CLOCKS_PER_SEC;
    printf("time = %f\n",time);
    break;
  }

  case 2: {
     fp1 = fopen("filetext.txt","r");
    if (fp1 == NULL) {
      printf("Cannot open file\n");
      break;
    }
    fp2 = fopen("destination2.txt","w");
    if (fp2 == NULL) {
      printf("Cannot open destination file\n");
      break;
    }
     start = clock();
    copyLine(fp1,fp2);
    end = clock();
    time = ( (double)(end - start) )/CLOCKS_PER_SEC;
    printf("time = %f\n",time);
    break;
  }
  case 3: {
     fp1 = fopen("filetext.txt","rb");
    if (fp1 == NULL) {
      printf("Cannot open file\n");
      break;
    }
    fp2 = fopen("destination3.txt","wb");
    if (fp2 == NULL) {
      printf("Cannot open destination file\n");
      break;
    }
     start = clock();
    copyBlock(fp1,fp2);
    end = clock();
    time = ( (double)(end - start) )/CLOCKS_PER_SEC;
    printf("time = %f\n",time);
    break;
  }
  default: printf("Wrong Syntax!!!\n");
    break;
  }
  printf("\n");
  fclose(fp1);
  fclose(fp2);
  return 0;
}
