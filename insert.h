#ifndef INSERT_H_INCLUDED
#define INSERT_H_INCLUDED

#include <stdio.h>
#include <ctype.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

void add(int key, struct page *last, struct freq_node *parent,
        struct page **freq_hash_t, struct freq_node **hash_t);

struct freq_node *get_new_node(int value, struct freq_node *prev,
                               struct freq_node *next, struct page **freq_hash_t);

void insert(int key, struct page **freq_hash_t, struct freq_node **hash_t);

void access(int key, struct page **freq_hash_t, struct freq_node **hash_t, int *cache_hit);

#endif // INSERT_H_INCLUDED
