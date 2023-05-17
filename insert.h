/*!
  @file insert.h
  @brief Functions for inserting and adding pages or freq_nodes.
*/

#ifndef INSERT_H_INCLUDED
#define INSERT_H_INCLUDED

#include <stdio.h>
#include <ctype.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "struct.h"

/*!
  @brief function adds new page in hash table.

     @param [in] key            key         - value of page
     @param [in] hash_t         hash_t      - hash table of pages

     @param [out]
*/
struct page *add_page_in_hash_t(int key, struct page **hash_t);

/*!
  @brief function adds page in list of freq_node.

     @param [in] key            key         - value of page
     @param [in] last           last        - last page in list
     @param [in] parent         parent      - freq_node, which list will increase
     @param [in] freq_hash_t    freq_hash_t - array with info about freq_node's lists

*/
void add(int key, struct page *last, struct freq_node *parent,
        struct page **freq_hash_t);

/*!
  @brief function create new freq_node.

     @param [in] value          value       - value of frequency
     @param [in] prev           prev        - previous from the adding place
     @param [in] next           next        - next from the adding place
     @param [in] freq_hash_t    freq_hash_t - array with info about freq_node's lists

     @param [out] new_node      new_node    - pointer to new freq_node

*/
struct freq_node *get_new_node(int value, struct freq_node *prev,
                               struct freq_node *next, struct page **freq_hash_t);

/*!
  @brief function inserts new page in cache.

     @param [in] key            key         - value of page
     @param [in] freq_hash_t    freq_hash_t - array with info about freq_node's lists
     @param [in] hash_t         hash_t      - hash table of pages

*/
void insert(int key, struct page **freq_hash_t, struct freq_node **hash_t);

/*!
  @brief function move page to next frequency and count number of cache hits.

     @param [in] key            key         - value of page
     @param [in] freq_hash_t    freq_hash_t - array with info about freq_node's lists
     @param [in] hash_t         hash_t      - hash table of pages
     @param [in] cache_hit      cache_hit   - number of cache hits

*/
void access(int key, struct page **freq_hash_t, struct freq_node **hash_t, int *cache_hit);

#endif // INSERT_H_INCLUDED
