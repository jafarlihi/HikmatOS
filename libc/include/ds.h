#ifndef _DS_H
#define _DS_H 1

#include <stdint.h>

typedef void* type_t;
typedef int8_t (*lessthan_predicate_t)(type_t,type_t);
typedef struct {
    type_t *array;
    uint32_t size;
    uint32_t max_size;
    lessthan_predicate_t less_than;
} ordered_array_t;

int8_t standard_lessthan_predicate(type_t a, type_t b);
ordered_array_t create_ordered_array(uint32_t max_size, lessthan_predicate_t less_than);
ordered_array_t place_ordered_array(void *addr, uint32_t max_size, lessthan_predicate_t less_than);
void destroy_ordered_array(ordered_array_t *array);
void insert_ordered_array(type_t item, ordered_array_t *array);
type_t lookup_ordered_array(uint32_t i, ordered_array_t *array);
void remove_ordered_array(uint32_t i, ordered_array_t *array);

typedef struct ll_node {
    void *value;
    struct ll_node *next;
} ll_node_t;

ll_node_t *create_llist();
void ll_insert(ll_node_t *ll, void *value);
void ll_remove_value(ll_node_t *ll, void *value);

#endif

