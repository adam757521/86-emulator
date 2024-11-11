#include "instruction.h"
#include <memory.h>
#include <stdio.h>

void push_32(cpu_t *cpu, OPCODE *start)
{
    BYTE register_ = start[0] - 0x50;
    cpu_register_t *reg = &cpu->gp_registers[register_];

    DWORD *esp = &cpu->gp_registers[ESP].dword;
    *esp -= 4;
    memcpy(&cpu->memory[*esp], &reg->dword, 4);
}

void push_16(cpu_t* cpu, OPCODE *start) 
{
    BYTE register_ = start[1] - 0x50;
    cpu_register_t* reg = &cpu->gp_registers[register_];
    
    DWORD *esp = &cpu->gp_registers[ESP].dword;
    *esp -= 2;
    memcpy(&cpu->memory[*esp], &reg->word, 2);
}

void pop_32(cpu_t *cpu, OPCODE *start)
{
    BYTE register_ = start[0] - 0x58;
    cpu_register_t *reg = &cpu->gp_registers[register_];

    DWORD *esp = &cpu->gp_registers[ESP].dword;
    memcpy(&reg->dword, &cpu->memory[*esp], 4);
    *esp += 4;
}

void pop_16(cpu_t *cpu, OPCODE *start)
{
    BYTE register_ = start[1] - 0x58;
    cpu_register_t *reg = &cpu->gp_registers[register_];

    DWORD *esp = &cpu->gp_registers[ESP].dword;
    memcpy(&reg->word, &cpu->memory[*esp], 2);
    *esp += 2;
}

void inc_32_16(cpu_t *cpu, OPCODE *start)
{
    BYTE is_operand_override = start[0] == 0x66;
    cpu_register_t* reg = &cpu->gp_registers[start[is_operand_override] - 0x40];
    
    if (is_operand_override) {
        reg->word++;
    } else {
        reg->dword++;
    }
}

void dec_32_16(cpu_t *cpu, OPCODE *start)
{
    BYTE is_operand_override = start[0] == 0x66;
    cpu_register_t* reg = &cpu->gp_registers[start[is_operand_override] - 0x48];
    
    if (is_operand_override) {
        reg->word--;
    } else {
        reg->dword--;
    }
}

void mov_r32_imm(cpu_t* cpu, OPCODE *start) {
    memcpy(
        &cpu->gp_registers[start[0] - 0xB8],
        &start[1],
        4
    );
}

void mov_r16_imm(cpu_t* cpu, OPCODE *start) {
    memcpy(
        &cpu->gp_registers[start[1] - 0xB8],
        &start[2],
        2
    );
}

