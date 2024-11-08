#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#include "instruction.h"

typedef struct {
    void* ptr;
    int is_map;
} entry_t;

static entry_t *entries[256] = {0};

void initialize_first_map() {
    handler_t* handler = malloc(sizeof(handler_t));
    handler->handler = push;
    handler->consumed_opcodes = 1;

    entry_t* entry = malloc(sizeof(entry_t));
    for (uint8_t start = 0x50; start < 0x58; start++) {
        entry->ptr = handler;
        entry->is_map = 0;

        entries[start] = entry;
    }

    handler_t* pop_handler = malloc(sizeof(handler_t));
    pop_handler->handler = pop;
    pop_handler->consumed_opcodes = 1;

    entry_t* entry_pop = malloc(sizeof(entry_t));
    for (uint8_t start = 0x58; start < 0x60; start++) {
        entry_pop->ptr = pop_handler;
        entry_pop->is_map = 0;

        entries[start] = entry_pop;
    }
}

int emulate_machine_code(cpu_t* cpu, OPCODE* opcodes, size_t opcodes_size) {
    if (opcodes_size <= cpu->ip) {
        return 2;
    }

    entry_t* mapping = entries[opcodes[cpu->ip]];
    if (mapping == NULL) {
        return 1;
    }

    handler_t* handler = (handler_t*)mapping->ptr;
    if (opcodes_size - cpu->ip < handler->consumed_opcodes) {
        return 1;
    }

    handler->handler(cpu, opcodes);
    cpu->ip += handler->consumed_opcodes;
    return 0;
}

void destruct_map_recursive() {
    // All push entries
    free(entries[0x50]->ptr);
    free(entries[0x50]);
    free(entries[0x58]->ptr);
    free(entries[0x58]);
}
