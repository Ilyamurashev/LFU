#include "struct.h"
#include "delete.h"
#include "insert.h"
#include "io.h"
#include "test.h"

const int MAX_LEN = 100;
static const char WARNING_ERROR[] = "ERROR: an error occurred while trying to get file data.";

int test_lfu() {

    char test_file_name[MAX_LEN] = {};

    get_test_file_name(test_file_name, MAX_LEN);

    FILE *test_file = NULL;
    if ((test_file = fopen(test_file_name, "r")) == NULL) {
        printf("ERROR: failed to open file %s\n", test_file_name);
        return 1;
    }

    //here program reads data from test_file and begins work

}

