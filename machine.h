#ifndef MACHINE_H
#define MACHINE_H

#include "defines.h"
#include "cpu.h"

void initialize_first_map();
void destruct_map_recursive();
void emulate_machine_code(cpu_t* cpu, OPCODE* codes);

#endif
