#include "instruction.h"
#include <memory.h>
#include <stdio.h>

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

// 66 B8 00 00 
// 66 B8 01 01
// 66 B8
void mov_r32_16_imm(cpu_t* cpu, OPCODE *start) {
    BYTE is_operand_override = start[0] == 0x66;
    memcpy(
        &cpu->gp_registers[start[is_operand_override] - 0xB8],
        &start[is_operand_override + 1],
        is_operand_override ? 2 : 4
    );
}

void mov_r8_imm(cpu_t* cpu, OPCODE *start) {

}
