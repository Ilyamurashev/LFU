#include <stdio.h>
#include <stdlib.h>

#include "struct.h"
#include "delete.h"
#include "insert.h"
#include "io.h"
#include "test.h"

int main()
{
    const int MAX_LEN = 100;

    char mode = 0;
    int  input_len = 0;
    char *input_line;  //?

    show_greetings();
    input_line = (char*)calloc(MAX_LEN, sizeof(char));

    //get mode of working
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
            case 't':           //testing mode
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

    free(input_line);

    return 0;
}

