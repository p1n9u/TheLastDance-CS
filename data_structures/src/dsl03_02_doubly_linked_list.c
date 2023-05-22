#include <stdio.h>
#include <stdlib.h>

#include "dsl03_02_doubly_linked_list.h"

typedef int element;

typedef struct ListNode {
    element data;
    struct list_head list;
} ListNode;

ListNode *create_list_node(element data)
{
    ListNode *ptr = (ListNode *)malloc(sizeof(ListNode));
    if (ptr == NULL) {
        printf("fail: create list by malloc\n");
    } else {
        ptr->data = data;
        return ptr;
    }
}

int main(void)
{
    LIST_HEAD(head);

    int i;
    ListNode *ptr, *pos;

    for (i = 1; i <= 5; i++) {
        ptr = create_list_node(i);
        list_add_tail(&ptr->list, &head);
    }

    printf("list: [ ");
    list_for_each_entry(pos, &head, list) {
		printf("%d ", pos->data);
	}
    printf("]\n");

    if (list_empty(&head)) {
        printf("List is Empty\n");
    	return -1;
    }

    printf("REMOVE: list\n");
    struct list_head *cur, *n;
    list_for_each_safe(cur, n, &head) {
		ptr = list_entry(cur, ListNode, list);
		printf("Removing list element: %d\n", ptr->data);
		list_del(cur);
		free(ptr);
	}

    if (list_empty(&head)) {
        printf("List is Empty\n");
    	return 0;
    }
    
	return 0;
}