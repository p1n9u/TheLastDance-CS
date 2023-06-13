// SPDX-License-Identifier: GPL-2.0-only

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "inc/bst.h"
#include "inc/linux_min_heap.h"

/*
 * Tree
 */
typedef int weight;

typedef struct TreeNode {
    BSTREE_ENTRY(TreeNode) entry;
    weight w;
} TreeNode;

TreeNode *make_tree(TreeNode *left, TreeNode *right)
{
    TreeNode *n = (TreeNode *)malloc(sizeof(TreeNode));
    if (n == NULL) {
        fprintf(stderr, "%s: create tree node by malloc\n", __func__);
    } else {
        BSTREE_LINK_LEFT(n, left, entry);
        BSTREE_LINK_RIGHT(n, right, entry);
    }
    return n;
}

void destroy_tree(TreeNode *root)
{
    if(root == NULL)
        return;
    destroy_tree(BSTREE_LEFT(root, entry));
    destroy_tree(BSTREE_RIGHT(root, entry));
    free(root);
}

void display_preorder(TreeNode *n)
{
    if(n) {
        printf("%d ", n->w);
        display_preorder(BSTREE_LEFT(n, entry));
        display_preorder(BSTREE_RIGHT(n, entry));
    }
}

/*
 * Heap
 */
typedef struct element {
    int key;
    TreeNode *ptree;
} element;


static bool less_than(const void *lhs, const void *rhs)
{
    const element *lp = lhs;
    const element *rp = rhs;
	return (lp->key) < (rp->key);
}

static void swap_elem(void *lhs, void *rhs)
{
    element temp = *(element *)lhs;

	*(element *)lhs = *(element *)rhs;
	*(element *)rhs = temp;
}


void huffman_tree(const int freq[], int n)
{
    element data[n];

    struct min_heap heap = {
		.data = data,
		.nr = 0,
		.size = n,
	};

	struct min_heap_callbacks funcs = {
		.elem_size = sizeof(element),
		.less = less_than,
		.swp = swap_elem,
	};

    TreeNode *node, *x;
    element e, e1, e2;
    
    int i;
    for (i = 0; i < n; i++) {
        node = make_tree(NULL, NULL);
        e.key = node->w = freq[i];
        e.ptree = node;
        min_heap_push(&heap, &e, &funcs);
    }

    element last;
    element *v = heap.data;

    for (i = 1; i < n; i++) {
        last = v[0];
        e1 = last;
	    min_heap_pop(&heap, &funcs);
        if (last.key > v[0].key)
            return;

        last = v[0];
        e2 = last;
	    min_heap_pop(&heap, &funcs);
        if (last.key > v[0].key)
            return;

        x = make_tree(e1.ptree, e2.ptree);
        e.key = x->w = e1.key + e2.key;
        e.ptree = x;

        min_heap_push(&heap, &e, &funcs);
    }

    last = v[0];
    display_preorder(last.ptree);
    printf("\n");

    destroy_tree(last.ptree);
}

int main(void)
{
    const int freq[] = { 15, 12, 8, 6, 4 };
    huffman_tree(freq, 5);
    return 0;
}

