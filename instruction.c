#include "instruction.h"
#include <stdio.h>
#include <memory.h>

void push(cpu_t* cpu, OPCODE* opcodes, uint8_t count) {
    BYTE register_ = opcodes[0] - 0x50;
    cpu_register_t* reg = &cpu->registers[register_];
    
    DWORD* esp = &cpu->registers[ESP].dword;
    *esp -= 4;
    memcpy(&cpu->memory[*esp], &reg->dword, 4);

    printf("%d\n", *((int*)cpu->memory + *esp));
}
