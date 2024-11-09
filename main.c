#include <stdint.h>
#include <stdio.h>
#include "cpu.h"
#include "map.h"
#include "machine.h"

int main()
{
    // TODO: check no memory leaks in map.c
    // how are we gonna split instructions to their handlers? 
    // the current solution we have were gonna have to check if we have enough space in the handler itself, and before it was inside the machine runner
    // since we had the handler_t struct which had the opcode count, but i removed it since i thought it was stupid and i think its better to work with ip
    // in each handler

    cpu_t cpu;
    cpu.gp_registers[EAX].dword = 80000;
    cpu.ip = 0;
    cpu.gp_registers[ESP].dword = MEMORY_SIZE - 1;

    initialize_first_map();

    OPCODE test[] = {0x40, 0x66, 0x40, 0x48, 0x66, 0x48};

    for (;;)
    {
        int status = emulate_machine_code(&cpu, test, sizeof(test)/sizeof(OPCODE));
        printf("status: %d\n", status);
        if (status != 0)
        {
            break;
        }
    }

    destruct_map_recursive();
    return 0;
}
