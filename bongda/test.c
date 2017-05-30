#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

typedef struct {
	char team[MAX];
	int pts;
} eletype;

#include "tree.h"


Node_tr* buildTree(FILE *fin, Node_tr *root){
	char buff[MAX];
	eletype team1;
	eletype team2;
	Node_tr* tmp;
	int goal1, goal2;
	while( fgets(buff,MAX,fin) != NULL){
		sscanf(buff,"%s %s %d %d ", team1.team, team2.team, &goal1, &goal2);
		if (goal1 > goal2)
		{
			team1.pts = 3;
			team2.pts = 0;
		}

		else if (goal1 < goal2){
			team1.pts = 0;
			team2.pts = 3;
		} 
		else {
			team1.pts = 1;
			team2.pts = 1;
		}

		if (Search(team1,root) == NULL)
		{
			root = insertNode(team1,root);
			printf("Number:%d\n", count(root));
			printf("Address: %p\n", Search(team1,root));
		}

		else {
			tmp = Search(team1,root);
			tmp -> val.pts += team1.pts;
		}

		if (Search(team2,root) == NULL)
		{
			root = insertNode(team2,root);
			printf("Number:%d\n", count(root));
			printf("Address: %p\n", Search(team2,root));
		}

		else {
			tmp = Search(team2,root);
			tmp -> val.pts += team2.pts;
		}
	}
	return root;
}

void Delegated(Node_tr* root, int x, int *count, eletype list[]){
	if (root != NULL)
	{
		if (root -> val.pts < x)
		{
			list[(*count)++] = root -> val;
		}

		Delegated(root -> left, x,count, list);
		Delegated(root -> right, x, count, list);
	}
}


void writeFile(Node_tr* root, FILE *fin){
	if (root != NULL)
	{
		fprintf(fin, "%s\t%d\n",root -> val.team, root -> val.pts);
		writeFile(root -> left, fin);
		writeFile(root -> right, fin);
	}
}




int main()
{
	FILE *f1 = fopen("bongda.txt","r");
	FILE *f2;
	if (f1 == NULL)
	{
		printf("Cannot read file data\n");
		return 0;
	}

	int choice;
	Node_tr* root = NULL;
	Node_tr* p;
	eletype list[MAX];
	int count = 0,x;
	eletype tmp;
	while(1){
		printf("1. Tao cay\n");
		printf("2. Ket qua\n");
		printf("3. Tim kiem\n");
		printf("4. Xuong hang\n");
		printf("5. Xuat file\n");
		printf("Chon: ");
		scanf("%d",&choice);
		while(getchar() != '\n');
		switch(choice){
			case 1:
				root = buildTree(f1,root);
				break;

			case 2:
				printf("%-10s%-10s\n","Team", "Points");
				inorder(root);
				break;

			case 3:
				printf("Enter a team: ");
				scanf("%s",tmp.team);
				p = Search(tmp,root);
				if (p == NULL)
				{
					printf("Khong co doi bong nay\n");
				}

				else {
					printf("%-10s%-10s\n","Team", "Points");
					display(p->val);
				}
				break;

			case 4:
				printf("Enter a point: ");
				scanf("%d",&x);

				Delegated(root,x,&count,list);
				printf("Doi bi xuong hang\n");
				printf("%-10s%-10s\n","Team", "Points");
				for (int i = 0; i < count; ++i)
				{
					printf("%-10s%d\n",list[i].team,list[i].pts);
					root = deleteNode(list[i],root);
				}

				printf("Nhung doi con lai\n");
				inorder(root);
				break;

			case 5: 
				f2 = fopen("Ketqua.txt","w+");
				if (f2 == NULL)
				{
					printf("Cannot open file\n");
					break;
				}
				writeFile(root,f2);
				fclose(f2);
				break;
			case 0: 
				printf("Exit\n\n\n");
				return 0;
		}
		printf("\n\n\n");
	}

	fclose(f1);

	return 0;
}