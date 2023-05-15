
//IN: the number of frequency = key, hash table of pages, lfu to get the size
//OUT: 1/0 equals true or false

int if_in_hash(int key, struct page **hash_t, struct lfu_cache lfu){
    int lenght = lfu.size_hash_t;
    //If it is possible(the size is appropriae) to get data from hash_table returns 1 = True
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
            struct page *del_node = (freq_hash_t[frequency])->first;

            //check if page contains anything

            if (del_page == NULL) {
                printf("Something went wrong. You are cleanining a non-existing object.");
                return 0;
             }

             //check if del_node is a single child of current_freq_node or not
             //in both cases we delete the exact page

             if (del_page->prev == NULL){
                lfu.freq_head->next = current_freq_node->next;
                free(del_node);
                free(current_freq_node);
             }
             else{
                del_node->prev->next = del_node->next;
                free(del_node);
             }
             return 1;
}