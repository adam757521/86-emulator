#include <stdint.h>
#include <stdlib.h>

#include "instruction.h"

typedef struct {
    void* ptr;
    int is_map;
} entry_t;

static entry_t *entries[256] = {0};

void initialize_first_map() {
    entry_t* entry = malloc(sizeof(entry_t));
    for (uint8_t start = 0x50; start < 0x58; start++) {
        entry->ptr = push;
        entry->is_map = 0;

        entries[start] = entry;
    }
}

void emulate_machine_code(cpu_t* cpu, OPCODE* codes) {
    entry_t* mapping = entries[codes[0]];
    if (mapping == NULL) {
        return;
    }
    
    INSTRUCTION_HA thing = (INSTRUCTION_HA)mapping->ptr;
    thing(cpu, codes, 1);
}

void destruct_map_recursive() {
    // All push entries
    free(entries[0x50]);
}
