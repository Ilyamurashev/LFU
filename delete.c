#include "struct.h"
#include "delete.h"
#include "insert.h"

void remove(int key, struct bucket_freq_node **freq_hash_t, struct page **hash_t) {
    int freq = hash_t[key]->parent->value;

    if (freq_hash_t[freq]->lenght == 1) {
        delete_node(hash_t[key]->parent);
    } else {

    if (hash_t[key]->prev == NULL) {        //if first in bucket
        freq_hash_t[freq]->first = hash_t[key]->next;
        hash_t[key]->next->prev = NULL;
    } else if (hash_t[key]->next == NULL) { //if last in bucket
        freq_hash_t[freq]->last = hash_t[key]->prev;
        hash_t[key]->prev->next = NULL;
    } else {                                //another case
        hash_t[key]->next->prev = hash_t[key]->prev;
        hash_t[key]->prev->next = hash_t[key]->next;
    }

    freq_hash_t[freq]->lenght -= 1; //decrease length

    }

}

void delete_node(struct freq_node *node, struct bucket_freq_node **freq_hash_t) {

    int freq = node->value;

    node->prev->next = node->next;
    if (node->next != NULL) {
        node->next->prev = node->prev;
    }

    freq_hash_t[freq]->first  = NULL;
    freq_hash_t[freq]->prev   = NULL;
    freq_hash_t[freq]->length = 0;
}
