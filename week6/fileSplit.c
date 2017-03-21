#include <stdio.h>


#define MAX 100

typedef struct {
  char name[20];
  char number[20];
} CONTACT;

void splitFile(FILE *f1, FILE *f2, FILE *f3){
  
}

int main(int argc, char *argv[])
{
  FILE *fp1, *fp2, *fp3;
  if (argc != 2) {
    printf("Wrong syntax!!!\n");
    printf("Syntax: *number of contacts\n");
    return 1;
  }

  fp1 = fopen("phoneDB.txt",'rb');
  if (fp1 == NULL) {
    printf("Cannot open file phoneDB.dat\n");
    return 1;
  }

  fp2 = fopen("phone1.dat",'wb');
  if (fp2 == NULL) {
    printf("Cannot open file phone1.dat\n");
    return 1;
  }

  fp3 = fopen("phone2.dat",'wb');
  if (fp3 == NULL) {
    printf("Cannot open file phone2.dat\n");
    return 1;
  }


  
  return 0;
}
