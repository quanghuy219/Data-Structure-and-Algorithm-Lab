#include "stacklib.h"

int getMenu(char sections[][100], int maxsection);
void detoBinary(int n, stack_type *s);
void detoHex(int n, stack_type * s);

int main() {
////////////////////////////////////////////////////initialize stack
	int n;
	int choice;
	char sections[3][100] = {"Convert the decimal number into binary form",
	                         "Convert the decimal number into hexadecimal form", "Exit"
	                        };
	stack_type *s;
	s = iniStack(s);
///////////////////////////////////////////////////Menu
	do {
		choice = getMenu(sections, 3);
		switch (choice) {
		case 1:
			printf("Type in a decimal number n: ");
			scanf("%d", &n);
			detoBinary(n, s);
			break;
		case 2:
			printf("Type in a decimal number n: ");
			scanf("%d", &n);
			detoHex(n, s);
			break;
		case 3:
			break;
		default: printf("Invalid choice. It must be from 1 to %d\n", 3);
			break;
		}
	} while (choice != 3);
	return 0;
}

int getMenu(char sections[][100], int maxsection) {
	int choice;
	printf("\n");
	for (int i = 0; i < maxsection; ++i)
		printf("%2d. %s\n", i + 1, sections[i]);
	printf("Your choice: ");
	scanf("%d", &choice);
	printf("\n");
	return choice;
}
//////////////////////////////////////////////////convert from decimal to binary
void detoBinary(int n, stack_type * s) {
	char mod;
	char result;
	int first = n;
	while (n != 0)
	{
		mod = n % 2 == 1 ? '1' : '0';
		n = n / 2;
		push(mod, s);
	}
	printf("The number %d in binary is: \n", first);
	while (!(empty(s)))
	{
		result = pop(s);
		printf("%c\n", result);
	}
}

//////////////////////////////////////////////////convert from decimal to hex
void detoHex(int n, stack_type * s) {
	char mod;
	char result;
	int tem; // tem = n%16
	int first = n;
	while (n != 0)
	{
		tem = n % 16;
		switch (tem) {
		case 15: mod = 'F'; break;
		case 14: mod = 'E'; break;
		case 13: mod = 'D'; break;
		case 12: mod = 'C'; break;
		case 11: mod = 'B'; break;
		case 10: mod = 'A'; break;
		default: mod = tem + '0'; break;
		}
		n = n / 16;
		push(mod, s);
	}
	printf("The number %d in hexadecimal is: \n", first);
	while (!(empty(s)))
	{	
		result = pop(s) ;
		printf("%c\n", result);
	}
}
