#include "struct.h"
#include "delete.h"
#include "insert.h"
#include "io.h"
#include "test.h"

const int MAX_LEN = 100;
const int File_error = 1;
static const char WARNING_ERROR[] = "ERROR: an error occurred while trying to get file data.";

int test_lfu() {

    int *cache_hit;      //number of cache hits
    int *pages_in_cache; //number of different pages
    int *size_cache;     //from file

    int key_page;        //keys of pages
    int amount_of_pages; //amount of pages in file

    struct page **hash_t = NULL;
    struct lfu_cache *lfu_cache = NULL;
    struct bucket_freq_node *freq_hash_t = NULL; //index = frequency

    char test_file_name[MAX_LEN] = {};

    amount_of_pages = 0
    *(pages_in_cache) = 0;
    *(cache_hit) = 0;

    get_test_file_name(test_file_name, MAX_LEN);

    FILE *test_file = NULL;
    if ((test_file = fopen(test_file_name, "r")) == NULL) {
        fprintf(stderr, "ERROR: failed to open file %s: %s\n", test_file_name, strerror(errno));
        fprintf(stderr, "ERROR_LINE %d\n", __LINE__);
        return File_error;
    }

    //here program reads data from test_file and begins work

    //read from file size of cache
    check_inputting = fscanf(test_file, "%d", size_cache);
    check_data_input(check_inputting, *size_cache);

    //read from file amount of pages
    check_inputting = fscanf(test_file, "%d", &amount_of_pages);
    check_data_input(check_inputting, amount_of_pages);

    //crate struct lfu_cache
    create_lfu_cache(lfu_cache, hash_t, amount_of_pages);

    //create head of list of frequency nodes
    create_head(lfu_cache, freq_hash_t, amount_of_pages);

    //read from file of page's key and sent it to cache
    for (int i = 0; i < amount_of_pages; ++i) {
        check_inputting = fscanf(test_file, "%d", &key_page);
        check_data_input(check_inputting, key_page);

        struct page *find_result = if_in_hash(key_page, hash_t);
        if (find_result == NULL) {
            if (*(pages_in_cache) > size_cache) {
                fprintf(stderr, "ERROR: the cache is overflowing\n");
                fprintf(stderr, "ERROR_LINE %d\n", __LINE__);
                abort();
            }
            if (*(pages_in_cache) == size_cache)
                cleaner(lfu_cache, hash_t, freq_hash_t, pages_in_cache);
            insert(key_page, freq_hash_t, hash_t, pages_in_cache);

        } else
            access(find_result, freq_hash_t, hash_t, cache_hit);
    }

    printf("cache_hits: %d\n", *(cache_hit));

    if (fclose(test_file) != 0) {
        fprintf(stderr, "ERROR: failed to close file %s: %s\n", test_file_name, strerror(errno));
        fprintf(stderr, "ERROR_LINE %d\n", __LINE__);
        return File_error;
    }

    return 0;
}

