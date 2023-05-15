#include <stdio.h>
#include <stdlib.h>

#include "delete.h"
#include "insert.h"
#include "io.h"
#include "test.h"

int main()
{
    const int MAX_LEN = 100;               //the limit of elements(= data) in program

    int *cache_hit;                        //counter of cash hits    
    struct page **hash_t;                  //hash table of data. index of element = value
    struct bucket_freq_node **freq_hash_t; //index = frequency

    int  input_len = 0;
    char input_line[MAX_LEN] = {};

    *(cache_hit) = 0;

    show_greetings();

    char mode = 0;

    while (!mode) {

        while (!(get_input(input_line, MAX_LEN))) {
            printf("Too long! Try again.\n");
            while (getchar() != '\n')
                {}
        }

        input_len = strlen(input_line);

        mode = check_selected_mode(input_line, input_len);

        switch (mode)
        {
            case 't':
                if(test_lfu())
                    printf("Test aborted!!!\n");
                break;
            case 'c':
                break;
            default:
                printf("Wrong data format entered!\n");
                break;
        }

    }

    return 0;
}

