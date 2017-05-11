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
    printf("%c    ",p -> data);
    p = p -> prev;
  }
  printf("\n");
}

char *postfix(char exp[]) {
  //char exp[MAX];
  static char p[MAX] = "";
  char x;
  int i = 0;
  stackType s1;

  Initialize(&s1);

  // printf("Enter an expression: ");
  // scanf("%s",exp);
  exp[strlen(exp)] = ')';

  push(&s1,'(');

  while ( !empty(&s1) ) {

    if ( isdigit(exp[i]) || isalpha(exp[i])) {
      //printf("%c",exp[i]);
      //strcat(p,exp[i]);
      p[strlen(p)] = exp[i];
    }

    else if (exp[i] == '(') {
      push(&s1,'(');
    }

    else if ( checkOperator(exp[i]) ) {
      while ( priority(Top(&s1)) >= priority(exp[i]) ) {
        //printf("%c",Top(&s1));
        //strcat(p,Top(&s1));
        p[strlen(p)] = Top(&s1);
        pop(&s1);
      }
      push(&s1,exp[i]);
    }

    else if (exp[i] == ')') {
      while ( (x=pop(&s1)) != '(') {
        //printf("%c",x);
        //strcat(p,x);
        p[strlen(p)] = x;
      }

    }
    i++;
  }
  return p;
}
