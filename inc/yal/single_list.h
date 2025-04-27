
#ifndef __yal_single_list_H__
#define __yal_single_list_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>

typedef struct yal_slist_node
{
  struct yal_slist_node *next;
} yal_slist_node_t;

typedef struct yal_single_list
{
  yal_slist_node_t sentinel;
} yal_slist_t;

int yal_slist_init(yal_slist_t *list);

int yal_slist_destroy(yal_slist_t *list);

int yal_slist_node_init(yal_slist_node_t *node);

int yal_slist_node_destroy(yal_slist_node_t *node);

int yal_slist_add_head(yal_slist_t *list, yal_slist_node_t *node);

int yal_slist_add_tail(yal_slist_t *list, yal_slist_node_t *node);

int yal_slist_add_after(yal_slist_t *list, yal_slist_node_t *previous, yal_slist_node_t *node);

int yal_slist_add_before(yal_slist_t *list, yal_slist_node_t *next, yal_slist_node_t *node);

yal_slist_node_t *yal_slist_remove_head(yal_slist_t *list);

yal_slist_node_t *yal_slist_remove_tail(yal_slist_t *list);

yal_slist_node_t *yal_slist_remove_next_node(yal_slist_t *list, yal_slist_node_t *previous);

yal_slist_node_t *yal_slist_remove_previous_node(yal_slist_t *list, yal_slist_node_t *next);

yal_slist_node_t *yal_slist_remove_node(yal_slist_t *list, yal_slist_node_t *node);

yal_slist_node_t *yal_slist_get_head(yal_slist_t *list);

yal_slist_node_t *yal_slist_get_tail(yal_slist_t *list);

yal_slist_node_t *yal_slist_get_next_node(yal_slist_t *list, yal_slist_node_t *previous);

#ifdef __cplusplus
}
#endif

#endif