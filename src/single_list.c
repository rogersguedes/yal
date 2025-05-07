#include <yal/mutex.h>
#include <yal/single_list.h>

#include <errno.h>
#include <stddef.h>

static inline void add_next(yal_slist_node_t* previous, yal_slist_node_t* node)
{
    node->next     = previous->next;
    previous->next = node;
}

static inline yal_slist_node_t* remove_next(yal_slist_node_t* previous)
{
    yal_slist_node_t* next = previous->next;
    if (next) {
        previous->next = next->next;
        next->next     = NULL;
    }
    return next;
}

int yal_slist_init(yal_slist_t* list)
{
    int result;
    if (list == NULL) {
        return EINVAL;
    }
    result = yal_mutex_init(&list->mutex);
    if (result) {
        return result;
    }

    result = yal_slist_node_init(&list->sentinel);
    if (result) {
        yal_mutex_deinit(&list->mutex);
    }
    return result;
}

int yal_slist_destroy(yal_slist_t* list)
{
    if (list == NULL) {
        return EINVAL;
    }

    return yal_mutex_deinit(&list->mutex) || yal_slist_node_destroy(&list->sentinel);
}

int yal_slist_node_init(yal_slist_node_t* node)
{
    if (node == NULL) {
        return EINVAL;
    }

    node->next = NULL;
    return 0;
}

int yal_slist_node_destroy(yal_slist_node_t* node)
{
    if (node == NULL) {
        return EINVAL;
    }

    node->next = NULL;
    return 0;
}

int yal_slist_add_head(yal_slist_t* list, yal_slist_node_t* node)
{
    if (list == NULL || node == NULL) {
        return EINVAL;
    }
    yal_mutex_lock(&list->mutex);
    add_next(&list->sentinel, node);
    yal_mutex_unlock(&list->mutex);
    return 0;
}

int yal_slist_add_tail(yal_slist_t* list, yal_slist_node_t* node)
{
    if (list == NULL || node == NULL) {
        return EINVAL;
    }

    yal_slist_node_t* tmp_node = &list->sentinel;
    yal_mutex_lock(&list->mutex);
    while (tmp_node->next) {
        tmp_node = tmp_node->next;
    }

    add_next(tmp_node, node);
    yal_mutex_unlock(&list->mutex);
    return 0;
}

int yal_slist_add_after(yal_slist_t* list, yal_slist_node_t* previous, yal_slist_node_t* node)
{
    if (list == NULL || node == NULL) {
        return EINVAL;
    }

    if (previous == NULL) {
        return yal_slist_add_head(list, node);
    }

    yal_mutex_lock(&list->mutex);
    add_next(previous, node);
    yal_mutex_unlock(&list->mutex);
    return 0;
}

int yal_slist_add_before(yal_slist_t* list, yal_slist_node_t* next, yal_slist_node_t* node)
{
    if (list == NULL || node == NULL) {
        return EINVAL;
    }

    if (next == NULL) {
        return yal_slist_add_tail(list, node);
    }

    yal_slist_node_t* tmp_node = &list->sentinel;
    yal_mutex_lock(&list->mutex);
    while (tmp_node->next && tmp_node->next != next) {
        tmp_node = tmp_node->next;
    }

    if (tmp_node->next == NULL) {
        yal_mutex_unlock(&list->mutex);
        return ENODATA;
    }

    add_next(tmp_node, node);
    yal_mutex_unlock(&list->mutex);
    return 0;
}

yal_slist_node_t* yal_slist_remove_head(yal_slist_t* list)
{
    if (list == NULL) {
        return NULL;
    }

    yal_mutex_lock(&list->mutex);
    yal_slist_node_t* removed = remove_next(&list->sentinel);
    yal_mutex_unlock(&list->mutex);

    return removed;
}

yal_slist_node_t* yal_slist_remove_tail(yal_slist_t* list)
{
    if (list == NULL) {
        return NULL;
    }

    yal_slist_node_t* tmp_node = &list->sentinel;

    yal_mutex_lock(&list->mutex);
    while (tmp_node->next && tmp_node->next->next) {
        tmp_node = tmp_node->next;
    }
    yal_slist_node_t* removed = remove_next(tmp_node);
    yal_mutex_unlock(&list->mutex);

    return removed;
}

yal_slist_node_t* yal_slist_remove_next_node(yal_slist_t* list, yal_slist_node_t* previous)
{
    yal_slist_node_t* ret;
    if (list == NULL) {
        return NULL;
    }

    if (previous == NULL) {
        return yal_slist_remove_head(list);
    }
    yal_mutex_lock(&list->mutex);
    ret = remove_next(previous);
    yal_mutex_unlock(&list->mutex);

    return ret;
}

yal_slist_node_t* yal_slist_remove_previous_node(yal_slist_t* list, yal_slist_node_t* next)
{
    yal_slist_node_t* ret;
    if (list == NULL) {
        return NULL;
    }

    if (next == NULL) {
        return yal_slist_remove_tail(list);
    }

    yal_slist_node_t* tmp_node = &list->sentinel;

    yal_mutex_lock(&list->mutex);
    while (tmp_node->next && tmp_node->next->next != next) {
        tmp_node = tmp_node->next;
    }
    ret = remove_next(tmp_node);
    yal_mutex_unlock(&list->mutex);

    return ret;
}

yal_slist_node_t* yal_slist_remove_node(yal_slist_t* list, yal_slist_node_t* node)
{
    yal_slist_node_t* ret;
    if (list == NULL || node == NULL) {
        return NULL;
    }

    yal_slist_node_t* tmp_node = &list->sentinel;

    yal_mutex_lock(&list->mutex);
    while (tmp_node->next && tmp_node->next != node) {
        tmp_node = tmp_node->next;
    }

    ret = remove_next(tmp_node);
    yal_mutex_unlock(&list->mutex);

    return ret;
}

yal_slist_node_t* yal_slist_get_head(yal_slist_t* list)
{
    yal_slist_node_t* ret;
    if (list == NULL) {
        return NULL;
    }
    yal_mutex_lock(&list->mutex);
    ret = list->sentinel.next;
    yal_mutex_unlock(&list->mutex);
    return ret;
}

yal_slist_node_t* yal_slist_get_tail(yal_slist_t* list)
{
    if (list == NULL) {
        return NULL;
    }

    yal_slist_node_t* tmp_node = &list->sentinel;
    yal_mutex_lock(&list->mutex);
    do {
        tmp_node = tmp_node->next;
    } while (tmp_node);
    yal_mutex_unlock(&list->mutex);

    return tmp_node;
}

yal_slist_node_t* yal_slist_get_next_node(yal_slist_t* list, yal_slist_node_t* previous)
{
    if (list == NULL) {
        return NULL;
    }
    yal_mutex_lock(&list->mutex);
    yal_slist_node_t* tmp_node = previous ? previous->next : list->sentinel.next;
    yal_mutex_unlock(&list->mutex);
    return tmp_node;
}