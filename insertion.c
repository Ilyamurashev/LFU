#include <stdio.h>
#include <ctype.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

struct freq_node { //structure of frequency node
    int value; //frequency
    struct freq_node *next;
    struct freq_node *prev;
};

struct page {
    struct freq_node *parent; //frequency of page
    struct page *next;
    struct page *prev;
};

struct bucket_freq_node {  //element of frequency hash table
    struct page *last;
    struct page *first;
    int lenght;
};

struct lfu_cache {
    struct page **hash_t;
    struct freq_node *freq_head;
    int size_hash_t;
    int size_freq_hash_t;
}



void add(int key, struct page *last, struct freq_node *parent) {
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

void remove(int key) {
    int freq = hash_t[key]->parent->value;

    if (freq_hash_t[freq]->lenght == 1) {
        delete_node(hash_t[key]->parent);
    } else {

    if (hash_t[key]->prev == NULL) {        //first in bucket
        freq_hash_t[freq]->first = hash_t[key]->next;
        hash_t[key]->next->prev = NULL;
    } else if (hash_t[key]->next == NULL) { //last in bucket
        freq_hash_t[freq]->last = hash_t[key]->prev;
        hash_t[key]->prev->next = NULL;
    } else {
        hash_t[key]->next->prev = hash_t[key]->prev;
        hash_t[key]->prev->next = hash_t[key]->next;
    }

    freq_hash_t[freq]->lenght -= 1; //decrease length

    }

}

struct freq_node *get_new_node(int value, struct freq_node *prev, struct freq_node *next) {

    struct freq_node *new_node;

    new_node = (struct freq_node*)malloc(sizeof(struct freq_node));
    new_node->next = next;
    new_node->prev = prev;
    prev->next = new_node;
    if (next != NULL)
        next->prev = new_node;
    new_node->value = value;

    if (value > lfu_cache->size_freq_hash_t) {
        freq_hash_t = (struct freq_node*)realloc(freq_hash_t, (value+1)*sizeof(struct freq_node));
        lfu_cache->size_freq_hash_t = value+1;
    }

    freq_hash_t[value]->length = 0;
    freq_hash_t[value]->first  = NULL;
    freq_hash_t[value]->last   = NULL;

    return new_node;
}

void delete_node(struct freq_node *node) {

    int freq = node->value;

    node->prev->next = node->next;
    if (node->next != NULL) {
        node->next->prev = node->prev;
    }

    freq_hash_t[freq]->first  = NULL;
    freq_hash_t[freq]->prev   = NULL;
    freq_hash_t[freq]->length = 0;
}

void insert(int key) {

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

void access(int key) {

    if (key in hash_t) {        //create checking
        //m += 1;  - cache hit
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

int main()
{
    struct page **hash_t;
    struct bucket_freq_node *freq_hash_t; //index = frequency


    return 0;
}
