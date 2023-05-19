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
    char input_line[MAX_LEN] = {};

    // для хранения времени выполнения кода
    double time_spent = 0.0;

    clock_t begin_time = clock();

    show_greetings();

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

    clock_t end_time = clock();

    //calculate the elapsed time by finding the difference (end_time - begin_time)
    //dividing the difference by CLOCKS_PER_SEC to convert to seconds
    time_spent += (double)(end_time - begin_time) / CLOCKS_PER_SEC;

    printf("The elapsed time is %f seconds\n", time_spent);

    return 0;
}

