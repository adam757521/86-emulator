#ifndef MACHINE_H
#define MACHINE_H

#include "defines.h"

void initialize_first_map();
void destruct_map_recursive();
void emulate_machine_code(OPCODE* codes);

#endif
