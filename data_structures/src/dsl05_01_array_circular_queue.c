#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 10

typedef int element;

typedef struct {
    element queue[MAX_QUEUE_SIZE];
    int front, rear;
} ArrayCircularQueueType;

void init(ArrayCircularQueueType *Q)
{
    Q->front = Q->rear = 0;
}

ArrayCircularQueueType *create_queue()
{
    ArrayCircularQueueType *tmp = (ArrayCircularQueueType *)malloc(sizeof(ArrayCircularQueueType));
    if (tmp == NULL) {
        printf("fail: create queue by malloc\n");
    } else {
        init(tmp);
        return tmp;
    }
}

int is_empty(ArrayCircularQueueType *Q)
{
    return (Q->front == Q->rear);
}

int is_full(ArrayCircularQueueType *Q)
{
    return ((Q->rear+1) % MAX_QUEUE_SIZE == Q->front);
}

void display(ArrayCircularQueueType *Q)
{
    if (is_empty(Q)) {
        fprintf(stderr, "%s(): [ EMPTY QUEUE ]\n", __func__);
    	return;
    } else {
        int i;
        printf("<- FRONT[%d] ", Q->front);
        printf("- ITEMS [ ");
        for (i = (Q->front + 1) % MAX_QUEUE_SIZE; i != (Q->rear + 1) % MAX_QUEUE_SIZE; i = (i + 1) % MAX_QUEUE_SIZE)
            printf("%d ", Q->queue[i]);
        printf("] <- REAR[%d]\n", Q->rear);
    }

}

void enqueue(ArrayCircularQueueType *Q, element item)
{
    if (is_full(Q)) {
        fprintf(stderr, "%s(): overflow!\n", __func__);
        return;
    } else {
        Q->rear = (Q->rear+1) % MAX_QUEUE_SIZE;
        Q->queue[Q->rear] = item;
        return;
    }
}

element dequeue(ArrayCircularQueueType *Q)
{
    if (is_empty(Q)) {
        fprintf(stderr, "%s(): underflow!\n", __func__);
        return -1;
    } else {
        Q->front = (Q->front+1) % MAX_QUEUE_SIZE;
        return Q->queue[Q->front];
    }
}

element peek(ArrayCircularQueueType *Q)
{
    if (is_empty(Q)) {
        fprintf(stderr, "%s(): underflow!\n", __func__);
        return -1;
    } else {
        return (Q->queue[(Q->front+1) % MAX_QUEUE_SIZE]);
    }
}


int main(void)
{
    ArrayCircularQueueType *Q = create_queue();
    printf("is empty test: [%d]\n", is_empty(Q));
    
    int i;
    for (i = 0; i < 10; i++)
        enqueue(Q, i);
    display(Q);
    printf("is empty test: [%d]\n", is_empty(Q));

    dequeue(Q);
    display(Q);

    for (i = 10; i < 19; i++) {
        enqueue(Q, i);
        dequeue(Q);
        display(Q);
    }
    
    for (i = 0; i < 8; i++) {
        dequeue(Q);
        display(Q);
    }
    
    dequeue(Q);

    return 0;
}