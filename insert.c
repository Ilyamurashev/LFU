#include "struct.h"
#include "delete.h"
#include "insert.h"

//return pointer to new_page
//if first in bucket => its previous = NULL
struct page *add_page_in_hash_t(int key, struct page **hash_t) {

    assert(hash_t && "hash_t shall not be null");

    int id = 0;
    struct page *new_page;
    struct page *tp;

    id = get_page_hash(key);
    new_page = (struct page *)calloc(1, sizeof(struct page));
    if (new_page== NULL) error_message();
    tp = (struct page *)calloc(1, sizeof(struct page));
    if (new_page== NULL) error_message();

    new_page->next_hash = NULL;
    new_page->prev_hash = NULL;
    new_page->value     = key;

    if (hash_t[id] == NULL) {
        hash_t[id] = new_page;
        free(tp);
        free(new_page);
        return hash_t[id];
    }

    tp = hash_t[id]->next_hash;

    if (tp == NULL) tp = hash_t[id];

    //Insert
    while(tp->next != NULL){
        tp = tp->next_hash;
        }
    tp->next_hash = new_page;      //
    new_page->next_hash = NULL;    //bandaging
    new_page->prev_hash = tp;      //

    return new_page;
}

/*
//after removing and adding we need to update freq_hash_t
void update_freq_hash_t()
{

}
*/

void fill_freq_hash_t(struct bucket_freq_node **freq_hash_t, struct page *first,
                    struct page *last, int length, int index) {

    assert(freq_hash_t && "freq_hash_t shall not be null");

    freq_hash_t[index] = (struct bucket_freq_node*)malloc(sizeof(struct bucket_freq_node));
    if (freq_hash_t[index] == NULL) error_message();

    (*(freq_hash_t)[index]).first  = first;
    (*(freq_hash_t)[index]).last   = last;
    (*(freq_hash_t)[index]).length = length;
    printf("22HERE! %d\n", freq_hash_t[1]->length);

}

void create_lfu_cache(struct lfu_cache **lfu_cache, struct page ***hash_t,
                      int amount_of_pages) {

    *lfu_cache = (struct lfu_cache*)calloc(1, sizeof(struct lfu_cache));
    if (*lfu_cache == NULL) error_message();
    //printf("address %d\n", &lfu_cache);

    *hash_t = (struct page **)calloc(Power_hash, sizeof(struct page *));
    if (*hash_t == NULL) error_message();

    (*lfu_cache)->hash_t = *hash_t;
    (*lfu_cache)->freq_head = NULL;

}

void create_head(struct lfu_cache *lfu_cache,
                 struct bucket_freq_node **freq_hash_t, int amount_of_pages) {

    assert(lfu_cache   &&   "lfu_cache shall not be null");
    //assert(*freq_hash_t && "freq_hash_t shall not be null");

    int size_freq_hash_t = amount_of_pages/2;

    *freq_hash_t = (struct bucket_freq_node*)calloc(size_freq_hash_t, sizeof(struct bucket_freq_node));
    if (*freq_hash_t == NULL) error_message();

    struct freq_node *head = (struct freq_node*)malloc(sizeof(struct freq_node));
    if (head == NULL) error_message();

    //head of list of freq_node
    head->next = head;
    head->prev = head;
    head->value = 0;

    fill_freq_hash_t(freq_hash_t, NULL, NULL, 0, 0);
    lfu_cache->freq_head = head;
    lfu_cache->size_freq_hash_t = size_freq_hash_t;

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

    if (freq_hash_t[freq].first == NULL)
        freq_hash_t[freq].first = new_page;      //change first in bucket if necessary
    freq_hash_t[freq].last = new_page;           //change last  in bucket
    freq_hash_t[freq].length += 1;               //increase length
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
    if (new_node == NULL) error_message();

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

    fill_freq_hash_t(&freq_hash_t, NULL, NULL, 17, value);
    printf("33HERE! %d\n", freq_hash_t[1].length);

    return new_node;
}

void insert(int key, struct bucket_freq_node *freq_hash_t,
            struct page **hash_t, int *pages_in_cache, struct lfu_cache *lfu_cache) {

    assert(hash_t         &&         "hash_t shall not be null");
    assert(freq_hash_t    &&    "freq_hash_t shall not be null");
    assert(pages_in_cache && "pages_in_cache shall not be null");

    struct freq_node *freq_n = (struct freq_node *)calloc(1, sizeof(struct freq_node));
    struct page *old_last = (struct page *)calloc(1, sizeof(struct page)); //last page in list of freq_node before adding
    struct page *new_page = (struct page *)calloc(1, sizeof(struct page));

    *pages_in_cache += 1;       //new page => increase its number
    new_page = add_page_in_hash_t(key, hash_t);
    //printf("HERE! %d\n", hash_t[get_page_hash(key)]->value);
    freq_n = lfu_cache->freq_head->next;

    if (freq_n->value == 0)     //if head
        freq_n = get_new_node(1, lfu_cache->freq_head, NULL,   lfu_cache, freq_hash_t); //if only head => creates freq_node with value = 1
    else if (freq_n->value != 1)
        freq_n = get_new_node(1, lfu_cache->freq_head, freq_n, lfu_cache, freq_hash_t); //creates freq_node with value = 1
    printf("HERE!\n");
    printf("33HERE! %d\n", freq_hash_t[1].length);
    //fill_freq_hash_t(freq_hash_t, struct page *first, struct page *last, int length, int index);
    old_last = freq_hash_t[1].last;
    add(new_page, old_last, freq_n, freq_hash_t);    //add page in list of freq_node

    free(old_last);
    free(new_page);

}

//move page to next freq_node
//and if necessary creates new freq_node
void access(struct page *get_page, struct bucket_freq_node *freq_hash_t,
            int *cache_hit, struct lfu_cache *lfu_cache) {

    //assert(hash_t      &&      "hash_t shall not be null");
    assert(cache_hit   &&   "cache_hit shall not be null");
    assert(freq_hash_t && "freq_hash_t shall not be null");

    struct freq_node *next_freq_n;

    *cache_hit += 1;
    struct freq_node *freq_n = get_page->parent;

    if (freq_n->next != NULL) {
        struct freq_node *next_freq_n = freq_n->next;

        //if it head or freq != 1
        if (next_freq_n == lfu_cache->freq_head || next_freq_n->value != (1 + freq_n->value)) {
            next_freq_n = get_new_node(freq_n->value + 1, freq_n, next_freq_n, lfu_cache, freq_hash_t);
        }

    } else { //if freq_node is last el in list
        next_freq_n = get_new_node(freq_n->value + 1, freq_n, freq_n->next, lfu_cache, freq_hash_t);
    }

    //remove from old frequency
    remove_page_in_freq_hash_t(get_page, freq_hash_t);

    //add to new frequency node
    add(get_page, freq_hash_t[get_page->parent->next->value].last,
       next_freq_n, freq_hash_t);

}
