#ifndef CPU_H
#define CPU_H

#include <stdint.h>
#include "defines.h"

#define MEMORY_SIZE 1 * KB

typedef union
{
    BYTE low;
    WORD word;
    DWORD dword;
} cpu_register_t;

#define LOW_BYTE(reg) reg.low
#define HIGH_BYTE(reg) (reg.word ^ reg.low) >> 8
#define CHANGE_HIGH_BYTE(reg, high)                   \
    {                                                 \
        reg.word = (reg.word & 0x00FF) | (high << 8); \
    }

typedef enum
{
    EAX,
    ECX,
    EDX,
    EBX,
    ESP,
    EBP,
    ESI,
    EDI,
    REGISTERS_COUNT
} cpu_registers;

typedef struct
{
    cpu_register_t gp_registers[REGISTERS_COUNT];
    DWORD ip;
    BYTE memory[MEMORY_SIZE];
} cpu_t;

#endif
