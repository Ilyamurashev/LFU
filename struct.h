#ifndef STRUCT_H_INCLUDED
#define STRUCT_H_INCLUDED

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
};

#endif // STRUCT_H_INCLUDED
