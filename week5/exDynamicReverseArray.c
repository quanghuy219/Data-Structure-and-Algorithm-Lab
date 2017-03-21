#include <stdio.h>
#include <stdlib.h>

int main()
{
  int i, n , *p;
  int add;
  printf("How many numbers do you want to enter?\n");
  scanf("%d",&n);

  p = (int *)malloc(n * sizeof(int));
  if (p == NULL) {
    printf("Memory allocation failed!\n");
    return 1;
  }
  //Get numbers from user
  printf("Please enter numbers now: \n");
  for (i = 0; i < n; i++) {
    scanf("%d",&p[i]);
  }

  //Display in reverse order
  printf("Numbers in reverse order: \n");
  for (i = n-1; i >= 0; i--) {
    printf("%d",p[i]);
  }
  printf("\n");
  
  printf("How many numbers do you want to add?\n");
  scanf("%d",&add);


  p = (int *)realloc(p, (n+add) * sizeof(int) );
  if (p == NULL) {
    printf("Reallocation failed!\n");
    return 1;
  }

  //Add numbers to array
  printf("Add numbers to array: \n");
  for (i = n; i < n+add; i++) {
    scanf("%d",&p[i]);
  }
  
  //print new array
  for (i = n+add-1; i >= 0; i--) {
    printf("%d",p[i]);
  }
  printf("\n");


  //free space
  free(p);
  return 0;
}
