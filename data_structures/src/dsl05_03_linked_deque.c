#include <stdio.h>
#include <stdlib.h>

#include "inc/linux_list.h"

typedef int element;

typedef struct DequeNode {
    element data;
    struct list_head list;
} DequeNode;

DequeNode *create_deque_node(element data)
{
    DequeNode *ptr = (DequeNode *)malloc(sizeof(DequeNode));
    if (ptr == NULL) {
        printf("fail: create deque node by malloc\n");
    } else {
        ptr->data = data;
        return ptr;
    }
}

void display(struct list_head *DQ)
{
    if (list_empty(DQ)) {
        fprintf(stderr, "%s(): [ EMPTY DEQUE ]\n", __func__);
    	return;
    }

    struct list_head *pos;
    DequeNode *entry;

    printf("<- FRONT ");
    printf("- ITEMS [ ");
    list_for_each(pos, DQ) {
        entry = list_entry(pos, DequeNode, list);
        printf("%d ", entry->data);;
    }
    printf("] - REAR ->\n");
}

void add_front(struct list_head *DQ, element data)
{
    DequeNode *new = create_deque_node(data);
    if (new != NULL) {
        list_add(&new->list, DQ);
        printf("item %d add front\n", data);
    }
}

void add_rear(struct list_head *DQ, element data)
{
    DequeNode *new = create_deque_node(data);
    if (new != NULL) {
        list_add_tail(&new->list, DQ);
        printf("item %d add rear\n", data);
    }
}

element get_front(struct list_head *DQ)
{
    if (list_empty(DQ)) {
        fprintf(stderr, "%s(): underflow!\n", __func__);
    	return -1;
    }
    DequeNode *p = list_entry(DQ->next, DequeNode, list);
    return p->data;
}

element get_rear(struct list_head *DQ)
{
    if (list_empty(DQ)) {
        fprintf(stderr, "%s(): underflow!\n", __func__);
    	return -1;
    }
    DequeNode *p = list_entry(DQ->prev, DequeNode, list);
    return p->data;
}

element delete_front(struct list_head *DQ)
{
    if (list_empty(DQ)) {
        fprintf(stderr, "%s(): underflow!\n", __func__);
    	return -1;
    }
    DequeNode *p = list_entry(DQ->next, DequeNode, list);
    element res = p->data;
    list_del(DQ->next);
    free(p);
    return res;
}

element delete_rear(struct list_head *DQ)
{
    if (list_empty(DQ)) {
        fprintf(stderr, "%s(): underflow!\n", __func__);
    	return -1;
    }
    DequeNode *p = list_entry(DQ->prev, DequeNode, list);
    element res = p->data;
    list_del(DQ->prev);
    free(p);
    return res;
}

int main(void)
{
    LIST_HEAD(deque);

    add_front(&deque, 1);
    add_front(&deque, 2);
    add_front(&deque, 3);

    add_rear(&deque, 4);
    add_rear(&deque, 5);
    add_rear(&deque, 6);

    display(&deque);

    printf("delete_front item %d\n", delete_front(&deque));
    printf("delete_rear item %d\n", delete_rear(&deque));
    display(&deque);

    printf("delete_front item %d\n", delete_front(&deque));
    printf("delete_rear item %d\n", delete_rear(&deque));
    display(&deque);

    printf("delete_front item %d\n", delete_front(&deque));
    printf("delete_front item %d\n", delete_front(&deque));
    display(&deque);

    printf("delete_front item %d\n", delete_front(&deque));

    return 0;
}
