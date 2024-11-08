#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#include "map.h"


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

