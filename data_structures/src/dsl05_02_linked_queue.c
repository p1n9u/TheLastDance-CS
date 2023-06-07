#include <stdio.h>
#include <stdlib.h>

#include "dsl03_02_doubly_linked_list.h"

typedef int element;

typedef struct QueueNode {
    element data;
    struct list_head list;
} QueueNode;

QueueNode *create_queue_node(element data)
{
    QueueNode *ptr = (QueueNode *)malloc(sizeof(QueueNode));
    if (ptr == NULL) {
        printf("fail: create queue node by malloc\n");
    } else {
        ptr->data = data;
        return ptr;
    }
}

void display(struct list_head *Q)
{
    if (list_empty(Q)) {
        fprintf(stderr, "%s(): [ EMPTY QUEUE ]\n", __func__);
    	return;
    }

    struct list_head *pos;
    QueueNode *entry;

    printf("<- FRONT ");
    printf("- ITEMS [ ");
    list_for_each(pos, Q) {
        entry = list_entry(pos, QueueNode, list);
        printf("%d ", entry->data);;
    }
    printf("] <- REAR\n");
}

void enqueue(struct list_head *Q, element data)
{
    QueueNode *new = create_queue_node(data);
    if (new != NULL) {
        list_add_tail(&new->list, Q);
        printf("item %d enqueue\n", data);
    }
}

element peek(struct list_head *Q)
{
    if (list_empty(Q)) {
        fprintf(stderr, "%s(): underflow!\n", __func__);
    	return -1;
    }
    QueueNode *p = list_entry(Q->next, QueueNode, list);
    return p->data;
}

element dequeue(struct list_head *Q)
{
    if (list_empty(Q)) {
        fprintf(stderr, "%s(): underflow!\n", __func__);
    	return -1;
    }
    QueueNode *p = list_entry(Q->next, QueueNode, list);
    element res = p->data;
    list_del(Q->next);
    free(p);
    return res;
}


int main(void)
{
    LIST_HEAD(queue);

    int i;
    
    for (i = 1; i <= 5; i++) {
        enqueue(&queue, i);
    }
    display(&queue);

    printf("dequeue item %d\n", dequeue(&queue));
    printf("dequeue item %d\n", dequeue(&queue));
    display(&queue);

    enqueue(&queue, 6);
    display(&queue);

    printf("dequeue item %d\n", dequeue(&queue));
    printf("dequeue item %d\n", dequeue(&queue));
    printf("dequeue item %d\n", dequeue(&queue));
    printf("dequeue item %d\n", dequeue(&queue));
    printf("dequeue item %d\n", dequeue(&queue));
    display(&queue);

    return 0;
}
