#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

char *my_strcat(char *str1, char *str2){
  int len1 = strlen(str1);
  int len2 = strlen(str2);
  int n = 0;
  char *result;
  result = (char *)malloc( (len1+len2+1) * sizeof(char) );
  
  if (result == NULL) {
    printf("Allocation failed!\n");
    return NULL;
  }

  strcpy(result,str1);
  strcpy(result+len1,str2);
  return result;
}

int main()
{
  char str1[MAX+1], str2[MAX+1];
  char *str_cat;

  printf("Enter 2 strings: \n");
  scanf("%100s",str1);
  scanf("%100s",str2);
  str_cat = my_strcat(str1,str2);
  if (str_cat == NULL) {
    printf("Problem allocating memory!\n");
    return 1;
  }

  printf("Strcat(str1,str2) = %s\n",str_cat);
  free(str_cat);
  return 0;
}
