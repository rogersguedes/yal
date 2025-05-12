#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <yal/single_list.h>
#include <yal/misc/array.h>
#include <yal/misc/mem.h>
#include <yal/misc/container_of.h>


int main(int argc, char *argv){
    YAL_NEW(yal_slist_t, single_list);
    if(!single_list){
        return EXIT_FAILURE;
    }
    yal_slist_init(single_list);

    typedef struct int_values_list {
        yal_slist_node_t list_node;
        int value;
    } samples_list_t;

    //samples_list_t samples[] = {
    //    {.sample = 1},
    //    {.sample = 3},
    //    {.sample = 7},
    //    {.sample = 11},
    //    {.sample = 13},
    //};

    int int_values[] = {
        1,
        3,
        7,
        11,
        13
    };

    samples_list_t* samples_nodes[ARRAY_ITEMS(int_values)];

    size_t i = 0;
    for (i = 0; i < ARRAY_ITEMS(int_values); i++){
        YAL_NEW(samples_list_t, new_elem);
        if (!new_elem){
            goto _end;
        }
        samples_nodes[i] = new_elem;
        yal_slist_node_init(&new_elem->list_node);
        new_elem->value = int_values[i];
        yal_slist_add_tail(single_list, &new_elem->list_node);
    }

    yal_slist_node_t* curr_node;
    yal_slist_for_each(single_list, curr_node) {
        samples_list_t* curr_sample_obj = container_of(curr_node, samples_list_t, list_node);
        printf("%d\n", curr_sample_obj->value);
    }

_end:
    for (size_t j = 0; j < i; j++) {
        yal_slist_remove_node(single_list, &samples_nodes[j]->list_node);
        yal_slist_node_destroy(&samples_nodes[j]->list_node);
        YAL_DELETE(samples_nodes[j]);
    }
    YAL_DELETE(single_list);
    return EXIT_SUCCESS;
}