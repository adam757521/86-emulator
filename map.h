#ifndef MAP_H
#define MAP_H

#include "instruction.h"

typedef struct {
    void* ptr;
    int is_map;
} entry_t;

extern entry_t* entries[256];

void initialize_first_map();
void destruct_map_recursive();

#endif
