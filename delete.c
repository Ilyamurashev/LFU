#include "struct.h"
#include "delete.h"
#include "insert.h"

void remove_page_in_hash_t(int key, struct page **hash_t) {

    assert(hash_t && "hash_t shall not be null");

    int id = 0;

    struct page *tp;
    struct page *prev;
    struct page *next;

    id = get_page_hash(key);
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


void delete_node(struct freq_node *node, struct bucket_freq_node *freq_hash_t) {

    assert(node        &&        "node shall not be null");
    assert(freq_hash_t && "freq_hash_t shall not be null");

    int freq = node->value;

    node->prev->next = node->next;
    if (node->next != NULL) {
        node->next->prev = node->prev;
    }

    freq_hash_t[freq].first  = NULL;
    freq_hash_t[freq].last   = NULL;
    freq_hash_t[freq].length = 0;
}

//remove page in list of freq_node, not remove page from hash_t
void remove_page_in_freq_hash_t(struct page *del_page, struct bucket_freq_node *freq_hash_t) {

    //assert(hash_t      &&      "hash_t shall not be null");
    assert(del_page    &&    "del_page shall not be null");
    assert(freq_hash_t && "freq_hash_t shall not be null");

    int freq = del_page->parent->value;

    if (freq_hash_t[freq].length == 1) { //if page was alone in list
        delete_node(del_page->parent, freq_hash_t);
    } else {

    if (del_page->prev == NULL) {         //if first in bucket
        freq_hash_t[freq].first = del_page->next;
        del_page->next->prev = NULL;
    } else if (del_page->next == NULL) {  //if last in bucket
        freq_hash_t[freq].last = del_page->prev;
        del_page->prev->next = NULL;
    } else {                              //another case
        del_page->next->prev = del_page->prev;
        del_page->prev->next = del_page->next;
    }

    freq_hash_t[freq].length -= 1;       //decrease length

    }

}

void cleaner(struct lfu_cache *lfu, struct page **hash_t,
             struct bucket_freq_node *freq_hash_t, int *pages_in_cache) {

  // get the required frequency node and page.

  struct freq_node *current_freq_node = (lfu->freq_head)->next;
  int frequency = current_freq_node->value;
  struct page *del_page = (freq_hash_t[frequency]).first;

  // check if page contains anything

  if (del_page == NULL) {
    fprintf(stderr, "Something went wrong. You are cleaning a non-existing object.\n");
    fprintf(stderr, "ERROR_LINE %d\n", __LINE__);
    abort();
  }

  // check if del_page is a single child of current_freq_node or not
  // in both cases we delete the exact page
  // numbering pages from the top
  *pages_in_cache -= 1;                    //counts objects in cache

  if (del_page->next == NULL) {
    lfu->freq_head->next = current_freq_node->next;
    free((freq_hash_t[frequency]).last);
    free((freq_hash_t[frequency]).first);
    (freq_hash_t[frequency]).length = 0;   //contains the number of pages in a frequency node
    free(del_page);
    free(current_freq_node);
  } else {
    del_page->next->prev = NULL;
    (freq_hash_t[frequency]).first = del_page->next;
    remove_page_in_hash_t(del_page->value, hash_t);
    free(del_page);
    (freq_hash_t[frequency]).length -= 1;
  }

  return;

}
