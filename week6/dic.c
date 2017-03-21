#include<stdio.h>
#include<stdlib.h>

typedef struct dic{
	char tu[100];
	char nghia[100];
}DIC;

int main()
{
	FILE *f;
	DIC *p;
	if((f = fopen("dic.txt","r+b"))==0)
	{
		printf("can't open file!\n");
		return 0;
	}
	int n=0;
	char c[100];
	fgets(c,100,f);
	while(!feof(f))
	{
		n++;
		if(n==1)
		{
			p = (DIC*)malloc(54003*sizeof(DIC));
		}
	    
		fscanf(f,"%[^:]",p[n].tu); fscanf(f,"%c");
		fscanf(f,"%[^\n]",p[n].nghia); fscanf(f,"%c");
	}
	fclose(f);

	f = fopen("dic.dat","w+b");
	fwrite(p,sizeof(DIC),53800,f);
	fclose(f);

	f = fopen("dic.dat","rb");
	int begin,end;
	printf("nhap bat dau va ket thuc: ");
	scanf("%d %d",&begin,&end);

	fseek(f,begin*sizeof(DIC),SEEK_SET);

	fread(p,1,(end-begin)*sizeof(DIC),f);

	
	int i;
	for(i=1;i<=end-begin;i++)
	{
		printf("%s : %s\n",p[i].tu,p[i].nghia);
	}

	fclose(f);
	free(p);
	return 0;
}
