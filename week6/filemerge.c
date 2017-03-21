#include<stdio.h>
#include<stdlib.h>

typedef struct db{
	char ten[20];
	char sdt[20];
}DB;

int main(int argc,char** argv)
{
	if(argv[3]==NULL)
	{
		printf("chua nhap du file!\n");
		return 0;
	}

	DB p[20];
	DB q[20];
	FILE *f1= fopen("phone1.dat","rb");
	FILE *f2= fopen("phone2.dat","rb");
	FILE *f3= fopen("phone3.dat","w+b");

	if(f1==NULL || f2 ==NULL)
	{
		printf("read data unsuccessfully!\n");
		return 0;
	}
	int i = 0, j = 0;
	while(fread(p,1,sizeof(DB),f1))
	{
		fwrite(p,1,sizeof(DB),f3);
		if(fread(q,1,sizeof(DB),f2))
			fwrite(q,1,sizeof(DB),f3);
		i++;
	}
	while(fread(q,1,sizeof(DB),f2))
	{
		fwrite(q,1,sizeof(DB),f3);
	}

	fclose(f1);
	fclose(f2);
	fclose(f3);
	return 0;
}
