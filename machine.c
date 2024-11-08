#include <stdint.h>
#include <stdlib.h>

#include "instruction.h"

typedef struct {
    void* ptr;
    int is_map;
} entry_t;

static entry_t *entries[256] = {0};

void initialize_first_map() {
    for (uint8_t start = 0x50; start < 0x58; start++) {
        entry_t* entry = malloc(sizeof(entry_t));
        entry->ptr = push;
        entry->is_map = 0;

        entries[start] = entry;
    }
}

void destruct_map_recursive() {
    for (uint8_t start = 0x0; start < 0xff; start++) {
        entry_t* e = entries[start];
        if (e != 0) {
            free(e);
        }
    }
}
