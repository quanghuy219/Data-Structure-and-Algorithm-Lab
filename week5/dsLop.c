#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 100

typedef struct {
  int STT;
  int mssv;
  char name[50];
  char phoneNumber[20];
  float mark;
} student;

student *std;

void writeFile(FILE *fin, int num_std,FILE* fout){
  int count;
  int tmp;
 
  count = fread(std,sizeof(student),num_std,fin);  
  printf("count = %d\n",count);
  tmp = fwrite(std,sizeof(student),num_std,fout);
  printf("tmp = %d\n",tmp);
  for (int i = 0; i < num_std; i++) {
    printf("%-5d%-10d%-30s%-15s%f\n",std[i].STT,std[i].mssv,std[i].name,std[i].phoneNumber,std[i].mark);
  }
}



void readFile(FILE *fin, int num_std){
  student *std1;
  int tmp;

  std1 = (student *)malloc(num_std * sizeof(student));
  tmp = fread(std1,sizeof(student),num_std,fin);
  printf("tmp = %d\n",tmp);
  for (int i = 0; i < num_std; i++) {
    printf("%-7d%-10d%-30s%-15s%.2f\n", std1[i].STT, std1[i].mssv, std1[i].name, std1[i].phoneNumber, std1[i].mark);
  }
  free(std1);
}





int main()
{
  FILE *fp1, *fp2;
  int num_std, line;
  char filebuff[MAX];

  fp1 = fopen("bangdiem.txt","rb");

  if (fp1 == NULL) {
    printf("Cannot open student list!\n");
    return 1;
  }


  fp2 = fopen("grade.dat","w+b");

  if (fp2 == NULL) {
    printf("Cannot open file grade.dat!!!\n");
    return 1;
  }

  
   line = 0;
  while (fgets(filebuff,MAX,fp1) != NULL) {
    line++;
  }

  num_std = line;

  
  fseek(fp1,0,SEEK_SET);
  
  std = (student *)malloc(num_std * sizeof(student) );
  printf("Sizeof(student) = %ld\n",sizeof(student));
  printf("line = %d, num_std = %d\n",line,num_std);
  writeFile(fp1,num_std,fp2);

  fseek(fp2,0,SEEK_SET);
  readFile(fp2, num_std);

  free(std);
  fclose(fp1);
  fclose(fp2);
 
  return 0;
}
