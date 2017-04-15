#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 100

typedef struct {
	char id[ID_LENGTH];
	char name[NAME_LENGTH];
	int grade;
} STUDENT;


void convertToDAT(FILE* fp1, FILE* fp2){
  char *buff;
   buff = (char *)malloc(sizeof(STUDENT));
   buff[MAX * sizeof(char)] = '\0';

   while(fgets(buff,MAX,fp1) != NULL){
     fwrite(buff,MAX,sizeof(char),fp2);
  }
}
