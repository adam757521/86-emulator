#include "instruction.h"
#include <stdio.h>
#include <memory.h>

void push(cpu_t* cpu, OPCODE* opcodes, uint8_t count) {
    BYTE register_ = opcodes[0] - 0x50;
    cpu_register_t* reg = &cpu->registers[register_];
    
    DWORD* ebp = &cpu->registers[EBP].dword;
    *ebp -= 4;
    memcpy(&cpu->memory[*ebp], &reg->dword, 4);

    printf("%d\n", *((int*)cpu->memory + *ebp));
}
