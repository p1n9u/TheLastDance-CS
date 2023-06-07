#include <stdio.h>
#include <stdlib.h>

#include "dsl03_02_doubly_linked_list.h"

typedef int element;

typedef struct StackNode {
    element data;
    struct list_head list;
} StackNode;

StackNode *create_stack_node(element data)
{
    StackNode *ptr = (StackNode *)malloc(sizeof(StackNode));
    if (ptr == NULL) {
        printf("fail: create list by malloc\n");
    } else {
        ptr->data = data;
        return ptr;
    }
}
// static inline int list_is_first(const struct list_head *list, const struct list_head *head)
void display(struct list_head *top)
{
    if (list_empty(top)) {
        fprintf(stderr, "%s(): [ EMPTY STACK ]\n", __func__);
    	return;
    }

    struct list_head *pos;
    StackNode *entry;
    list_for_each(pos, top) {
        entry = list_entry(pos, StackNode, list);
        printf("[ %d ]", entry->data);;
        if(list_is_first(pos, top))
            printf(" ==> TOP");
        printf("\n");
    }
}

void push(struct list_head *top, element data)
{
    StackNode *new = create_stack_node(data);
    if (new != NULL) {
        list_add(&new->list, top);
        printf("item %d push\n", data);
    }
}

element peek(struct list_head *top)
{
    if (list_empty(top)) {
        fprintf(stderr, "%s(): underflow!\n", __func__);
    	return -1;
    }
    StackNode *p = list_entry(top->next, StackNode, list);
    return p->data;
}

element pop(struct list_head *top)
{
    if (list_empty(top)) {
        fprintf(stderr, "%s(): underflow!\n", __func__);
    	return -1;
    }
    StackNode *p = list_entry(top->next, StackNode, list);
    element res = p->data;
    list_del(top->next);
    free(p);
    return res;
}


int main(void)
{
    LIST_HEAD(top);

    int i;
    StackNode *ptr, *pos;

    for (i = 1; i <= 5; i++) {
        push(&top, i);
    }
    display(&top);

    printf("pop item %d\n", pop(&top));
    printf("pop item %d\n", pop(&top));
    display(&top);

    push(&top, 5);
    display(&top);

    printf("pop item %d\n", pop(&top));
    printf("pop item %d\n", pop(&top));
    printf("pop item %d\n", pop(&top));
    printf("pop item %d\n", pop(&top));
    printf("pop item %d\n", pop(&top));
    display(&top);

    return 0;
}
