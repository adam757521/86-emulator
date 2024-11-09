#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include "defines.h"
#include "cpu.h"
#include <stddef.h>

typedef void (*INSTRUCTION_HA)(cpu_t *, OPCODE *);

void push(cpu_t *, OPCODE *);
void pop(cpu_t *, OPCODE *);
void inc_32_16(cpu_t *, OPCODE *);
void dec_32_16(cpu_t *, OPCODE *);
void mov_r32_16_imm(cpu_t*, OPCODE*);

#endif
