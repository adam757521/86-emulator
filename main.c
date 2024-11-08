#include <stdint.h>
#include "cpu.h"
#include "machine.h"

typedef struct {
    void* ptr;
    int is_map;
} entry_t;

int main() {
    cpu_t cpu;
    cpu.registers[EBP].dword = MEMORY_SIZE - 1;

    initialize_first_map();

    OPCODE test[] = {0x55};

    emulate_machine_code(&cpu, test);

    destruct_map_recursive();
    return 0;
}
