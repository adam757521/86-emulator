#include <stdint.h>
#include "machine.h"

typedef struct {
    void* ptr;
    int is_map;
} entry_t;

int main() {
    initialize_first_map();

    OPCODE test[] = {0x50};

    emulate_machine_code(test);

    destruct_map_recursive();
    return 0;
}
