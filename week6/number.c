#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{

  int count = atoi(argv[1]);
  int *arr;
  int sum = 0;
  int i;

  arr = (int *)malloc(count * sizeof(int));

  if (argc != count + 2) {
    printf("Enter %d number(s)\n",count);
    return 1;
  }

  

  for (i = 0; i < count; i++) {
    arr[i] = atoi(argv[i+2]);
    sum += arr[i];
    printf("%d\t",arr[i]);
  }
  printf("sum = %d\n",sum);

  FILE* fp1;

  fp1 = fopen("out.txt","a");
  if (fp1 == NULL) {
    printf("Cannot open file\n");
    return 1;
  }

  for (i = count-1; i >= 0; i--) {
    fprintf(fp1,"%d   ",arr[i]);
  }
  fprintf(fp1, "%d\n",sum);

  free(arr);
  fclose(fp1);
  
  
  return 0;
}
