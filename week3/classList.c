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


void getInfomation(student a[], FILE *fin, int *num_std){ //get stt and student ID
  char filebuff[MAX];
  int line = 0;
  char tmp[MAX];
  int start,end;
  int n, m = 0;
  
  while ( fgets(filebuff,MAX,fin) != NULL  ) {
    
    if(sscanf(filebuff,"%d %d", &a[line].STT,&a[line].mssv)  != 2){
      printf("Line %d: Wrong information!!!\n",line+1);
      continue;
    }
   

    for (n = 0; n < strlen(filebuff); n++) {
      if ( isalpha(filebuff[n]) ) {
	start = n;
	break;
      }
    }
    for (n = strlen(filebuff); n > start; n--) {
      if ( isalpha(filebuff[n]) ) {
	end = n;
	break;
      }
    }
    m = 0;
    for (n = start; n <= end; n++) {
      tmp[m] = filebuff[n];
      m++;
    }
   
    strcpy(a[line].name,tmp);

    m = 0;
    for (n = end; n < strlen(filebuff); n++) {
      if( isdigit(filebuff[n]) ){
	tmp[m] = filebuff[n];
	m++;
      }
    }
    tmp[m] = '\0';
    strcpy(a[line].phoneNumber,tmp);
    
    line++;
  }
  *num_std = line;
}



void addMark(student a[], int *num_std){
  int i;
  printf("Enter mark of each student\n");
  for (i = 0; i < *num_std; i++) {
    printf("Student #%d: ",i+1);
    scanf("%f",&a[i].mark);
  }
}



void printInfo(student a[], int *num_std){
  int i;
  printf("%-7s%-10s%-30s%-15s\n","STT","MSSV","Name","Phone Number");
  for (i = 0; i < *num_std; i++) {
    printf("%-7d%-10d%-30s%-15s\n",a[i].STT,a[i].mssv,a[i].name,a[i].phoneNumber);
  }
}



void printStudentMark(FILE *fin, int *num_std, student a[]){
  int i;
  for (i = 0; i < *num_std; i++) {
    fprintf(fin, "%-7d  %-10d  %-30s  %-15s  %.2f\n", a[i].STT, a[i].mssv, a[i].name, a[i].phoneNumber, a[i].mark);
  }
}




int main()
{
  FILE *fp1 , *fp2;
  student std[20];
  int num_std;

  fp1 = fopen("studentList.txt","r");
  if (fp1 == NULL) {
    printf("Cannot open student list!!!\n");
    return 1;
  }

  getInfomation(std,fp1,&num_std);
  // getName(std,fp1,&num_std);
  printInfo(std,&num_std);

  fclose(fp1);

  fp2 = fopen("bangdiem.txt","w");
  if (fp2 == NULL) {
    printf("Cannot open file %s\n","bangdiem.txt");
    return 1;
  }
  addMark(std,&num_std);
  printStudentMark(fp2,&num_std,std);
  fclose(fp2);

  return 0;
}
