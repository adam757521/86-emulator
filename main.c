#include <stdint.h>
#include <stdio.h>
#include "cpu.h"
#include "machine.h"

typedef struct
{
    void *ptr;
    int is_map;
} entry_t;

int main()
{
    cpu_t cpu;
    cpu.gp_registers[EAX].dword = 50;
    cpu.ip = 0;
    cpu.gp_registers[ESP].dword = MEMORY_SIZE - 1;

    initialize_first_map();

    OPCODE test[] = {0x40};

    for (;;)
    {
        int status = emulate_machine_code(&cpu, test, 2);
        printf("status: %d\n", status);
        if (status != 0)
        {
            break;
        }
    }

    destruct_map_recursive();
    return 0;
}
