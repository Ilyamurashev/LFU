#ifndef DELETE_H_INCLUDED
#define DELETE_H_INCLUDED

#include <stdio.h>
#include <ctype.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

void remove(int key, struct page **freq_hash_t, struct freq_node **hash_t);

void delete_node(struct freq_node *node, struct page **freq_hash_t);

#endif // DELETE_H_INCLUDED
