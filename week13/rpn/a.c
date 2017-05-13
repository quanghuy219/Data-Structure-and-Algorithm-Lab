#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* test(char *a){
  char *x = (char*)malloc(sizeof(char)*8);
  x = a;
  return x;
}

int main(int argc, char const *argv[]) {
  char a[100] = "aaaaa";
  char tmp[100];
  //strcpy(tmp,test(a));
  tmp[0] = test(a)[0];
  printf("a = %s\n",a);
  printf("tmp = %c\n",tmp[0]);
  strcpy(tmp,"bbbbbb");
  printf("a = %s\n", a);
  printf("tmp = %s\n", tmp);
  return 0;
}
