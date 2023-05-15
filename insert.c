#include "struct.h"
#include "delete.h"
#include "insert.h"

void fill_freq_hash_t(struct bucket_freq_node **freq_hash_t, struct page *first,
                    struct page *last, int length, int index) {

    freq_hash_t[index]->first  = first;
    freq_hash_t[index]->last   = last;
    freq_hash_t[index]->length = length;

}

void add(int key, struct page *last, struct freq_node *parent,
        struct bucket_freq_node **freq_hash_t, struct freq_node **hash_t) {

    int freq = -1;

    hash_t[key]->parent = parent;
    hash_t[key]->next = NULL;
    hash_t[key]->prev = last;
    if (last != NULL)
        last->next = hash_t[key];

    freq = hash_t[key]->parent->value;

    if (freq_hash_t[freq]->first == NULL)
        freq_hash_t[freq]->first = hash_t[key];   //change first in bucket
    freq_hash_t[freq]->last = hash_t[key];        //change last  in bucket
    freq_hash_t[freq]->lenght += 1;               //increase length
}

struct freq_node *get_new_node(int value, struct freq_node *prev,
                               struct freq_node *next, struct bucket_freq_node **freq_hash_t) {

    struct freq_node *new_node;

    new_node = (struct freq_node*)malloc(sizeof(struct freq_node));
    new_node->next = next;
    new_node->prev = prev;
    prev->next = new_node;
    if (next != NULL)
        next->prev = new_node;
    new_node->value = value;

    if (value > lfu_cache->size_freq_hash_t) {
        freq_hash_t = (struct bucket_freq_node**)realloc(freq_hash_t, (value+1)*sizeof(struct bucket_freq_node*));
        lfu_cache->size_freq_hash_t = value+1;
    }

    fill_freq_hash_t(freq_hash_t, NULL, NULL, 0, value);

    return new_node;
}

void insert(int key, struct bucket_freq_node **freq_hash_t, struct page **hash_t) {

    struct freq_node *freq_n;
    struct page *old_last;

    if (key not in hash_t) {    //create checking
        freq_n = lfu_cache->freq_head->next;

        if (freq_n->value != 1)
            freq_n = get_new_node(1, lfu_cache->freq_head, freq_n);

        old_last = freq_hash_t[1]->last;
        add(key, freq_hash_t[1]->last, freq_n); //add

        if (key > lfu_cache->size_hash_t) {
            hash_t = (struct page **) realloc(hash_t, (key+1) * sizeof(struct page *));
            lfu_cache->size_hash_t = key + 1;
        }
        update_hash_t(key, freq_n, NULL, old_last);
    }
}

void access(int key, struct bucket_freq_node **freq_hash_t, struct page **hash_t, int *cache_hit) {

    if (key in hash_t) {        //create checking
        *cache_hit += 1;
        struct page *tmp = hash_t[key];
        struct freq_node *freq_n = tmp->parent;

        if (freq_n->next != NULL) {
            struct freq_node *next_freq_n = freq_n->next;

            if (next_freq_n == lfu_cache.freq_head or next_freq_n->value != (1 + freq_n->value)) {
                next_freq_n = get_new_node(freq_n->value + 1, freq_n, next_freq_n);
            }

        } else {
            next_freq_n = get_new_node(freq_n->value + 1, freq_n, freq_n->next);
        }

        remove(key);
        add(key, freq_hash_t[hash_t[key]->parent->value]->last, next_freq_n);
    }
}
