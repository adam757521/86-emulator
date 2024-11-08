#include <stdint.h>
#include "cpu.h"
#include "machine.h"

typedef struct {
    void* ptr;
    int is_map;
} entry_t;

int main() {
    cpu_t cpu;
    cpu.registers[EAX].dword = 50;
    cpu.registers[ESP].dword = MEMORY_SIZE - 1;

    initialize_first_map();

    OPCODE test[] = {0x50};

    emulate_machine_code(&cpu, test);

    destruct_map_recursive();
    return 0;
}
