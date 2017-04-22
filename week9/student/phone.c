#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

void MENU();
void readFILE(node** head , node** tail, node** cur , FILE* f);
void writeFILE(node *head);
int readPosition();
phone readNewPhone();
void search(node* head, node** cur);

int main(int argc, char *argv[])
{
    if(argc != 2){
		printf("There should be 3 arguments:\n");
		printf("1. Executed file.\n");
		printf("2. Iutput file (Binary file).\n");
		return 0;
	}

	char* file = argv[1];
	FILE* f;
	int n; //position
	int n1;
	int n2;
	
	
	if((f = fopen(file, "rb")) == NULL){
		printf("%s does not exist!\n", argv[1]);
		return 0;
	}
	
	node* head = NULL;
	node* tail = NULL;
	node* cur = NULL;
	
	node* head1 = NULL;
	node* tail1 = NULL;
	node* cur1 = NULL;
	
	node* head2 = NULL;
	node* tail2 = NULL;
	node* cur2 = NULL;
	int flag;

	
	int choice;
    do{
    	MENU();
		printf("\nChoice: ");
		scanf("%d", &choice);
		while(getchar() != '\n');
		
		switch (choice) {
		case 1:
			readFILE(&head, &tail, &cur, f);
			break;
			
		case 2:			
		    do{
				printf("\nDISPLAY THE LIST:\n");
				printf("1. FORWARD.\n");
				printf("2. BACKWARD.\n\n");
				printf("Choice: ");
				scanf("%d", &flag);
				getchar();
				if(flag != 1 && flag != 2)
					printf("INVALID VALUE!\nPLEASE RE-ENTER!\n\n");
				
			}while(flag != 1 && flag != 2);
			
			if(flag == 1)
				displayList(head);
			else
				displayReverseList(tail);
			printf("\n");
			break;
			
		case 3:
			insertAtEnd(&head, &tail, &cur, readNewPhone());
			printf("\nINSERTING SUCCESSFULLY!\n\n");
	    	break;

		case 4:			
			n = readPosition();
			insertAtPosition(&head, &tail, &cur, readNewPhone(), n);
			printf("\nINSERTING SUCCESSFULLY!\n\n");
	    	break;
			
		case 5:
			n = readPosition();
			deleteAtPosition(&head, &tail, &cur, n);
			printf("\nDELETING SUCCESSFULLY!\n\n");
			break;

		case 6:
			deleteNode(&head, &tail, &cur);
			if(cur != NULL)
				printf("\nDELETING SUCCESSFULLY!\n\n");
			else printf("\n");
				
			break;
			
		case 7:
			cur = head;
			deleteNode(&head, &tail, &cur);
			if(cur != NULL)
				printf("\nDELETING SUCCESSFULLY!\n\n");
			else printf("\n");
		
			break;
			
		case 8:
			cur = tail;
			deleteNode(&head, &tail, &cur);
			if(cur != NULL)
				printf("\nDELETING SUCCESSFULLY!\n\n");
			else printf("\n");
		
			break;

		case 9:
			search(head, &cur);
			break;

		case 10:
			
			do{
				printf("STARTING POINT: ");
				scanf("%d", &n1);
				
				printf("NUMBER OF ELEMENT(S): ");
				scanf("%d", &n2);
				while(getchar() != '\n');
				if(n1 < 0 || n2 <= 0)
					printf("Invalid value!\nPlease re-enter!\n\n");
			}while(n1 < 0 || n2 <= 0);
			
			split(head, &head1, &tail1, &cur1, &head2, &tail2, &cur2, n1, n2);
			
			printf("\nFILE 1:\n");
			writeFILE(head1);
			

			printf("FILE 2:\n");
			writeFILE(head2);
			
			break;

		case 11:
			reverseList(&head, &tail, &cur);
			printf("REVERSING SUCCESSFULLY!\n\n");
			break;

		case 12:
			writeFILE(head);
			break;

		case 13:
			break;
		default:
			printf("Invalid vallue!\n\n");
			break;
		}
	}while(choice != 13);

/*
	root = freeList(root, &cur);
	free(cur);*/
	fclose(f);
	
    return 0;
}

//functions:

void MENU(){
	printf("\tMENU:\n");
	printf("1.  IMPORT FROM BINARY FILE.\n");
	printf("2.  DISPLAY THE LIST.\n");
	printf("3.  ADD NEW PHONE.\n");
	printf("4.  INSERT AT POSITION.\n");
	printf("5.  DELETE AT POSITION.\n");
	printf("6.  DELETE CURRENT.\n");
	printf("7.  DELETE FIRST.\n");
	printf("8.  DETELE LAST.\n");
	printf("9.  SEARCH AND UPDATE.\n");
	printf("10. DIVIDE AND EXTRACT.\n");
	printf("11. REVERSE LIST.\n");
	printf("12. SAVE TO FILE.\n");
	printf("13. QUIT.\n");	
}

int readPosition(){
	int n;
	do{
		printf("POSITION: ");
		scanf("%d", &n);
		while(getchar() != '\n');
		if(n < 0)
					printf("INVALID VALUE FOR POSITION!\n\n");
	}while(n < 0);
	return n;
}

void readFILE(node** head, node** tail, node** cur, FILE* f){
	if(*head != NULL)
		freeList(head, tail, cur); //free the list if it already existed
	
	phone *phonearr = (phone*)malloc(sizeof(phone));
	fseek(f, 0, SEEK_SET);
	while(!feof(f)){		
		int num = fread(phonearr, sizeof(phone), 1, f);
		if(num == 1){
			insertAtEnd(head, tail, cur, phonearr[0]); //insert the element to the end of the list
		}
	}
	free(phonearr);	
	printf("IMPORT SUCCESSFULLY!\n\n");
}


void writeFILE(node *head){
	char s[256];
	printf("NAME OF THE FILE: ");
	scanf("%[^\n]", s);
	while(getchar() != '\n');

	FILE* f = fopen(s, "w+b");
	node* p;
	phone *phonearr = (phone*)malloc(sizeof(phone));
	for(p = head; p != NULL; p = p->next){
		
		strcpy(phonearr[0].model, p->info.model);
		phonearr[0].screensize = p->info.screensize;
		phonearr[0].memory = p->info.memory;
		phonearr[0].price = p->info.price;
		
		fwrite(phonearr, sizeof(phone), 1, f);
	}
	free(phonearr);
	printf("EXPORT SUCCESSFULLY!\n\n");
	fclose(f);
}


phone readNewPhone(){
	phone a;
	
	printf("MODEL: ");
	scanf("%[^\n]s", a.model);
	while(getchar() != '\n');

	do{
		printf("MEMORY: ");
		scanf("%d", &a.memory);
		while(getchar() != '\n');
		if(a.memory <= 0)
			printf("INVALID VALUE FOR MEMORY!\n\n");
	}while(a.memory <= 0);

	do{
		printf("SCREEN SIZE: ");
		scanf("%f", &a.screensize);
		while(getchar() != '\n');
		if(a.screensize <= 0)
			printf("INVALID VALUE FOR SCEEN SIZE!\n\n");
	}while(a.screensize <= 0);

	do{
		printf("PRICE: ");
		scanf("%d", &a.price);
		while(getchar() != '\n');
		if(a.price <= 0)
			printf("INVALID VALUE FOR PRICE!\n\n");
	}while(a.price <= 0);
	return a;
}


void search(node* head, node** cur){
	int flag = 0;
	char s[100];
	printf("Model: ");
	scanf("%[^\n]", s);	
	while(getchar() != '\n');
	node* p ;
	
	for(p = head; p != NULL; p = p->next)
		if(strcmp(p->info.model, s) == 0){
			flag = 1;
			break;
		}
    
	if (flag != 0){
		printf("\n%-20s%-15s%-25s%s\n\n","MODEL", "MEMORY (GB)", "SCREEN SIZE (INCHES)", "PRICE(VND)");

		for(p = head; p != NULL; p = p->next)
			if(strstr(p->info.model, s) != NULL){
				displayNode(p);
				*cur = p;
				break;
			}
		printf("\n");

		char c;
		do{
		printf("Do you want to update (Y/N): ");		
		scanf("%c", &c);
		while(getchar() != '\n');
		if(c != 'Y' && c != 'N')
			printf("\nInvalid value!\nPlease re-type!\n\n");
		}while(c != 'Y' && c != 'N');

		if(c == 'Y'){
			p->info = readNewPhone(); 
			printf("\nUPDATING SUCCESSFULLY!\n\n");
		}
		else
			printf("\n");
	}
	
	if(flag == 0)
		printf("Can not find the item!\n\n");
}

