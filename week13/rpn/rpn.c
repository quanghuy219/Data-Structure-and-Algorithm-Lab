#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "nodeStack.h"

int priority(char x)
{
    if(x == '(')
        return 0;
    if(x == '+' || x == '-')
        return 1;
    if(x == '*' || x == '/')
        return 2;
    if(x== '^')
        return 3;
}

int checkOperator(char x){
  if (x == '+' || x == '-' || x == '*' || x == '/' || x == '^') {
    return 1;
  }
  else return 0;
}

void Traverse(stackType stack){
  Node *p = stack.top;
  printf("\n");
  while (p != NULL) {
    printf("%s    ",p -> data);
    p = p -> prev;
  }
  printf("\n");
}

int main() {
  char exp[MAX];
  char tmp[MAX];
  char x;
  int i = 0;
  stackType s1,post;

  Initialize(&s1);
  Initialize(&post);

  printf("Enter an expression: ");
  scanf("%s",exp);
  exp[strlen(exp)] = ')';
  strcpy(tmp,"(");
  push(&s1,tmp);
  tmp[0] = '\0';

  while ( i <= strlen(exp) ) {

    // if ( isdigit(exp[i]) || isalpha(exp[i])) {
    //   printf("%c",exp[i]);
    // }
    if(isdigit(exp[i])){
      while (isdigit(exp[i])) {
        tmp[strlen(tmp)] = exp[i];
        i++;
      }
      push(&post,tmp);
      tmp[0] = '\0';
    }


     if (exp[i] == '(') {
      push(&s1,"(");
    }

    if ( checkOperator(exp[i]) ) {
      strcpy(tmp,Top(&s1));
      while ( priority(tmp[0]) >= priority(exp[i]) ) {
        //printf("%c",Top(&s1));
        push(&post,Top(&s1));
        pop(&s1);
        strcpy(tmp,Top(&s1));
      }
      tmp[0] = exp[i];
      tmp[1] = '\0';
      push(&s1,tmp);
      tmp[0] = '\0';
    }

  // else  if (exp[i] == ')') {
  //     while ( strcmp(Top(&s1),"(") != 0) {
  //       //printf("%c",x);
  //       //tmp[0] = x;
  //       push(&post,pop(&s1));
  //     }
  //     tmp[0] = '\0';
  //   }
    i++;
  }
  Traverse(post);
  printf("\n\n");
  return 0;
}
