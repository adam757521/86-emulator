#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#include "map.h"

int emulate_machine_code(cpu_t* cpu, OPCODE* opcodes, size_t opcodes_size) {
    if (opcodes_size <= cpu->ip) {
        return 2;
    }

    entry_t** entries_ptr = entries;
    DWORD start = cpu->ip;
    for (;; cpu->ip++) {
        entry_t* e = entries_ptr[opcodes[cpu->ip]];
        if (e == NULL) {
            return 1;
        }

        if (e->is_map) {
            entries_ptr = e->ptr;
            if (entries_ptr == NULL) {
                return 1;
            }
        } else {
            handler_t* handler = (handler_t*)e->ptr;
            if (opcodes_size - cpu->ip < handler->consumed_opcodes) {
                return 1;
            }

            handler->handler(cpu, &opcodes[start]);
            cpu->ip += handler->consumed_opcodes;
            return 0;
        }
    }
}

