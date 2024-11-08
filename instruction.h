#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include "defines.h"
#include "cpu.h"
#include <stddef.h>

typedef void (*INSTRUCTION_HA)(cpu_t *, OPCODE *);

typedef struct
{
    INSTRUCTION_HA handler;
    size_t consumed_opcodes;
} handler_t;

void push(cpu_t *, OPCODE *opcodes);
void pop(cpu_t *, OPCODE *opcodes);
void inc(cpu_t *, OPCODE *);
void dec(cpu_t *, OPCODE *);

#endif
