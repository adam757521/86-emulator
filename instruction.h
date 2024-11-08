#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include "defines.h"

typedef void (*INSTRUCTION_HA)(OPCODE*, uint8_t);

void push(OPCODE* opcodes, uint8_t count);

#endif
