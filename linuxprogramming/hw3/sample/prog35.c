#include <stdio.h>
int main()
{
	char *p = "Hello";
	char m[] = "World";
	printf("%s %s\n", p, m);
	p = m;
	printf("%s\n", p);
	while (*p)
		putchar(*p++);
	printf("\n");
}
