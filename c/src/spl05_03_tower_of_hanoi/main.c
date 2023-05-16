#include "./inc/hanoi.h"

int cnt = 0;

int main(void)
{
    int n;
    n = get_n_from_user();
    assert(n > 0);
    /**
     * Move n disks from tower A to tower C,
     * using tower B as an intermediate tower.
     */
    move(n, 'A', 'B', 'C');

    return 0;
}