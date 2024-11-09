#include <stdint.h>
#include <stdio.h>
#include "cpu.h"
#include "map.h"
#include "machine.h"

int main()
{
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
