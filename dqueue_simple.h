#ifndef DQUEUE_SIMPLE_H
#define DQUEUE_SIMPLE_H

#ifdef __GNUC__
	#pragma GCC diagnostic push
	#pragma GCC diagnostic ignored "-Wunused-function"
#endif

#include <assert.h>

// DQueue

#define DQUEUE_MEMBER(type)			type * node_prev, * node_next;

#define DQUEUE_HEAD(uniquename, type)																			\
		struct uniquename ## dqueue_head_s																		\
		{																										\
			type * begin, * end;																				\
		} uniquename ## dqueue_head;																			\

#define DQUEUE_INIT_FUNC(uniquename, type)																		\
static inline void uniquename ## dqueue_init(struct uniquename ## dqueue_head_s * head, type * node)			\
{																												\
	assert(head);																								\
	head->begin = head->end = node;																				\
}																												\
static inline int uniquename ## dqueue_not_empty(struct uniquename ## dqueue_head_s * head)						\
{																												\
	assert(head);																								\
	return head->begin && head->end;																			\
}																												\
static inline type * uniquename ## dqueue_node_init(type * node) 												\
{																												\
	node->node_prev = node->node_next = NULL;																	\
	return node;																								\
}																												\
static inline int uniquename ## dqueue_node_not_empty(const type * node)										\
{																												\
	return node != NULL;																						\
}																												\
static inline type * uniquename ## dqueue_get_prev_node(const type * node) 										\
{																												\
	assert(node);																								\
	return node->node_prev;																						\
}																												\
static inline type * uniquename ## dqueue_get_next_node(const type * node) 										\
{																												\
	return node->node_next;																						\
}																												\
static inline type * uniquename ## dqueue_get_first_node(const struct uniquename ## dqueue_head_s * head)		\
{																												\
	return head->begin;																							\
}																												\
static inline type * uniquename ## dqueue_get_last_node(const struct uniquename ## dqueue_head_s * head)		\
{																												\
	return head->end;																							\
}																												\
static inline int uniquename ## dqueue_node_is_first(const struct uniquename ## dqueue_head_s * head,			\
			const type * node)																					\
{																												\
	return head->begin == node;																					\
}																												\
static inline int uniquename ## dqueue_node_is_last(const struct uniquename ## dqueue_head_s * head,			\
			const type * node)																					\
{																												\
	return head->end == node;																					\
}																												\
static type * uniquename ## dqueue_insert_before(struct uniquename ## dqueue_head_s * head,						\
			type * node, type * nodenew) 																		\
{																												\
	assert(uniquename ## dqueue_node_not_empty(nodenew));														\
	if(uniquename ## dqueue_not_empty(head))																	\
	{																											\
		assert(uniquename ## dqueue_node_not_empty(node));														\
		type * nodeprev = uniquename ## dqueue_get_prev_node(node);												\
		nodenew->node_prev = nodeprev;																			\
		nodenew->node_next = node;																				\
		node->node_prev = nodenew;																				\
		if(uniquename ## dqueue_node_not_empty(nodeprev))														\
		{																										\
			nodeprev->node_next = nodenew;																		\
		} else {																								\
			head->begin = nodenew;																				\
		}																										\
	} else {																									\
		assert(!uniquename ## dqueue_node_not_empty(node));														\
		uniquename ## dqueue_init(head, nodenew);																\
	}																											\
	return nodenew;																								\
}																												\
static type * uniquename ## dqueue_insert_after(struct uniquename ## dqueue_head_s * head,						\
			type * node, type * nodenew) 																		\
{																												\
	assert(uniquename ## dqueue_node_not_empty(nodenew));														\
	if(uniquename ## dqueue_not_empty(head))																	\
	{																											\
		assert(uniquename ## dqueue_node_not_empty(node));														\
		type * nodenext = uniquename ## dqueue_get_next_node(node);												\
		nodenew->node_prev = node;																				\
		nodenew->node_next = nodenext;																			\
		node->node_next = nodenew;																				\
		if(uniquename ## dqueue_node_not_empty(nodenext))														\
		{																										\
			nodenext->node_prev = nodenew;																		\
		} else {																								\
			head->end = nodenew;																				\
		}																										\
	} else {																									\
		assert(!uniquename ## dqueue_node_not_empty(node));														\
		uniquename ## dqueue_init(head, nodenew);																\
	}																											\
	return nodenew;																								\
}																												\
static inline type * uniquename ## dqueue_push_first(struct uniquename ## dqueue_head_s * head, type * nodenew)	\
{																												\
	assert(uniquename ## dqueue_node_not_empty(nodenew));														\
	if(uniquename ## dqueue_not_empty(head))																	\
	{																											\
		type * next = head->begin;																				\
		nodenew->node_prev = NULL;																				\
		nodenew->node_next = next;																				\
		next->node_prev = nodenew;																				\
		head->begin = nodenew;																					\
	} else {																									\
		uniquename ## dqueue_init(head, nodenew);																\
	}																											\
	return nodenew;																								\
}																												\
static inline type * uniquename ## dqueue_push_back(struct uniquename ## dqueue_head_s * head, type * nodenew)	\
{																												\
	assert(uniquename ## dqueue_node_not_empty(nodenew));														\
	if(uniquename ## dqueue_not_empty(head))																	\
	{																											\
		type * prev = head->end;																				\
		nodenew->node_prev = prev;																				\
		nodenew->node_next = NULL;																				\
		prev->node_next = nodenew;																				\
		head->end = nodenew;																					\
	} else {																									\
		uniquename ## dqueue_init(head, nodenew);																\
	}																											\
	return nodenew;																								\
}																												\
static inline type * uniquename ## dqueue_remove(struct uniquename ## dqueue_head_s * head, type * const node)	\
{																												\
	assert(uniquename ## dqueue_not_empty(head));																\
	if(uniquename ## dqueue_node_not_empty(node))																\
	{																											\
		type * next = uniquename ## dqueue_get_next_node(node);													\
		type * prev = uniquename ## dqueue_get_prev_node(node);													\
		if(uniquename ## dqueue_node_not_empty(prev))															\
		{																										\
			prev->node_next = next;																				\
		} else {																								\
			head->begin = next;																					\
		}																										\
		if(uniquename ## dqueue_node_not_empty(next))															\
		{																										\
			next->node_prev = prev;																				\
		} else {																								\
			head->end = prev;																					\
		}																										\
	}																											\
	uniquename ## dqueue_node_init(node);																		\
	return node;																								\
}																												\
static inline type * uniquename ## dqueue_remove_first(struct uniquename ## dqueue_head_s * head)				\
{																												\
	if(uniquename ## dqueue_not_empty(head))																	\
	{																											\
		type * first = uniquename ## dqueue_get_first_node(head);												\
		type * next = uniquename ## dqueue_get_next_node(first);												\
		head->begin = next;																						\
		if(uniquename ## dqueue_node_not_empty(next))															\
		{																										\
			next->node_prev = NULL;																				\
		} else {																								\
			head->end = NULL;																					\
		}																										\
		uniquename ## dqueue_node_init(first);																	\
		return first;																							\
	} else {																									\
		return NULL;																							\
	}																											\
}																												\
static inline type * uniquename ## dqueue_remove_last(struct uniquename ## dqueue_head_s * head)				\
{																												\
	if(uniquename ## dqueue_not_empty(head))																	\
	{																											\
		type * last = uniquename ## dqueue_get_last_node(head);													\
		type * prev = uniquename ## dqueue_get_next_node(last);													\
		head->end = prev;																						\
		if(uniquename ## dqueue_node_not_empty(prev))															\
		{																										\
			prev->node_next = NULL;																				\
		} else {																								\
			head->begin = NULL;																					\
		}																										\
		uniquename ## dqueue_node_init(last);																	\
		return last;																							\
	} else {																									\
		return NULL;																							\
	}																											\
}																												\

#ifdef __GNUC__
	#pragma GCC diagnostic pop
#endif

#endif  // DQUEUE_SIMPLE_H
