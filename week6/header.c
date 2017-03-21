#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct head{
	int size;
	char name[20];
	char date[20];
}header;

void hea(char *file)
{
	FILE * f = fopen(file,"r+");

	if(f==NULL)
	{
		printf("can't read %s\n",file);
		return;
	}
	char c[20];
	header a;
	printf("input information of file:\n");
	printf("authorize name: ");
	scanf("%[^\n]%*c",c);
	strcpy(a.name,c);
	printf("date: ");
	scanf("%[^\n]%*c",c);
	strcpy(a.date,c);

	fseek(f,0,SEEK_END);
	int l = a.size = ftell(f);
	rewind(f);
	char p[10000];
	fread(p,1,10000,f);
//	printf("%s\n",p);

	rewind(f);
	fprintf(f,"size: %d\nauthorize name: %s\ndate: %s\n",a.size,a.name,a.date);
	fwrite(p,1,l,f);
	fclose(f);
}

void print(char *file)
{
	FILE *f = fopen(file,"rb");
	char p[100000];
	fread(p,1,10000,f);
	printf("%s\n",p);
	fclose(f);
}

int main(int argc, char ** argv)
{
	if(argv[1] ==NULL)
	{
		printf("you haven't input file name!\n");
		return 0;
	}
	hea(argv[1]);
	print(argv[1]);
	return 0;
}
