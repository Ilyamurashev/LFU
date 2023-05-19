#include <stdlib.h>

// IN: the number of frequency = key, hash table of pages, lfu to get the size
// OUT: 1/0 equals true or false


struct freq_node {               //structure of frequency node
    int value;                   //frequency
    struct freq_node *next;
    struct freq_node *prev;
};

struct page {
    struct freq_node *parent;    //freq of  page
    struct page *next;           //next     page in list of freq_node
    struct page *prev;           //previous page in list of freq_node
    int value;                   //value of page
    struct page *next_hash;      //next     page in bucket of hash_t
    struct page *prev_hash;      //previous page in bucket of hash_t
};

struct bucket_freq_node {        //element of frequency hash table, index = frequency
    struct page *last;           //last page  in list of freq_node
    struct page *first;          //first page in list of freq_node
    int length;                  //length   of   list of freq_node
};

struct lfu_cache {
    struct page **hash_t;
    struct freq_node *freq_head;
    int size_hash_t;             //size of hash table
    int size_freq_hash_t;        //size of frequency hash table
};

//returns pointer to circle
struct if_page_exist(int key, struct page **hash_t){

  int index = get_page_hash(key);
  struct page *node = hash_t[index];
  while (node != NULL){
    if (node->value == key){
      break;
    }
    node = node->next;
  }
  return node;
}

// Cleaner is used to unload cache and delete the least
// used object - page, which is the closest to the head of freq_nodes.
// IN: lfu to get the head, hash table of frequency nodes, hash table of pages.
// OUT: 1/0 depends on success of the remove.

void cleaner(struct lfu_cache *lfu, struct page **hash_t,
             struct bucket_freq_node *freq_hash_t, int *pages_in_cache) {

  // get the required frequency node and page.
  
  struct freq_node *current_freq_node = (lfu->freq_head)->next;
  int frequency = current_freq_node->value;
  struct page *del_page = (freq_hash_t[frequency]).first;

  // check if page contains anything

  if (del_page == NULL) {
    fprintf(stderr, "Something went wrong. You are cleanining a non-existing object.\n");
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
    remove_page_ih_hash_t(del_page);
    free(del_page);
    (freq_hash_t[frequency]).length -= 1;
  }
  return;
}
