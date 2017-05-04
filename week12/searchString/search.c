#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

typedef struct {
  char word[MAX];
} words;

int line;

void buildList(FILE *fin, words* list){
  char buff[MAX];
  while (fgets(buff,100,fin) != NULL) {
    strcpy(list[line].word,buff);
    if ( list[line].word[strlen(list[line].word)-1] == '\n') {
      list[line].word[strlen(list[line].word)-1] = '\0';
    }
    line++;
  }
}


int binarySearch(words* list,int left,int right,char str[]){
    int mid;
    if (left > right) {
      printf("Not found\n");
      return -1;
    }

    mid = (left+right)/2;
    if ( strcmp(list[mid].word,str) == 0) {
      return mid;
    }
    else if (strcmp(list[mid].word,str) > 0) {
      binarySearch(list,left,mid-1,str);
    }
    else if (strcmp(list[mid].word,str) < 0) {
      binarySearch(list,mid+1,right,str);
    }
}


void relatedWord(words* list, int n){
  int len = strlen(list[n].word);
  int i = n;
  char buff[len];
  strcpy(buff,list[n].word);
  while (strcmp(buff,list[n].word) == 0) {
    strcpy(buff,list[i].word);
    buff[len] = '\0';
    if(strcmp(buff,list[n].word) == 0)  printf("%s\n",list[i].word);
    i++;
  }
}




int main(int argc, char *argv[]) {
  char str[MAX];
  line = 0;
  strcpy(str,argv[1]);
  str[strlen(str)] = '\0';
  FILE *fp = fopen("words","r");
  if (fp == NULL) {
    printf("Cannot read file Words\n");
    return 1;
  }
  words *list;
  fseek(fp,0,SEEK_END);
  int size = ftell(fp);
  fseek(fp,0,SEEK_SET);
  list = (words*)malloc( size * sizeof(words));
  buildList(fp,list);

  int index = binarySearch(list,0,line,str);

  if(index != -1) relatedWord(list,index);
  return 0;
}
