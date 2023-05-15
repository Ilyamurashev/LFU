
//IN: the number of frequency = key, hash table of pages, lfu to get the size
//OUT: 1/0 equals true or false

int if_in_hash(int key, struct page **hash_t, struct lfu_cache lfu){
    int lenght = lfu.size_hash_t;
    //If it is possible(the size is appropriate) to get data from hash_table returns 1 = True
    if (key < lenght){
        if (hash_t[key] != NULL) return 1;
    }
    //if not returns 0 = false
    return 0;
}

//Cleaner is used to unload cache and delete the least
//used object - page, which is the closest to the head of freq_nodes.
//IN: lfu to get the head, hash table of frequency nodes, hash table of pages.
//OUT: 1/0 depends on success of the remove.

void cleaner(struct lfu cache lfu, struct page **hash_t, 
            struct bucket_freq_node **freq_hash_t){

            //get the required frequency node and page.

            struct freq_node *current_freq_node = (lfu.freq_head)->next;
            frequency = current_freq_node->value
            struct page *del_page = (freq_hash_t[frequency])->first;

            //check if page contains anything

            if (del_page == NULL) {
                printf("Something went wrong. You are cleanining a non-existing object.");
                return 0;
             }

             //check if del_page is a single child of current_freq_node or not
             //in both cases we delete the exact page
             //numbering pages from the top

             if (del_page->next == NULL){
                lfu.freq_head->next = current_freq_node->next;
                freq_hash_t[frequency] = NULL;
                free(del_page);
                free(current_freq_node);
             }
             else{
                del_page->next->prev = NULL;
                freq_hash_t[frequency] = del_page->next;
                free(del_page);
             }
             return 1;
}

