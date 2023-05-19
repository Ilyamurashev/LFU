/*!
  @file io.hpp
  @brief Functions for greeting, inputing and outputing.
*/

#ifndef IO_H_INCLUDED
#define IO_H_INCLUDED

#include <errno.h>
#include <time.h>

#include "struct.h"

enum {          //for getting hash of page
  A = 257u,
  B = 519u,
  Power_hash = 19739u,   //Power of hash-table
};

/*!
  @brief function greetings user.
*/
void show_greetings(void);

/*!
  @brief function determines selected mod of program.

     @param [in] c                 c                 - symbol of mod
     @param [in] input_line[]      input_line[]      - entered data
     @param [in] input_len         input_len - length of entered data

*/
char check_selected_mode(char input_line[], int input_len);

/*!
  @brief function gets line.

     @param [in] input_line[]  input_line[] - entered data
     @param [in] lim           lim          - max length

*/
bool get_input(char input_line[], int lim);

/*!
  @brief function gets test file.

     @param [in] name_test_file  name_test_file - name of test file
     @param [in] lim             lim            - name's of test file max length
*/
bool get_test_file_name(char *test_file_name, int lim);

#endif // IO_H_INCLUDED