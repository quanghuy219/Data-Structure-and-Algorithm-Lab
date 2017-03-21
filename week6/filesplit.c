#include<stdio.h>
#include<stdlib.h>

typedef struct db{
	char ten[20];
	char sdt[20];
}DB;

int main(int argc,char** argv)
{
	if(argv[4]==NULL)
	{
		printf("ban chua nhap du thong so!\n");
		return 0;
	}

	FILE *f = fopen(argv[1],"rb");
	FILE *f1 = fopen(argv[3],"w+b");
	FILE *f2 = fopen(argv[4],"w+b");
	if(f==NULL) {
		printf("can't open %s!\n",argv[1]);
	}
	DB p[100];
	fread(p,atoi(argv[2]),sizeof(DB),f);
	fwrite(p,atoi(argv[2]),sizeof(DB),f1);
	fread(p,20-atoi(argv[2]),sizeof(DB),f);
	fwrite(p,20-atoi(argv[2]),sizeof(DB),f2);

	fclose(f);
	fclose(f1);
	fclose(f2);
	return 0;
}
