#include <stdlib.h>
#include <assert.h>

struct page {
    struct freq_node *parent;
    struct page *next;
    struct page *prev;
    int value;
    struct page *next_hash;
    struct page *prev_hash;
};

int check_key(int key, struct page* page){
    if(key == page->value) return 1;
    else return 0;
}

//This function remove the page

void remove_page_in_hash_t(int key, struct page **hash_t){
    int id = 0;
    id = get_hash(key);
    struct page *tp;
    struct page *prev;
    struct page *next;
    tp = hash_t[id];
    assert(tp != NULL);
    next = tp->next_hash;
    if(check_key(key, tp) == 1){                    //
        free(tp);                                   // key == value on the first circle
        if(next != NULL) next->prev_hash = NULL;    //
    }
    else{
        prev = tp;
        tp = next;
        next = tp->next_hash;
        while(check_key(key, tp) != 1){
            prev = tp;                                           //
            tp = tp->next_hash;                                 // looking for the key
            if(next != NULL) next = tp->next_hash;             //
        }
        if(next == NULL){                                    // 
            prev->next_hash = next;                         // the key is in the last circle
            free(tp);                                      //
        }
        else{                                            // 
            prev->next_hash = next;                     // the key is in the middle
            next->prev_hash = prev;                    //
            free(tp);
        }
    }

          
    

    
}