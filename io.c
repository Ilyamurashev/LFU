#include "struct.h"
#include "io.h"

void show_greetings() {

    printf("An O(1) algorithm for implementing the LFU cache eviction scheme\n"
           "This program counts cache hits and compare LRU and LFU strategies \n"
           "Project created by Matvienko Mikhal, Murashev Ilya, Novomlinov Anton\n"
           "MIPT, 2023 \n");
    printf("Select the program operation mode:\n"
           "\"t\" - test  mode  \n"
           "\"c\" - close program\n");
}

int get_input(char *input_line, int lim) {
    int i = 0;
    int c = 0;

    for(i = 0; i < (lim - 1) && (c = getchar()) != EOF && c != '\n';) {
        input_line[i++] = (char)c;
    }

    if (i == lim - 1)
        return 0;

    if (c == '\n')
        input_line[i++] = (char)c;
    input_line[i] = '\0';

    return 1;
}

// return mode;
char check_selected_mode(char *input_line, int input_len) {
    int i = 0;
    int j = 0;

    for (i = 0; isspace(input_line[i]); i++)
        {}

    i++;
    j = i;   // here index of symbol
    for (; isspace(input_line[i]) && i < input_len; i++)
        {}

    if (i == input_len)
        return input_line[j-1];

    return 0;
}

int get_test_file_name(char test_file_name[], int lim) {
    int i = 0;
    int c = 0;

    printf("Enter the name of the test file\n");

    //miss spaces
    for (i = 0; isspace(c = getchar()); ++i)
        {}

    test_file_name[0] = (char)c;

    for(i = 1; (c = getchar()) != EOF && c != '\n';) {
        if (i >= lim - 1) {
            printf("too_long long!\n");
            return 0;
        }

        if (isspace(c))
            break;

        test_file_name[i++] = (char)c;
    }
    test_file_name[i] = '\0';

    return 1;
}

int get_page_hash(int key) {
    return (A * key + B) % Power_hash;
}

void check_data_input(int read_page, int check_arg) {

    assert(check_arg > 0);   //check_arg - positive integer
    assert(read_page == 1);
    assert(read_page != EOF);
}

void error_message() {

    fprintf(stderr, "%s\n", strerror(errno));
    fprintf(stderr, "ERROR_LINE %d\n", __LINE__);
    fprintf(stderr, "ERROR_FILE %s\n", __FILE__);
    abort();

}

struct page* if_page_exist(int key, struct page **hash_t) {

    int index = get_page_hash(key);
    //printf("!! %d\n", &(hash_t));

    if (hash_t[index] == NULL) {
    //printf("%d\n", &(hash_t[index]));
    return NULL;
    }

    struct page *node = hash_t[index];
    while (node != NULL){
        if (node->value == key){
            break;
        }
        node = node->next;
    }

    return node;
}

int check_key(int key, struct page* page) {
    if(key == page->value) return 1;
    else return 0;
}
