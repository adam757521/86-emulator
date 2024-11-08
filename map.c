#include "map.h"

#include <stdlib.h>

entry_t *entries[256] = {0};

entry_t* get_push_handler() {
    handler_t* handler = malloc(sizeof(handler_t));
    handler->handler = push;
    handler->consumed_opcodes = 1;

    entry_t* entry = malloc(sizeof(entry_t));
    entry->ptr = handler;
    entry->is_map = 0;
    
    return entry;
}

entry_t* get_pop_handler() {
    handler_t* pop_handler = malloc(sizeof(handler_t));
    pop_handler->handler = pop;
    pop_handler->consumed_opcodes = 1;

    entry_t* entry_pop = malloc(sizeof(entry_t));
    entry_pop->ptr = pop_handler;
    entry_pop->is_map = 0;

    return entry_pop;
}

void initialize_first_map() {
    entry_t* push_h = get_push_handler();
    for (uint8_t start = 0x50; start < 0x58; start++) {
        entries[start] = push_h;
    }

    entry_t* pop_h = get_pop_handler();
    for (uint8_t start = 0x58; start < 0x60; start++) {
        entries[start] = pop_h;
    }
}

void destruct_map_recursive() {
    free(entries[0x50]->ptr);
    free(entries[0x50]);
    free(entries[0x58]->ptr);
    free(entries[0x58]);
}
