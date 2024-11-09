#ifndef MACHINE_H
#define MACHINE_H

#include "defines.h"
#include "cpu.h"
#include <stddef.h>

int emulate_machine_code(cpu_t* cpu, OPCODE* opcodes, size_t opcodes_size);

#endif
