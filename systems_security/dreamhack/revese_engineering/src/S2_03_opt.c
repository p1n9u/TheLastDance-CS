/*
 * Name: opt.c
 * Compile: gcc -o opt opt.c -O2
 */

#include <stdio.h>

int main(void)
{
	int x = 0;
	int i;
	for (i = 0; i < 100; i++)
		x += i;
	printf("%d", x);
	return 0;
}