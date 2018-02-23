#ifndef QUEUE_SIMPLE_H
#define QUEUE_SIMPLE_H

#ifdef __GNUC__
	#pragma GCC diagnostic push
	#pragma GCC diagnostic ignored "-Wunused-function"
#endif

#include <assert.h>

// Simple FIFO Queue

#define QUEUE_MEMBER(type)		type * node_next;

#define QUEUE_HEAD(uniquename, type)																			\
		struct uniquename ## queue_head_s																		\
		{																										\
			type * begin, * end;																				\
		} uniquename ## queue_head;																				\

#define QUEUE_INIT_FUNC(uniquename, type)																		\
static inline void uniquename ## queue_init(struct uniquename ## queue_head_s * head)							\
{																												\
	head->begin = NULL;																							\
	head->end = NULL;																							\
}																												\
static inline int uniquename ## queue_not_empty(const struct uniquename ## queue_head_s * head)					\
{																												\
	return head->begin && head->end;																			\
}																												\
static inline type * uniquename ## queue_node_init(type * node) 												\
{																												\
	node->node_next = NULL;																						\
	return node;																								\
}																												\
static inline int uniquename ## queue_node_not_empty(const type * node)											\
{																												\
	return node != NULL;																						\
}																												\
static inline int uniquename ## queue_is_last(const struct uniquename ## queue_head_s * head,					\
			const type * node)																					\
{																												\
	return head->end == node;																					\
}																												\
static inline type * uniquename ## queue_get_next_node(const type * node) 										\
{																												\
	return node->node_next;																						\
}																												\
static inline type * uniquename ## queue_get_first_node(const struct uniquename ## queue_head_s * head)			\
{																												\
	return head->begin;																							\
}																												\
static inline type * uniquename ## queue_get_last_node(const struct uniquename ## queue_head_s * head)			\
{																												\
	return head->end;																							\
}																												\
static inline type * uniquename ## queue_insert_after(struct uniquename ## queue_head_s * head,					\
			type * node, type * nextnode) 																		\
{																												\
	assert(uniquename ## queue_node_not_empty(nextnode));														\
	if(uniquename ## queue_node_not_empty(node))																\
	{																											\
		assert(uniquename ## queue_not_empty(head));															\
		if(uniquename ## queue_is_last(head, node))																\
		{																										\
			head->end = nextnode;																				\
		}																										\
		node->node_next = nextnode;																				\
	} else {																									\
		assert(!uniquename ## queue_not_empty(head));															\
		head->begin = nextnode;																					\
		head->end = nextnode;																					\
	}																											\
	uniquename ## queue_node_init(nextnode);																	\
	return nextnode;																							\
}																												\
static inline type * uniquename ## queue_push_back(struct uniquename ## queue_head_s * head, type * node)		\
{																												\
	if(uniquename ## queue_not_empty(head))																		\
	{																											\
		type * n = uniquename ## queue_get_last_node(head);														\
		n->node_next = node;																					\
	} else {																									\
		head->begin = node;																						\
	}																											\
	head->end = node;																							\
	uniquename ## queue_node_init(node);																		\
	return node;																								\
}																												\
static inline type * uniquename ## queue_remove_first(struct uniquename ## queue_head_s *  head) 				\
{																												\
	if(uniquename ## queue_not_empty(head))																		\
	{																											\
		type * n = head->begin;																					\
		head->begin = uniquename ## queue_get_next_node(n);														\
		if(! uniquename ## queue_node_not_empty(head->begin))													\
		{																										\
			uniquename ## queue_init(head);																		\
		}																										\
		uniquename ## queue_node_init(n);																		\
		return n;																								\
	}																											\
	return NULL;																								\
}																												\

#ifdef __GNUC__
	#pragma GCC diagnostic pop
#endif

#endif  // QUEUE_SIMPLE_H
