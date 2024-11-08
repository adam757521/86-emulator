#ifndef MACHINE_H
#define MACHINE_H

#include "defines.h"
#include "cpu.h"
#include <stddef.h>

void initialize_first_map();
void destruct_map_recursive();
int emulate_machine_code(cpu_t* cpu, OPCODE* opcodes, size_t opcodes_size);

#endif
