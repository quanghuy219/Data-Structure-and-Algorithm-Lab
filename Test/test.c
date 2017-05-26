#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
	int code;
	char toy[30];
} Kid;

typedef struct {
	int app;
	char toy[30];
} Time;

typedef Kid eletype;


#include "tree.h"


void display(eletype val){
	printf("%d\t%s\n",val.code,val.toy);
}

Node_tr* buildBST(Node_tr* root){
	FILE *f1 = fopen("A.txt","r");
	if (f1 == NULL)
	{
		printf("Cannot read data\n");
		return NULL;
	}
	char buff[MAX];
	eletype tmp;
	tmp.code = 0;
	tmp.toy[0] = '\0';	
	int flag;

	while(fgets(buff,MAX,f1) != NULL){
		flag = sscanf(buff,"%d %s",&tmp.code,tmp.toy);
		if(flag != 2){
			if(tmp.code == 0) {
				printf("Code is missing. Reenter it: ");
				scanf("%d",&tmp.code);
			}
			printf("Code: %d\n", tmp.code);

			if (strlen(tmp.toy) == 0)
			{
				printf("Toy is missing. Reenter it: ");
				//while(getchar() != '\n');
				fgets(tmp.toy,MAX,stdin);
				if (tmp.toy[strlen(tmp.toy)-1] == '\n')
				{
					tmp.toy[strlen(tmp.toy)-1] = '\0';
				}
			}
			printf("Toy: %s\n", tmp.toy);
		}

		root = insertNode(tmp,root);
		tmp.code = 0;
		tmp.toy[0] = '\0';
	}
	fclose(f1);
	return root;
}

int buildList(eletype list[]){
	FILE* f1 = fopen("B.txt","r");
	int flag;
	if (f1 == NULL)
	{
		printf("Cannot read data\n");
		return 0;
	}
	char buff[MAX];
	int i = 0;
	while(fgets(buff,MAX,f1) != NULL){
		flag = sscanf(buff,"%d %s",&list[i].code,list[i].toy);
		if(flag != 2){
			if(list[i].code == 0) {
				printf("Code is missing. Reenter it: ");
				scanf("%d",&list[i].code);
			}
			printf("Code: %d\n", list[i].code);

			if (strlen(list[i].toy) == 0)
			{
				printf("Toy is missing. Reenter it: ");
				//while(getchar() != '\n');
				fgets(list[i].toy,MAX,stdin);
				if (list[i].toy[strlen(list[i].toy)-1] == '\n')
				{
					list[i].toy[strlen(list[i].toy)-1] = '\0';
				}
			}
			printf("Toy: %s\n", list[i].toy);
		}
		i++;
	}
	fclose(f1);
	return i;
}

Node_tr* find(eletype list[], Node_tr *root,int num){
	Node_tr* tmp = NULL;
	for (int i = 0; i < num; i++)
	{
		root = deleteNode(list[i],root);
	}
	return root;
}

Node_tr* Merge(eletype list[], Node_tr* root, int num){

	for (int i = 0; i < num; i++)
	{
		root = insertNode(list[i],root);
	}
	return root;
}

void descendDisplay(Node_tr *root){
	if (root != NULL)
	{
		descendDisplay(root->right);
		display(root->val);
		descendDisplay(root->left);
	}
}


int Count(Node_tr* root, char toy[]){
	if(root == NULL) return 0;

	if ( strcmp(root->val.toy,toy) == 0 )
	{
		return 1 + Count(root->left,toy) + Count(root -> right,toy);
	}

	else return Count(root -> left, toy) + Count(root -> right, toy);
}

int flag, list_count; 

void build(Node_tr *root, Time list[]){
	if (root == NULL) return;

		flag = 0;
		for (int i = 0; i < list_count; i++)
		{	
			if (strcmp(list[i].toy , root->val.toy) == 0) flag = 1;
		}

		if (flag == 0)
		{
			strcpy(list[list_count].toy, root -> val.toy);
			list_count++;
		}
	
	build(root->left,list);
	build(root->right,list);

}



int main()
{	
	flag = 0;
	list_count = 0;
	Node_tr *root = (Node_tr*)malloc(sizeof(Node_tr));
	root = NULL;
	eletype list[MAX];
	int numB;
	int choice;
	int c;
	char tmp[MAX];
	Time list1[MAX];

	while(1){
		printf("1. Read data from file A\n");
		printf("2. Read data from file B\n");
		printf("3. Search\n");
		printf("4. Combine\n");
		printf("5. List\n");
		printf("0. Exit\n");
		printf("Choose: \n");
		scanf("%d%*c",&choice);

		switch(choice){
			case 1: 
				root = buildBST(root);
				inorder(root);
				break;
			case 2:
				numB = buildList(list);
				printf("\n\n\n");
				for (int i = 0; i < numB; ++i)
				{
					display(list[i]);
				}
				break;
			case 3: 
				root = find(list,root,numB);
				inorder(root);
				break;

			case 4: 
					root = Merge(list,root,numB);
					descendDisplay(root);
					break;

			case 5:
				build(root,list1);
				printf("%-15s%s\n", "Toy","Number of kids");
				for (int i = 0; i < list_count; i++)
				{
					list1[i].app = Count(root,list1[i].toy);
					printf("%-15s%d\n", list[i].toy,list1[i].app);
				}
				break;

			case 0: 
				printf("Exit\n");
				return 0;	
		}
		printf("\n\n\n");
	}
	return 0;
}