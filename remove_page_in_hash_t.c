#include <stdlib.h>

struct page {
    struct freq_node *parent;
    struct page *next;
    struct page *prev;
    int value;
    struct page *next_hash;
    struct page *prev_hash;
};

//This function remove the page

void remove_page_in_hash_t(int key, struct page **hash_t){
    int id = 0;
    id = get_hash(key);
    struct page *tp;
    struct page *prev;
    tp = hash_t[id];
    while(tp->next != NULL){    //
        prev = tp;             // looking for the last element
        tp = tp->next;        //
        }
    prev->next = NULL;      // remove page
    free(tp);              //
    

    
}