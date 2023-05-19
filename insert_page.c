#include <stdio.h>
#include <stdlib.h>


struct page {
    struct freq_node *parent;
    struct page *next;
    struct page *prev;
    int value;
    struct page *next_hash;
    struct page *prev_hash;
};

//The function of inserting a new page


struct page *insert_page_in_hash_t(int key, struct page **hash_t){
    int id = 0;
    id = get_page_hash(key);
    struct page *ball;
    struct page *tp;
    tp = hash_t[id]->next;
    ball = (struct page *)calloc(1, sizeof(struct page));
    if(tp == NULL) tp = hash_t[id];
    //Insert
    while(tp->next != NULL){
        tp = tp->next;
        }
    tp->next = ball;      //
    ball->next = NULL;    //bandaging
    ball->prev = tp;      //

    return ball;
}
