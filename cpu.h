#ifndef DEFINES_H
#define DEFINES_H

#include <stdint.h>
#include "defines.h"

typedef union
{
    uint8_t low;
    uint16_t word;
    uint32_t dword;
} cpu_register_t;

#define LOW_BYTE(reg) reg.low
#define HIGH_BYTE(reg) (reg.word ^ reg.low) >> 8
#define CHANGE_HIGH_BYTE(reg, high)                   \
    {                                                 \
        reg.word = (reg.word & 0x00FF) | (high << 8); \
    }

#endif
