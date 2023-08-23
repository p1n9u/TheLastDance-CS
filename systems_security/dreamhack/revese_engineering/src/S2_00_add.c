/*
 * Name: add.c
 * $ gcc -E add.c > add.i
 * $ gcc -S add.i -o add.S
 */

#include "S2_01_add.h"

#define HI 3

int add(int a, int b)
{
	return a + b + HI;
}