#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 13

//the phone book structure
typedef struct {
	char name[30];
	char tel[15];
	char email[30];
} phone_addr;

phone_addr *contact;
int result;

int getMenu(char sections[][40], int maxsection) {
	int choice;
	printf("\n");
	for (int i = 0; i < maxsection; ++i)
		printf("%2d. %s\n", i + 1, sections[i]);
	printf("Your choice: ");
	scanf("%d", &choice);
	printf("\n");
	return choice;
}

int import(FILE *f, int numLine) {
	int result;
	contact = (phone_addr *)malloc(numLine * sizeof(phone_addr));
	result = fread(contact, sizeof(phone_addr), numLine, f);
	rewind(f);
	printf("Import success!\n");
	return result;
	free(contact);
}

phone_addr typeHand() {
	phone_addr p;
	printf("Name: ");
	scanf("%[^\n]", p.name);
	while (getchar() != '\n');
	printf("Tel number: ");
	scanf("%[^\n]", p.tel);
	while (getchar() != '\n');
	printf("Email address: ");
	scanf("%[^\n]", p.email);
	return p;
}

void searchName() {
	char s[40];
	printf("\nSearch by name\n");
	printf("Type in the name\n");
	while (getchar() != '\n');
	scanf("%[^\n]", s);
	printf("\nSearch result: \n");
	for (int i = 0; i < result; ++i)
		if (strstr(contact[i].name, s) != NULL)
		{
			printf("Position number %d: ", i + 1);
			printf("%-30s\t%-15s\t%-30s\n", contact[i].name, contact[i].tel, contact[i].email);
		}
}