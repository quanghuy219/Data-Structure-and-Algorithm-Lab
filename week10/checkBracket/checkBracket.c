#include <stdio.h>
#include <stdlib.h>
#include "nodeStack.h"

int flag=0;

void check(FILE *fin, stackType *s1){
  char buff[MAX];
  char c;
  Eltype x;
  int cout_line = 1;

  while ( (c=fgetc(fin)) != EOF) {
    if (c == '\n') {
      cout_line++;
    }
    else if (c == '{') {
      push(s1,'{',cout_line);
    }
    else if (c == '[') {
      push(s1,'[',cout_line);
    }
    else if (c == '(') {
      push(s1,'(',cout_line);
    }

    else if (c == '}') {
      x = pop(s1);
      if (x.bracket != '{') {
        printf("Line: %d::::Missing closing bracket for '%c'\n",x.line,x.bracket);
        flag = 1;
      }
    }

    else if (c == ']') {
      x = pop(s1);
      if (x.bracket != '[') {
        printf("Line: %d::::Missing closing bracket for '%c'\n",x.line,x.bracket);
        flag = 1;
      }
    }

    else if (c == ')') {
      x = pop(s1);
      if ((x.bracket) != '(') {
        printf("Line: %d::::Missing closing bracket for '%c'\n",x.line,x.bracket);
        flag = 1;
      }
    }
  }

  while (!empty(s1)) {
    x = pop(s1);
    if (x.bracket == '{' || x.bracket == '[' || x.bracket == '(') {
      printf("Line: %d::::Missing closing bracket for '%c'\n",x.line,x.bracket);
      flag = 1;
    }

     else if (x.bracket == '}' || x.bracket == '}' || x.bracket == ')') {
      printf("Line: %d::::Missing opening bracket for '%c'\n",x.line,x.bracket);
      flag = 1;
    }

  }
  printf("\n");
}

int main() {
  stackType s1;
  Initialize(&s1);
  FILE *f1 = fopen("try.txt","r");
  if (f1 == NULL) {
    printf("Failed to read file\n");
    return 0;
  }

  check(f1,&s1);
  if (flag == 0) {
    printf("Matching parenthesis\n\n");
  }

  return 0;
}
