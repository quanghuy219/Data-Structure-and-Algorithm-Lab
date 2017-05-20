#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 10

typedef struct {
  int key;
} element;

void quicksort(element list[], int left, int right){
  int pivot, i,j;
  element temp;
  if ( left < right ) {
    i = left;
    j = right+1;
    pivot = list[left].key;
    do
      {
	do i++; while(list[i].key < pivot);
	do j--; while(list[j].key > pivot);
	if (i<j){
	  temp = list[left];
	  list[left] = list[j];
	  list[j] = temp;
	}
      } while (i<j);

    quicksort(list,left,j-1);
    quicksort(list,j+1,right);
  }
}

int main()
{
  element list[MAX];
  srand(time(NULL));
  for (int i = 0; i < MAX; i++) {
    int a = rand() % 100;
    list[i].key = a;
    printf("%d\n",list[i].key);
  }

  printf("\n\n\n");
  
  quicksort(list,0,MAX-1);

  for (int i = 0; i < MAX; i++) {
    printf("%d\n",list[i].key);
  }
  
  return 0;
}
