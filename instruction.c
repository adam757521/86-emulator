#include "instruction.h"
#include <memory.h>

void push(cpu_t *cpu, OPCODE *start)
{
    BYTE register_ = start[0] - 0x50;
    cpu_register_t *reg = &cpu->gp_registers[register_];

    DWORD *esp = &cpu->gp_registers[ESP].dword;
    *esp -= 4;
    memcpy(&cpu->memory[*esp], &reg->dword, 4);
}

void pop(cpu_t *cpu, OPCODE *start)
{
    BYTE register_ = start[0] - 0x58;
    cpu_register_t *reg = &cpu->gp_registers[register_];

    DWORD *esp = &cpu->gp_registers[ESP].dword;
    memcpy(&reg->dword, &cpu->memory[*esp], 4);
    *esp += 4;
}

void inc_32_16(cpu_t *cpu, OPCODE *start)
{
    // TODO: add support to 66 and multi opcode
    // ALU
    BYTE register_ = start[0] - 0x40;
    cpu->gp_registers[register_].dword++;
}

void dec_32_16(cpu_t *cpu, OPCODE *start)
{
    BYTE register_ = start[0] - 0x48;
    cpu->gp_registers[register_].dword--;
}

void mov_r32_imm(cpu_t* cpu, OPCODE *opcodes) {

}

void mov_r16_imm(cpu_t* cpu, OPCODE *opcodes) {

}
