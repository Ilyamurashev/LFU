#include "struct.h"
#include "delete.h"
#include "insert.h"

//return pointer to new_page
//if first in bucket => its previous = NULL
struct page *add_page_in_hash_t(int key, struct page **hash_t)
{

}

//after removing and adding we need to update freq_hash_t
void update_freq_hash_t()
{

}

void fill_freq_hash_t(struct bucket_freq_node *freq_hash_t, struct page *first,
                    struct page *last, int length, int index) {

    assert(freq_hash_t && "freq_hash_t shall not be null");

    freq_hash_t[index]->first  = first;
    freq_hash_t[index]->last   = last;
    freq_hash_t[index]->length = length;

}

void create_head(struct lfu_cache *lfu_cache, struct bucket_freq_node *freq_hash_t) {

    assert(lfu_cache   &&   "lfu_cache shall not be null");
    assert(freq_hash_t && "freq_hash_t shall not be null");

    //freq_hash_t = (struct bucket_freq_node*)malloc(sizeof(struct bucket_freq_node*));
    //Ãäå âûäåëÿòü ïàìÿòü???
    struct freq_node head = (struct freq_node)malloc(sizeof(struct freq_node));
    if (head == NULL) abort();

    //head of list of freq_node
    head.next = &head;
    head.prev = &head;
    head.value = 0;

    fill_freq_hash_t(freq_hash_t, NULL, NULL, 0, 0);
    lfu_cache->freq_head = &head;

}

//last - last page in list of freq_node
void add(struct page *new_page, struct page *last, struct freq_node *parent,
        struct bucket_freq_node *freq_hash_t) {

    assert(parent      &&      "parent shall not be null");
    assert(new_page    &&    "new_page shall not be null");
    assert(freq_hash_t && "freq_hash_t shall not be null");

    int freq = -1;

    //change pointers of new page
    new_page->parent = parent;
    new_page->next = NULL;
    new_page->prev = last;
    if (last != NULL)
        last->next = new_page;

    freq = new_page->parent->value;               //new frequency

    if (freq_hash_t[freq]->first == NULL)
        freq_hash_t[freq]->first = new_page;      //change first in bucket if necessary
    freq_hash_t[freq]->last = new_page;           //change last  in bucket
    freq_hash_t[freq]->lenght += 1;               //increase length
}

struct freq_node *get_new_node(int value, struct freq_node *prev,
                               struct freq_node *next, struct lfu_cache *lfu_cache,
                               struct bucket_freq_node *freq_hash_t) {

    assert(prev        &&        "prev shall not be null");
    assert(lfu_cache   &&   "lfu_cache shall not be null");
    assert(freq_hash_t && "freq_hash_t shall not be null");

    struct freq_node *new_node;

    //creating and initialization
    new_node = (struct freq_node*)malloc(sizeof(struct freq_node));
    if (new_node == NULL) abort();

    new_node->next = next;
    new_node->prev = prev;
    prev->next = new_node;
    if (next != NULL)
        next->prev = new_node;
    new_node->value = value;

    //checking size of frequency hash table
    //and expands if necessary
    //ÏÐÀÂÈËÜÍÎ ÍÀÏÈÑÀÒÜ ÐÅÀËËÎÊ
    if (value > lfu_cache->size_freq_hash_t) {
        freq_hash_t = (struct bucket_freq_node*)realloc(freq_hash_t, (value+1)*sizeof(struct bucket_freq_node));
        lfu_cache->size_freq_hash_t = value+1;
    }

    fill_freq_hash_t(freq_hash_t, NULL, NULL, 0, value);

    return new_node;
}

void insert(int key, const struct bucket_freq_node *freq_hash_t,
            const struct page **hash_t, int *pages_in_cache) {

    assert(hash_t         &&         "hash_t shall not be null");
    assert(freq_hash_t    &&    "freq_hash_t shall not be null");
    assert(pages_in_cache && "pages_in_cache shall not be null");

    struct freq_node *freq_n;
    struct page *old_last;      //last page in list of freq_node before adding
    struct page *new_page;

    if (key not in hash_t) {    //checking
        *pages_in_cache += 1;   //new page => increase their number
        new_page = add_page_in_hash_t(key, hash_t);
        freq_n = lfu_cache->freq_head->next;

        if (freq_n->value == 0)
            freq_n = get_new_node(1, lfu_cache->freq_head, NULL,   freq_hash_t);    //if only head => creates freq_node with value = 1
        else if (freq_n->value != 1)
            freq_n = get_new_node(1, lfu_cache->freq_head, freq_n, freq_hash_t);  //creates freq_node with value = 1

        old_last = freq_hash_t[1]->last;
        add(new_page, freq_hash_t[1]->last, freq_n, freq_hash_t);    //add page in list of freq_node

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
void access(int key, const struct bucket_freq_node *freq_hash_t,
            const struct page **hash_t, int *cache_hit) {

    assert(hash_t      &&      "hash_t shall not be null");
    assert(cache_hit   &&   "cache_hit shall not be null");
    assert(freq_hash_t && "freq_hash_t shall not be null");

    struct page *get_page;

    if (get_page = key in hash_t) {        //checking
        *cache_hit += 1;
        struct freq_node *freq_n = get_page->parent;

        if (freq_n->next != NULL) {
            struct freq_node *next_freq_n = freq_n->next;

            //if it head or not 1
            if (next_freq_n == lfu_cache.freq_head or next_freq_n->value != (1 + freq_n->value)) {
                next_freq_n = get_new_node(freq_n->value + 1, freq_n, next_freq_n);
            }

        } else { //if freq_node is last el in list
            next_freq_n = get_new_node(freq_n->value + 1, freq_n, freq_n->next);
        }

        //remove from old frequency
        remove(get_page, freq_hash_t, hash_t);

        //add to new frequency node
        add(get_page, freq_hash_t[get_page->parent->next->value]->last,
           next_freq_n, freq_hash_t);
    }
}
