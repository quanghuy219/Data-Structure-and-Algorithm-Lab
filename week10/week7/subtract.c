#include "stacklib.h"

int subtractsameSize(stack_type *s1, stack_type *s2, stack_type *result, int length);
void subtractExtra(stack_type *result, stack_type *subtractFrom, int length, int extra);

void main() {
	int i;
	stack_type *s1, *s2, *result;
	char n;
	char a[10000], b[10000];
	int extra;
	int length;
	
	result = iniStack(result);
	s1 = iniStack(s1);
	s2 = iniStack(s2);

	printf("Insert two number\n");
	printf("a = ");
	scanf("%s", a);
	printf("b = ");
	while (getchar() != '\n');
	scanf("%s", b);

	length = strlen(a) - strlen(b);
	for (i = 0; i < strlen(a); ++i)
		push(a[i], s1);
	for (i = 0; i < strlen(b); ++i)
		push(b[i], s2);

	if (length > 0) {
		extra = subtractsameSize(s1, s2, result, strlen(b));
		subtractExtra(result, s1, length, extra);

		printf("a - b = \n");
		while (n = pop(result))
			printf("%c\n", n);

	}
	else if (strcmp(a, b) == 0)
		printf("a - b = 0\n");
	else
	{
		extra = subtractsameSize(s2, s1, result, strlen(a));
		// printf("Extra = %d\n", extra);
		subtractExtra(result, s2, -length, extra);

		printf("a - b = \n");
		printf("-\n");
		while (n = pop(result))
			printf("%c\n", n);
	}

}

//subtraction of two same-size array
int subtractsameSize(stack_type *s1, stack_type *s2, stack_type *result, int length) {
	char sub1, sub2;
	int extra = 0;
	char minus;// sub1 - sub2 = minus
	int i;

	for (i = 0; i < length; ++i)
	{
		sub1 = pop(s1);
		sub2 = pop(s2);

		if (sub1 - sub2 - extra < 0) {
			minus = sub1 - extra - sub2 + 10 + '0';
			extra = 1;
		}
		else
		{
			minus = sub1 - sub2 + '0';
			extra = 0;
		}
		push(minus, result);
	}
	return extra;
}

//push the extra length of 1 stack subtractFrom to result
void subtractExtra(stack_type *result, stack_type *subtractFrom, int length, int extra) {
	int i;
	char n;
	for (i = 0; i < length; ++i)
	{
		n = pop(subtractFrom);
		n -= extra;
		extra = 0;
		if (n < '0'){
			extra = 1;
			n += 10;
		}
		if (n != '0')
			push(n, result);
	}
}