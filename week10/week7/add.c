#include "stacklib.h"

int addsameSize(stack_type *s1, stack_type *s2, stack_type *result, int length);
void addExtra(stack_type *result, stack_type *addFrom, int length, int extra);

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
		extra = addsameSize(s1, s2, result, strlen(b));
		addExtra(result, s1, length, extra);
	}
	else
	{
		extra = addsameSize(s1, s2, result, strlen(a));
		// printf("Extra = %d\n", extra);
		addExtra(result, s2, -length, extra);
	}

	printf("The combination of two numbers is: \n");
	while (n = pop(result))
		printf("%c\n", n);
}

//addition of two same-size array
int addsameSize(stack_type *s1, stack_type *s2, stack_type *result, int length) {
	char sub1, sub2;
	int extra = 0;
	char sum;
	int i;

	for (i = 0; i < length; ++i)
	{
		sub1 = pop(s1);
		sub2 = pop(s2);

		if (sub1 + sub2 + extra - '0' > '9') {	
			sum = sub1 + sub2 + extra - '0' - 9;
			extra = 1;
		}
		else
		{	
			sum = sub1 + sub2 - '0';
			extra = 0;
		}
		push(sum, result);
	}
	return extra;
}

//push the extra length of 1 stack addFrom to result
void addExtra(stack_type *result, stack_type *addFrom, int length, int extra) {
	int i;
	char n;
	for (i = 0; i < length; ++i)
	{
		n = pop(addFrom);
		n += extra;
		extra = 0;
		if (n > '9')
		{
			n -= 9;
			extra = 1;
		}
		push(n, result);
	}
}