/*!
  @file delete.h
  @brief Functions for removing pages or freq_nodes.
*/

#ifndef DELETE_H_INCLUDED
#define DELETE_H_INCLUDED

#include <stdio.h>
#include <ctype.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "struct.h"

/*!
  @brief function removes page in hash table.

     @param [in] key            key         - value of page
     @param [in] hash_t         hash_t      - hash table of pages

*/
void remove_page_in_hash_t(int key, struct page **hash_t);

/*!
  @brief function adds new page in hash table.

     @param [in] key            key         - value of page
     @param [in] freq_hash_t    freq_hash_t - array with info about freq_node's lists
     @param [in] hash_t         hash_t      - hash table of pages

*/
void remove(int key, struct bucket_freq_node **freq_hash_t, struct page **hash_t);

/*!
  @brief function adds new page in hash table.

     @param [in] node           node        - freq_node which will deleted
     @param [in] freq_hash_t    freq_hash_t - array with info about freq_node's lists

*/
void delete_node(struct freq_node *node, struct page **freq_hash_t);

#endif // DELETE_H_INCLUDED
