#ifndef CPU_H
#define CPU_H

#include <stdint.h>
#include "defines.h"

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
    EBX,
    ECX,
    EDX,
    ESI,
    EDI,
    REGISTERS_COUNT
} cpu_registers;

typedef struct
{
    cpu_register_t registers[REGISTERS_COUNT];

} cpu_t;

#endif
