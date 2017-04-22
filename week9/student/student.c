#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

void MENU();
void SUBMENU();
void readFile(node** head1, node** tail1, node** cur1, node** head2, node** tail2, node** cur2, FILE* f);
student readStudent();
int checkID(node* head1, node* head2, student a);
void moveStudent(node** head1, node** tail1, node** cur1, node** head2, node** tail2, node** cur2);
void appendList(node** head1, node** tail1, node** cur1, node** head2, node** tail2, node** cur2);
void appendList_Sort(node** head1, node** tail1, node** cur1, node** head2, node** tail2, node** cur2);



int main(int argc, char *argv[])
{
    if(argc != 2){
		printf("There should be 2 arguments:\n");
		printf("1. Executed file.\n");
		printf("2. Input binary file.\n");
		return 0;
	}

	char* file = argv[1];
	FILE* f;
	if((f = fopen(file, "rb")) == NULL){
		printf("%s does not exist!\n", argv[1]);
		return 0;
	}

	node* head1 = NULL;
	node* tail1 = NULL;
	node* cur1 = NULL;

	node* head2 = NULL;
	node* tail2 = NULL;
	node* cur2 = NULL;

	int choice;
	int subchoice;
	student a;
	
	do{
		MENU();
		printf("Choice: ");
		scanf("%d", &choice);
		getchar();

		switch (choice){
		case 1:
			readFile(&head1, &tail1, &cur1, &head2, &tail2, &cur2, f);
			break;

		case 2:
			do{
				SUBMENU();				
				printf("Choice: ");
				scanf("%d", &subchoice);
				getchar();

				switch (subchoice) {
				case 1: 
					displayList(head1);
					printf("\n");
					break;

				case 2:					
					displayList(head2);
					printf("\n");
					break;

				case 3:
					break;
					
				default:
					printf("Invalid value!\n\n");
					break;
				}
				
			}while(subchoice != 3);
			
			break;

		case 3:
			do{
				a = readStudent();
				if(!checkID(head1, head2, a)){
					printf("\nError: Student ID already existed! Please re-enter!\n\n");
				}
			}while(!checkID(head1, head2, a));

			if(a.grade > 8)
				insertAtEnd(&head1, &tail1, &cur1, a);
			else
				insertAtEnd(&head2, &tail2, &cur2, a);
			
			printf("INSERTING SUCCESSFULLY!\n\n");
				
			break;

		case 4:
			moveStudent(&head1, &tail1, &cur1, &head2, &tail2, &cur2);
			break;

		case 5:
			appendList(&head1, &tail1, &cur1, &head2, &tail2, &cur2);
			break;

		case 6:
			appendList_Sort(&head1, &tail1, &cur1, &head2, &tail2, &cur2);
			break;

		case 7:
			break;
		default:
			printf("Invalid value!\n\n");
			break;
				
		}
	}while(choice != 7);
	
	freeList(&head1, &tail1, &cur1);	
	freeList(&head2, &tail2, &cur2);
	fclose(f);
    return 0;
}

void MENU(){
	printf("\tMENU\n\n");
	printf("1. INITIATE 2 LISTS.\n");
	printf("2. DISPLAY THE LIST.\n");
	printf("3. ADD NEW STUDENT.\n");
	printf("4. MOVE STUDENT.\n");
	printf("5. CONCATENATE.\n");
	printf("6. CONCATENATE AND SORT.\n");
	printf("7. EXIT.\n\n");
}

void SUBMENU(){
	printf("\nDISPLAY LIST:\n");
	printf("1. LIST 1.\n");
	printf("2. LIST 2.\n");
	printf("3. BACK TO MAIN MENU.\n\n");
}

void readFile(node** head1, node** tail1, node** cur1, node** head2, node** tail2, node** cur2, FILE* f){
	if(*head1 != NULL)
		freeList(head1, tail1, cur1);
	if(*head2 != NULL)
		freeList(head2, tail2, cur2);
	fseek(f, 0, SEEK_SET);
	student* studentarr = (student*)malloc(sizeof(student));
	int num;
	while(!feof(f)){
		num = fread(studentarr, sizeof(student), 1, f);
		if(num == 1){
			if(studentarr[0].grade > 8)
				insertAtEnd(head1, tail1, cur1, studentarr[0]);
			else
				insertAtEnd(head2, tail2, cur2, studentarr[0]);
		}
	}
	free(studentarr);
	printf("IMPORTING SUCCESSFULLY!\n\n");
}

student readStudent(){
	student a;
	
	printf("\nSTUDENT:\n");
	do{
		printf("ID: ");
		scanf("%[^\n]s", a.id);
		while(getchar() != '\n');
		
		if(strlen(a.id) > 8)
			printf("Invalid value!\nPlease re-enter!\n\n");    
		
	}while(strlen(a.id) > 8);
	
	printf("NAME: ");
	scanf("%[^\n]s", a.name);
	while(getchar() != '\n');

	do{
	printf("GRADE: ");		
	scanf("%f", &a.grade);
	while(getchar() != '\n');

	if(a.grade < 0 || a.grade > 10)
		printf("Invalid value!\nPlease re-enter!\n\n");
	
	}while(a.grade < 0 || a.grade > 10);

	return a;
}

int checkID(node* head1, node* head2, student a){
    for(node* p = head1; p != NULL; p = p->next)
		if(strcmp(p->info.id, a.id) == 0)
			return 0;

	for(node* p = head2; p != NULL; p = p->next)
		if(strcmp(p->info.id, a.id) == 0)
			return 0;

	return 1;
}


void moveStudent(node** head1, node** tail1, node** cur1, node** head2, node** tail2, node** cur2){
	for(*cur2 = *head2; *cur2 != NULL; *cur2 = (*cur2)->next){
		while(*cur2 != NULL && (*cur2)->info.grade == 7.5){
			insertAtEnd(head1, tail1, cur1, (*cur2)->info);
			deleteNode(head2, tail2, cur2);
		}
	}
	printf("MOVING SUCCESSFULLY!\n\n");
}

void appendList(node** head1, node** tail1, node** cur1, node** head2, node** tail2, node** cur2){
	if(*head2 == NULL){
		printf("APPENDING SUCCESSFULLY!\n\n");
		return;
	}

	node* head = NULL;
	node* tail = NULL;
	node* cur = NULL;
//copy list 2 to another list
	for(node* p = *head2; p != NULL; p = p->next){
		insertAtEnd(&head, &tail, &cur, p->info);
	}
	
	if(*head1 == NULL){
		*head1 = head;
		*tail1 = tail;
		*cur1 = cur;
		printf("APPENDING SUCCESSFULLY!\n\n");
		return;
	}

	
	(*tail1)->next = head;
	head->prev = *tail1;
	*tail1 = tail;
	
	printf("APPENDING SUCCESSFULLY!\n\n");    
}

void appendList_Sort(node** head1, node** tail1, node** cur1, node** head2, node** tail2, node** cur2){
	appendList(head1, tail1, cur1, head2, tail2, cur2);
	char id_temp[ID_LENGTH];
	char name_temp[NAME_LENGTH];
	float grade_temp;
	
	for(node* p = *head1; p!= NULL; p = p->next){
		for(node* ptr = p->next; ptr != NULL; ptr=ptr->next){
			if(p->info.grade < ptr->info.grade){
				strcpy(id_temp, p->info.id);
				strcpy(name_temp, p->info.name);
				grade_temp = p->info.grade;

				strcpy(p->info.id, ptr->info.id);
				strcpy(p->info.name, ptr->info.name);
				p->info.grade = ptr->info.grade;

				strcpy(ptr->info.id, id_temp);
				strcpy(ptr->info.name, name_temp);
				ptr->info.grade = grade_temp;
			}
		}
	}

	
}
