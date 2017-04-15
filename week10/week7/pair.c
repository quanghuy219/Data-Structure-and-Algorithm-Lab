#include "stacklib.h"

int matchLiteral(char x, char y);
int check(char s[], int length, stack_type *st);

void main() {
	char s[20];
	int i;
	stack_type *st;
	
	st = iniStack(st);
	printf("Type in a string of literal\n");
	scanf("%s", s);
	if(check(s, strlen(s), st))
		printf("The string is made from literal in pairs\n");
	else
		printf("The string is not made from literal in pairs\n");
}

//check if the string is totally made from pair
int check(char s[], int length, stack_type *st) {
	int i;
	char tem; // result of pop
	for (i = 0; i < length; ++i)
	{
		if (s[i] == '(' || s[i] == '[' || s[i] == '{')
			push(s[i], st);
		else if (s[i] == ')' || s[i] == ']' || s[i] == '}')
		{
			if (empty(st))
				return 0;
			else
			{
				tem = pop(st);
				if (!matchLiteral(tem, s[i]))
					return 0;
			}
		}
	}
	if(empty(st))
		return 1;
	return 0;
}

//check if the literal is in pair
int matchLiteral(char x, char y) {
	if (x == '(' && y == ')') return 1;
	if (x == '{' && y == '}') return 1;
	if (x == '[' && y == ']') return 1;
	return 0;
}