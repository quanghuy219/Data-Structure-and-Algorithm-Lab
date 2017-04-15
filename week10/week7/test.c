#include "stacklib.h"

void main() {
	char s[5] = "abcde";
	int i;
	stack_type *st;
	st = (stack_type *)malloc(sizeof(stack_type));
	if (st == NULL)
	{
		fprintf(stderr, "ERROR : Allocated memory failed !!\n");
		exit(1);
	}
	iniStack(st);
	for (i = 0; i < 5; ++i)
		push(s[i], st);
	for (i = 0; i < 5; ++i)
		printf("%c\n", pop(st));
}