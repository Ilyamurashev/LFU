#include "struct.h"
#include "io.h"

void show_greetings()
{
    printf("An O(1) algorithm for implementing the LFU cache eviction scheme\n"
           "This program counts cache hits and compare LRU and LFU strategies \n"
           "Project created by Matvienko Mikhal, Murashev Ilya, Novomlinov Anton\n"
           "MIPT, 2023 \n");
    printf("Select the program operation mode:\n"
           "\"t\" - test   mode  \n"
           "\"c\" - close program\n");
}

bool get_input(char input_line[], int lim)
{
    int i = 0;
    int c = 0;

    for(i = 0; i < (lim - 1) && (c = getchar()) != EOF && c != '\n';) {
        input_line[i++] = (char)c;
    }

    if (i == lim - 1)
        return false;

    if (c == '\n')
        input_line[i++] = (char)c;
    input_line[i] = '\0';

    return true;
}

// return mode;
char check_selected_mode(char input_line[], int input_len)
{
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

bool get_test_file_name(char test_file_name[], int lim)
{
    int i = 0;
    int c = 0;

    printf("Enter the name of the test file\n");

    for (i = 0; isspace(c = getchar()); ++i)
        {}

    test_file_name[0] = (char)c;

    for(i = 1; (c = getchar()) != EOF && c != '\n';) {
        if (i >= lim - 1) {
            printf("too_long long!\n");
            return false;
        }

        if (isspace(c))
            break;

        test_file_name[i++] = (char)c;
    }
    test_file_name[i] = '\0';

    return true;
}
