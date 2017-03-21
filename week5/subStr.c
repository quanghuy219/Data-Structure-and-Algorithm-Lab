#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100


char* subStr(char *s1, int offset,int number){
  char *result;
  int j = 0;

  result = (char *)malloc( strlen(s1) * sizeof(char) );
  if (offset + number > strlen(s1)) {
    printf("Number of character exceeds the resting character of string\n");
    strcpy( result, s1+(offset-1) );
    return result;
  }

  else {
   for (int i = offset; i < offset + number; i++) {
     result[j] = s1[i];
     j++;
   }
   return result;
  }
  
}


int main()
{
  char str[MAX];
  int i;
  char *sub_str;
  int offset,num_char;
  printf("Enter a string: ");
  fgets(str, MAX, stdin);
  i = strlen(str) - 1;
  if (str[i] == '\n') {
    str[i] = '\0';
  }

  printf("Enter offset index and number of character: \n");
  scanf("%d%d",&offset,&num_char);

  sub_str = subStr(str,offset,num_char);
  printf("Substring: %s\n",sub_str);
  free(sub_str);

  return 0;
}

