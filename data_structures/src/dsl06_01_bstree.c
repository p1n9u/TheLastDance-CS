#include <stdio.h>
#include <stdlib.h>

#include "inc/bst.h"

typedef int element;

typedef struct TreeNode {
    BSTREE_ENTRY(TreeNode) entry;
    element data;
} TreeNode;

int element_cmp(TreeNode *e1, TreeNode *e2)
{
    if (e1->data == e2->data)
        return 0;
    else if (e1->data < e2->data)
        return -1;
    else
        return 1;
}

void element_swap(TreeNode *e1, TreeNode *e2)
{
    element tmp;
    tmp = e1->data;
    e1->data = e2->data;
    e2->data = tmp;
}

void display_preorder(TreeNode *n)
{
    if(n) {
        printf("%d ", n->data);
        display_preorder(BSTREE_LEFT(n, entry));
        display_preorder(BSTREE_RIGHT(n, entry));
    }
}

void display_inorder(TreeNode *n)
{
    if(n) {
        display_inorder(BSTREE_LEFT(n, entry));
        printf("%d ", n->data);
        display_inorder(BSTREE_RIGHT(n, entry));
    }
}

void display_postorder(TreeNode *n)
{
    if(n) {
        display_postorder(BSTREE_LEFT(n, entry));
        printf("%d ", n->data);
        display_postorder(BSTREE_RIGHT(n, entry));
    }
}

BSTREE_HEAD(bst, TreeNode) head = BSTREE_INITIALIZER(&head);
BSTREE_GENERATE(bst, TreeNode, entry, element_cmp, element_swap)

void insert_node_by_value(element data)
{
    TreeNode *tmp = (TreeNode *)malloc(sizeof(TreeNode));
    if (tmp == NULL) {
        fprintf(stderr, "%s: create tree node by malloc\n", __func__);
    } else {
        tmp->data = data;
        BSTREE_INSERT(bst, &head, tmp);
    }
}

element remove_node_by_value(element data)
{
    element res;
    TreeNode *key = (TreeNode *)malloc(sizeof(TreeNode));
    TreeNode *tmp = (TreeNode *)malloc(sizeof(TreeNode));
    if (key == NULL) {
        fprintf(stderr, "%s: create tree node by malloc\n", __func__);
    } else {
        key->data = data;
        tmp = BSTREE_REMOVE(bst, &head, key);
        if (tmp != NULL)
            res = tmp->data;
    }
    return res;
}

int main(void)
{
    element test_data[] = { 41, 20, 72, 11, 29, 51, 91, 32, 45, 90, 99 };
    int len = sizeof(test_data) / sizeof(element);
    
    int i;
    for (i = 0; i < len; i++)
        insert_node_by_value(test_data[i]);

    printf("Preorder: ");
    display_preorder(BSTREE_ROOT(&head));
    printf("\n");

    printf("Inorder: ");
    display_inorder(BSTREE_ROOT(&head));
    printf("\n");

    printf("Postorder: ");
    display_postorder(BSTREE_ROOT(&head));
    printf("\n");

    printf("remove item %d\n", remove_node_by_value(50));

    printf("remove item %d\n", remove_node_by_value(20));
    printf("Preorder: ");
    display_preorder(BSTREE_ROOT(&head));
    printf("\n");

    printf("remove item %d\n", remove_node_by_value(51));
    printf("Preorder: ");
    display_preorder(BSTREE_ROOT(&head));
    printf("\n");

    printf("remove item %d\n", remove_node_by_value(11));
    printf("Preorder: ");
    display_preorder(BSTREE_ROOT(&head));
    printf("\n");

    return 0;
}