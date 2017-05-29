#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 100

#include "mystring.h"

void readFile(FILE *fin, char arr[][MAX], int *num){
	char buff[MAX];
	while(fgets(buff,MAX,fin) != NULL){
		Validate(buff);
		strcpy(arr[(*num)++],buff);
	}
}

int main()
{
	char name[MAX][MAX];
	int num;
	FILE *f1 = fopen("name.txt","r");

	readFile(f1,name,&num);
	fclose(f1);

	for (int i = 0; i < num; ++i)
	{
		printf("%s\n",name[i] );
	}

	for (int i = 0; i < num; i++)
	{
		for (int j = i+1; j < num; j++)
		{
			if (  strcmp( convertName(name[i]), convertName(name[j]) )  > 0  )
			{
				char tmp[MAX];
				strcpy(tmp,name[i]);
				strcpy(name[i], name[j]);
				strcpy(name[j],tmp);
			}
		}
	}
	printf("\n\n\n");
	for (int i = 0; i < num; ++i)
	{
		printf("%s\n",name[i] );
	}
	return 0;
}





