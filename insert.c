#include "struct.h"
#include "delete.h"
#include "insert.h"

//return pointer to new_page
//if first in bucket => its previous = NULL
struct page *add_page_in_hash_t(int key, struct page **hash_t)
{

}

//after remove and add we need to update freq_hash_t
void update_freq_hash_t()
{

}

void fill_freq_hash_t(struct bucket_freq_node **freq_hash_t, struct page *first,
                    struct page *last, int length, int index) {

    freq_hash_t[index]->first  = first;
    freq_hash_t[index]->last   = last;
    freq_hash_t[index]->length = length;

}

//last - last page in list of freq_node
void add(struct page *new_page, struct page *last, struct freq_node *parent,
        struct bucket_freq_node **freq_hash_t, struct page **hash_t) {

    int freq = -1;

    new_page->parent = parent;
    new_page->next = NULL;
    new_page->prev = last;
    if (last != NULL)
        last->next = new_page;

    freq = new_page->parent->value;

    if (freq_hash_t[freq]->first == NULL)
        freq_hash_t[freq]->first = new_page;      //change first in bucket if necessary
    freq_hash_t[freq]->last = new_page;           //change last  in bucket
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

void insert(int key, struct bucket_freq_node **freq_hash_t, struct page **hash_t, int *pages_in_cache) {

    struct freq_node *freq_n;
    struct page *old_last;      //last page in list of freq_node before adding
    struct page *new_page;

    if (key not in hash_t) {    //create checking
        *pages_in_cache += 1;   //new page => increase their number
        new_page = add_page_in_hash_t(key, hash_t);
        freq_n = lfu_cache->freq_head->next;

        if (freq_n->value != 1)
            freq_n = get_new_node(1, lfu_cache->freq_head, freq_n);

        old_last = freq_hash_t[1]->last;
        add(new_page, freq_hash_t[1]->last, freq_n); //add page in list of freq_node

        /*if (key > lfu_cache->size_hash_t) {
            hash_t = (struct page **) realloc(hash_t, (key+1) * sizeof(struct page *));
            lfu_cache->size_hash_t = key + 1;
        }
        */

        update_freq_hash_t(key, freq_n, NULL, old_last);
    }
}

            //move page to next freq_node
            //and if necessary creates new freq_node

void access(int key, struct bucket_freq_node **freq_hash_t, struct page **hash_t, int *cache_hit) {

    struct page *get_page;

    if (get_page = key in hash_t) {        //create checking
        *cache_hit += 1;
        struct freq_node *freq_n = get_page->parent;

        if (freq_n->next != NULL) {
            struct freq_node *next_freq_n = freq_n->next;

            if (next_freq_n == lfu_cache.freq_head or next_freq_n->value != (1 + freq_n->value)) {
                next_freq_n = get_new_node(freq_n->value + 1, freq_n, next_freq_n);
            }

        } else {
            next_freq_n = get_new_node(freq_n->value + 1, freq_n, freq_n->next);
        }

        remove(get_page, freq_hash_t, hash_t);
        add(get_page, freq_hash_t[get_page->parent->next->value]->last, next_freq_n, freq_hash_t, hash_t);
    }
}
