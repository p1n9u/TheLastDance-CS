// SPDX-License-Identifier: BSD-3-Clause
/*
 * Copyright (c) 2023 p1n9u <cybrphntm4@hanyang.ac.kr>
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef __BSTREE_H__
#define __BSTREE_H__

#define BSTREE_HEAD(name, type)			\
struct name {							\
	struct type *root;					\
}

#define BSTREE_INITIALIZER(ptr)			\
	{ NULL }

#define BSTREE_INIT(ptr) do {			\
	(ptr)->root = NULL;					\
} while (0)

#define BSTREE_ENTRY(type)				\
struct {								\
	struct type *left;					\
	struct type *right;					\
}

#define BSTREE_LEFT(elm, field)       (elm)->field.left
#define BSTREE_RIGHT(elm, field)      (elm)->field.right
#define BSTREE_ROOT(head)             (head)->root
#define BSTREE_EMPTY(head)            (BSTREE_ROOT(head) == NULL)

#define BSTREE_LINK_LEFT(parent, child, field) do {			\
	BSTREE_LEFT(parent, field) = child;						\
} while (0)

#define BSTREE_LINK_RIGHT(parent, child, field) do {		\
	BSTREE_RIGHT(parent, field) = child;					\
} while (0)


/**
 * @name: BSTREE_HAED(args), arg name identifier
 * @type: BSTREE_HAED(args), arg type identifier
 * @field: BSTREE_ENTRY(type) declaration identifier
 * @cmp: user defined compare function
 * @swap: user defined element swap function for remove
 * 
 * @head: tree head, BSTREE_HEAD
 * @elm: tree node
 */
#define BSTREE_GENERATE(name, type, field, cmp, swap)						\
struct type *																\
name##_BSTREE_SEARCH(struct name *head, struct type *elm)					\
{																			\
	struct type *node;														\
	node = BSTREE_ROOT(head);												\
																			\
	int __comp;																\
	while (node != NULL) {													\
		__comp = (cmp)(elm, node);											\
		if (__comp == 0)													\
			return node;													\
		if (__comp < 0)														\
			node = BSTREE_LEFT(node, field);								\
		else																\
			node = BSTREE_RIGHT(node, field);								\
	}																		\
	return (NULL);															\
}																			\
																			\
void																		\
name##_BSTREE_INSERT(struct name *head, struct type *elm)					\
{																			\
	struct type *p, *t;														\
	t = BSTREE_ROOT(head);													\
	p = NULL;																\
																			\
	int __comp;																\
	while (t != NULL) {														\
		__comp = (cmp)(elm, t);												\
		if (__comp == 0)													\
			break;															\
		p = t;																\
		if (__comp < 0)														\
			t = BSTREE_LEFT(p, field);										\
		else																\
			t = BSTREE_RIGHT(p, field);										\
	}																		\
																			\
	if (p != NULL) {														\
		__comp = (cmp)(elm, p);												\
		if (__comp < 0)														\
			BSTREE_LINK_LEFT(p, elm, field);								\
		else																\
			BSTREE_LINK_RIGHT(p, elm, field);								\
	} else {																\
		(head)->root = (elm);												\
	}																		\
																			\
}																			\
																			\
struct type *																\
name##_BSTREE_REMOVE(struct name *head, struct type *elm)					\
{																			\
	struct type *p, *child, *succ, *succ_p, *t;								\
	t = BSTREE_ROOT(head);													\
	p = NULL;																\
																			\
	int __comp;																\
	while(t != NULL) {														\
		__comp = (cmp)(elm, t);												\
		if (__comp == 0)													\
			break;															\
		p = t;																\
		if (__comp < 0)														\
			t = BSTREE_LEFT(p, field);										\
		else																\
			t = BSTREE_RIGHT(p, field);										\
	}																		\
																			\
	if (t == NULL) {														\
		fprintf(stderr, "%s(): key is not in the tree\n", __func__);		\
		return (NULL);														\
	}																		\
																			\
	if ((BSTREE_LEFT(t, field) == NULL) &&									\
		(BSTREE_RIGHT(t, field) == NULL)) {									\
																			\
		if (p != NULL) {													\
			if(BSTREE_LEFT(p, field) == t)									\
				BSTREE_LINK_LEFT(p, NULL, field);							\
			else															\
				BSTREE_LINK_RIGHT(p, NULL, field);							\
		} else {															\
			(head)->root = (NULL);											\
		}																	\
	} else if ((BSTREE_LEFT(t, field) == NULL) ||							\
			   (BSTREE_RIGHT(t, field) == NULL)) {							\
		if (BSTREE_LEFT(t, field) != NULL)									\
			child = BSTREE_LEFT(t, field);									\
		else																\
			child = BSTREE_RIGHT(t, field);									\
																			\
		if (p != NULL) {													\
			if(BSTREE_LEFT(p, field) == t)									\
				BSTREE_LINK_LEFT(p, child, field);							\
			else															\
				BSTREE_LINK_RIGHT(p, child, field);							\
		} else {															\
			(head)->root = (NULL);											\
		}																	\
	} else {																\
		succ_p = t;															\
		succ = BSTREE_RIGHT(t, field);										\
		while (BSTREE_LEFT(succ, field) != NULL) {							\
			succ_p = succ;													\
			succ = BSTREE_LEFT(succ, field);								\
		}																	\
																			\
		if (BSTREE_LEFT(succ_p, field) == succ)								\
			BSTREE_LINK_LEFT(succ_p, (BSTREE_RIGHT(succ, field)), field);	\
		else																\
			BSTREE_LINK_RIGHT(succ_p, (BSTREE_RIGHT(succ, field)), field);	\
																			\
		(swap)(t, succ);													\
		t = succ;															\
	}																		\
	return t;																\
}

#define BSTREE_INSERT(name, x, y)	name##_BSTREE_INSERT(x, y)
#define BSTREE_REMOVE(name, x, y)	name##_BSTREE_REMOVE(x, y)
#define BSTREE_SEARCH(name, x, y)	name##_BSTREE_SEARCH(x, y)

#endif /* __BSTREE_H__ */