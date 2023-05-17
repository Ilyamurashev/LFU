#include "struct.h"
#include "delete.h"
#include "insert.h"

void remove_page_in_hash_t(int key, struct page **hash_t)
{

}

//remove page in list of freq_node, not remove page from hash_t
void remove(struct page *new_page, struct bucket_freq_node **freq_hash_t, struct page **hash_t) {

    int freq = new_page->parent->value;

    if (freq_hash_t[freq]->lenght == 1) { //if page was alone in list
        delete_node(new_page->parent);
    } else {

    if (new_page->prev == NULL) {         //if first in bucket
        freq_hash_t[freq]->first = new_page->next;
        new_page->next->prev = NULL;
    } else if (new_page->next == NULL) {  //if last in bucket
        freq_hash_t[freq]->last = new_page->prev;
        new_page->prev->next = NULL;
    } else {                              //another case
        new_page->next->prev = new_page->prev;
        new_page->prev->next = new_page->next;
    }

    freq_hash_t[freq]->lenght -= 1;       //decrease length

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
