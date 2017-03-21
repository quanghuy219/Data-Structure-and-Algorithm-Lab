#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum {SUCCESS, FAIL, MAX_ELEMENT=20};

typedef struct {
  char name[20];
  char tel[11];
  char email[25];
}phonebook;

phonebook person[100];
phonebook person1[100];

void writePhone(FILE *fin, int num){
  int count;
  char filebuff[100];
  count = fwrite(person,sizeof(phonebook),num,fin);
  printf("fwrite return %d\n",count);
}


void readPhone(FILE *fin, int num){
  int count;
  int i;
  count = fread(person1,sizeof(phonebook),num,fin);
  printf("fread return %d\n",count);
  for (i = 0; i < num; i++) {
    printf("#%d\n",i+1);
    printf("%-30s",person1[i].name);
    printf("%-20s",person1[i].tel);
    printf("%s\n",person1[i].email);
  }
}

int main()
{
  int num;
  int tmp;
  printf("How many people do you want to add: ");
  scanf("%d",&num);
  while(getchar() != '\n');
  for (int i = 0; i < num; i++) {
    printf("#%d\n",i+1);
    printf("Name: ");
    fgets(person[i].name,20,stdin);
    tmp = strlen(person[i].name) - 1;
    if (person[i].name[tmp] == '\n') {
      person[i].name[tmp] = '\0';
    }
    printf("Telephone: ");
    scanf("%s%*c",person[i].tel);
    printf("E-mail: ");
    scanf("%s%*c",person[i].email);
  }


  FILE *fp1;
  fp1 = fopen("phonebook.txt","w+b");
  if (fp1 == NULL) {
    printf("Cannot open phonebook\n");
    return 1;
  }

  writePhone(fp1,num);
  fseek(fp1,0,SEEK_SET);
  readPhone(fp1,num);
  fclose(fp1);
  
  return 0;
}
