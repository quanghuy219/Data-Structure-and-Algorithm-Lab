#include<stdio.h>
#include<stdlib.h>

typedef struct db{
	char ten[20];
	char sdt[20];
}DB;

int main(int argc,char** argv)
{
	DB *p = (DB*)malloc(sizeof(DB));
	FILE *f = fopen(argv[1],"rb");
	while(!feof(f))
	{
		fread(p,1,sizeof(DB),f);
		printf("%s-%s\n",p->ten,p->sdt);
	}
	fclose(f);
	return 0;
}
