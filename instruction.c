#include "instruction.h"
#include <stdio.h>
#include <memory.h>

void push(cpu_t *cpu, OPCODE *opcodes)
{
    BYTE register_ = opcodes[cpu->ip] - 0x50;
    cpu_register_t *reg = &cpu->gp_registers[register_];

    DWORD *esp = &cpu->gp_registers[ESP].dword;
    *esp -= 4;
    memcpy(&cpu->memory[*esp], &reg->dword, 4);
}

void pop(cpu_t *cpu, OPCODE *opcodes)
{
    BYTE register_ = opcodes[cpu->ip] - 0x58;
    cpu_register_t *reg = &cpu->gp_registers[register_];

    DWORD *esp = &cpu->gp_registers[ESP].dword;
    memcpy(&reg->dword, &cpu->memory[*esp], 4);
    *esp += 4;
}

void inc(cpu_t *cpu, OPCODE *opcodes)
{
    BYTE register_ = opcodes[cpu->ip] - 0x40;
    cpu->gp_registers[register_].dword++;
}

void dec(cpu_t *cpu, OPCODE *opcodes)
{
    BYTE register_ = opcodes[cpu->ip] - 0x48;
    cpu->gp_registers[register_].dword--;
}