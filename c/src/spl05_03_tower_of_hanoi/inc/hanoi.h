#ifndef __HANOI_H__
#define __HANOI_H__

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

extern int cnt; /* count of the number of moves */

int get_n_from_user(void);
void move(int n, char a, char b, char c);

#endif