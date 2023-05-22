#include <stdio.h>
#include <stdlib.h>

#define MAX_LIST_SIZE 10

typedef int element;

typedef struct {
    element list[MAX_LIST_SIZE];
    int len;
} ArrayListType;

void init(ArrayListType *L)
{
    L->len = 0;
}

ArrayListType *create_list()
{
    ArrayListType *tmp = (ArrayListType *)malloc(sizeof(ArrayListType));
    if (tmp == NULL) {
        printf("fail: create list by malloc\n");
    } else {
        init(tmp);
        return tmp;
    }
}

int is_empty(ArrayListType *L)
{
    return L->len == 0;
}

int is_full(ArrayListType *L)
{
    return L->len == MAX_LIST_SIZE;
}

void add(ArrayListType *L, int pos, element item)
{
    if (!is_full(L) &&
        (pos >= 0) &&
        (pos <= L->len)) {
            int i;
            for (i = (L->len-1); i >= pos; i--)
                L->list[i+1] = L->list[i];
            L->list[pos] = item;
            L->len++;
    } else {
        printf("fail: add\n");
    }
}

void add_last(ArrayListType *L, element item)
{
    add(L, L->len, item);
}

void add_first(ArrayListType *L, element item)
{
    add(L, 0, item);
}

element delete(ArrayListType *L, int pos)
{
    int i;
    element item;

    if (pos < 0 || pos >= L->len) {
        printf("fail: delete by pos\n");
        return -1;
    }

    item = L->list[pos];

    for (i = pos; i < (L->len-1); i++)
        L->list[i] = L->list[i+1];
    L->len--;

    return item;
}

void clear(ArrayListType *L)
{
    L->len = 0;
}

void replace(ArrayListType *L, int pos, element item)
{
    if (!is_empty(L) &&
        (pos >= 0) && 
        (pos < L->len))
        L->list[pos] = item;
    else
        printf("fail: replace\n");
}

int is_in_list(ArrayListType *L, element item)
{
    int i;
    if (!is_empty(L))
        for (i = 0; i < L->len; i++)
            if (L->list[i] == item)
                return 1;
    return 0;
}

element get_entry(ArrayListType *L, int pos)
{
    if (!is_empty(L) &&
        (pos >= 0) && 
        (pos < L->len))
        return L->list[pos];
    printf("fail: get entry\n");
    return -1;
}

int get_length(ArrayListType *L)
{
    return L->len;
}

int display(ArrayListType *L)
{
    int i;
    if (!is_empty(L)) {
        printf("[ ");
        for (i = 0; i < L->len; i++)
            /*
             * depend on element
             */
            printf("%d ", L->list[i]);
        printf("]\n");
    } else {
        printf("fail: display list by empty\n");
    }
}

int main(void)
{
    ArrayListType *L = create_list();
    printf("is empty test: [%d]\n", is_empty(L));
    add_last(L, 0);
    add_last(L, 1);
    add_last(L, 2);
    add_last(L, 3);
    display(L);
    printf("is empty test: [%d]\n", is_empty(L));
    printf("is in list test: [%d]\n", is_in_list(L, 0));
    printf("is in list test: [%d]\n", is_in_list(L, 5));
    printf("get length test: [%d]\n", get_length(L));
    printf("get entry(0) test: [%d]\n", get_entry(L, 0));

    add_first(L, 4);
    display(L);
    replace(L, 1, 5);
    display(L);
    add_last(L, 10);
    add_last(L, 10);
    add_last(L, 10);
    add_last(L, 10);
    add_last(L, 10);
    add_last(L, 10);
    display(L);
    delete(L, 4);
    display(L);

    return 0;
}