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
#include "io.h"

/*!
  @brief function removes page in hash table.

     @param [in] key            key         - value of page
     @param [in] hash_t         hash_t      - hash table of pages

*/
void remove_page_in_hash_t(int key, struct page **hash_t);

/*!
  @brief function adds new page in hash table.

     @param [in] node           node        - freq_node which will deleted
     @param [in] freq_hash_t    freq_hash_t - array with info about freq_node's lists

*/
void delete_node(struct freq_node *node, struct bucket_freq_node *freq_hash_t);

/*!
  @brief function adds new page in hash table.

     @param [in] del_page       del_page    - removed page in cache
     @param [in] freq_hash_t    freq_hash_t - array with info about freq_node's lists
     @param [in] hash_t         hash_t      - hash table of pages

*/
void remove_page_in_freq_hash_t(struct page *del_page, struct bucket_freq_node *freq_hash_t);

void cleaner(struct lfu_cache *lfu, struct page **hash_t,
             struct bucket_freq_node *freq_hash_t, int *pages_in_cache);

#endif // DELETE_H_INCLUDED
