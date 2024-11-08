#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include "defines.h"
#include "cpu.h"

typedef void (*INSTRUCTION_HA)(cpu_t*, OPCODE*, uint8_t);

void push(cpu_t*, OPCODE* opcodes, uint8_t count);

#endif
