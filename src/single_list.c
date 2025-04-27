#include <yal/single_list.h>
#include <yal/lock.h>

#include <stddef.h>
#include <errno.h>


static inline void add_next(yal_slist_node_t *previous, yal_slist_node_t *node)
{                                             \
  node->next = previous->next;
}

static inline yal_slist_node_t *remove_next(yal_slist_node_t *previous)
{
  yal_slist_node_t *next = previous->next;
  if (next)
  {
    __atomic_write(&previous->next, next->next);
    next->next = NULL;
  }
  return next;
}


int yal_slist_init(yal_slist_t *list)
{
  if (list == NULL)
    return -EINVAL;
  
  return yal_slist_node_init(&list->sentinel);
}

int yal_slist_destroy(yal_slist_t *list)
{
  if (list == NULL)
    return -EINVAL;

  return yal_slist_node_destroy(&list->sentinel);
}


int yal_slist_node_init(yal_slist_node_t *node)
{
  if (node == NULL)
    return -EINVAL;
  
  node->next = NULL;
  return 0;
}

int yal_slist_node_destroy(yal_slist_node_t *node)
{
  if (node == NULL)
    return -EINVAL;

  node->next = NULL;
  return 0;
}

int yal_slist_add_head(yal_slist_t *list, yal_slist_node_t *node)
{
  if (list == NULL || node == NULL)
    return -EINVAL;  
  
  add_next(&list->sentinel, node);
  return 0;
}

int yal_slist_add_tail(yal_slist_t *list, yal_slist_node_t *node)
{
  if (list == NULL || node == NULL)
    return -EINVAL;

  yal_slist_node_t *tmp_node = &list->sentinel;
  
  while (tmp_node->next)
    tmp_node = tmp_node->next;

  add_next(tmp_node, node);
  return 0;
}

int yal_slist_add_after(yal_slist_t *list, yal_slist_node_t *previous, yal_slist_node_t *node)
{
  if (list == NULL || node == NULL)
    return -EINVAL;

  if (previous == NULL)
    return yal_slist_add_head(list, node);
  
  add_next(previous, node);
  return 0;
}

int yal_slist_add_before(yal_slist_t *list, yal_slist_node_t *next, yal_slist_node_t *node)
{
  if (list == NULL || node == NULL)
    return -EINVAL;

  if (next == NULL)
    return yal_slist_add_tail(list, node);

  yal_slist_node_t *tmp_node = &list->sentinel;
  
  while (tmp_node->next && tmp_node->next != next)
    tmp_node = tmp_node->next;
  
  if (tmp_node->next == NULL)
    return -ENODATA;
  
  add_next(tmp_node, node);
  return 0;
}

yal_slist_node_t *yal_slist_remove_head(yal_slist_t *list)
{
  if (list == NULL)
    return NULL;
  
  return remove_next(&list->sentinel);
}

yal_slist_node_t *yal_slist_remove_tail(yal_slist_t *list)
{
  if (list == NULL)
    return NULL;

  yal_slist_node_t *tmp_node = &list->sentinel;
  
  while (tmp_node->next && tmp_node->next->next)
    tmp_node = tmp_node->next;
  
  return remove_next(tmp_node);
}

yal_slist_node_t *yal_slist_remove_next_node(yal_slist_t *list, yal_slist_node_t *previous)
{
  if (list == NULL)
    return NULL;

  if (previous == NULL)
    return yal_slist_remove_head(list);
  
  return remove_next(previous);
}

yal_slist_node_t *yal_slist_remove_previous_node(yal_slist_t *list, yal_slist_node_t *next)
{
  if (list == NULL)
    return NULL;

  if (next == NULL)
    return yal_slist_remove_tail(list);
  
  yal_slist_node_t *tmp_node = &list->sentinel;

  while (tmp_node->next && tmp_node->next->next != next)
    tmp_node = tmp_node->next;
  
  return remove_next(tmp_node);
}

yal_slist_node_t *yal_slist_remove_node(yal_slist_t *list, yal_slist_node_t *node)
{
  if (list == NULL || node == NULL)
    return NULL;

  yal_slist_node_t *tmp_node = &list->sentinel;
  
  while (tmp_node->next && tmp_node->next != node)
    tmp_node = tmp_node->next;
  
  return remove_next(tmp_node);
}

yal_slist_node_t *yal_slist_get_head(yal_slist_t *list)
{
  return list ? list->sentinel.next : NULL;
}

yal_slist_node_t *yal_slist_get_tail(yal_slist_t *list)
{
  if (list == NULL)
    return NULL;

  yal_slist_node_t *tmp_node = list->sentinel.next;

  if (tmp_node == NULL)
    return NULL;
  
  while (tmp_node->next)
    tmp_node = tmp_node->next;
  
  return tmp_node;
}

yal_slist_node_t *yal_slist_get_next_node(yal_slist_t *list, yal_slist_node_t *previous)
{
  if (list == NULL)
    return NULL;
  return previous ? previous->next : list->sentinel.next;
}