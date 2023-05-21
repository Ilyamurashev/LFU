/*!
  @file struct.h
  @brief Structures.
*/

#ifndef STRUCT_H_INCLUDED
#define STRUCT_H_INCLUDED

#include<stdio.h>

struct freq_node {               //structure of frequency node
    int value;                   //frequency
    struct freq_node *next;
    struct freq_node *prev;
};

struct page {
    struct freq_node *parent;    //freq of  page
    struct page *next;           //next     page in list of freq_node
    struct page *prev;           //previous page in list of freq_node
    int value;                   //value of page
    struct page *next_hash;      //next     page in bucket of hash_t
    struct page *prev_hash;      //previous page in bucket of hash_t
};

struct bucket_freq_node {        //element of frequency hash table, index = frequency
    struct page *last;           //last page  in list of freq_node
    struct page *first;          //first page in list of freq_node
    int length;                  //length   of   list of freq_node
};

struct lfu_cache {
    struct page **hash_t;
    struct freq_node *freq_head;
    int size_freq_hash_t;        //size of frequency hash table
};

#endif // STRUCT_H_INCLUDED
