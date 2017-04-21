#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "nodeStack.h"


int checkOperator(char x){
  if (x == '+' || x == '-' || x == '*' || x == '/' || x == '^') {
    return 1;
  }
  else return 0;
}


int main() {
  stackType s1;
  int i=0;
  int a,b;
  char exp[MAX];

  Initialize(&s1);
  printf("Enter postfix expression: ");
  fgets(exp,MAX,stdin);
  //exp[strlen(exp)] = '\0';


  while ( exp[i] != '\0') {

    if ( isdigit(exp[i]) ) {
      push( &s1, exp[i] - '0');
    }

    else if ( checkOperator(exp[i]) == 1){
      a = pop(&s1);
      b = pop(&s1);
      if (exp[i] == '+') {
        push(&s1,a+b);
      }

      else if (exp[i] == '-') {
        push(&s1,b-a);
      }

      else if (exp[i] == '*') {
        push(&s1,a*b);
      }

      else if (exp[i] == '/') {
        push(&s1,b/a);
      }
    }
    i++;
  }

  printf("Result: %d\n\n",Top(&s1));

  return 0;
}
