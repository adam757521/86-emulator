#include "map.h"
#include "instruction.h"

#include <stdlib.h>

entry_t *entries[256] = {0};

void free_entry(entry_t* entry) {
    free(entry->ptr);
    free(entry);
}

entry_t *get_push32_handler()
{
    handler_t* handler = malloc(sizeof(handler_t));
    handler->handler = push_32;
    handler->consumed_opcodes = 1;

    entry_t *entry = malloc(sizeof(entry_t));
    entry->ptr = handler;
    entry->is_map = 0;

    return entry;
}

entry_t *get_push16_handler()
{
    handler_t* handler = malloc(sizeof(handler_t));
    handler->handler = push_16;
    handler->consumed_opcodes = 1;

    entry_t *entry = malloc(sizeof(entry_t));
    entry->ptr = handler;
    entry->is_map = 0;

    return entry;
}

entry_t *get_pop32_handler()
{
    handler_t* handler = malloc(sizeof(handler_t));
    handler->handler = pop_32;
    handler->consumed_opcodes = 1;

    entry_t *entry = malloc(sizeof(entry_t));
    entry->ptr = handler;
    entry->is_map = 0;

    return entry;
}

entry_t *get_pop16_handler()
{
    handler_t* handler = malloc(sizeof(handler_t));
    handler->handler = pop_16;
    handler->consumed_opcodes = 1;

    entry_t *entry = malloc(sizeof(entry_t));
    entry->ptr = handler;
    entry->is_map = 0;

    return entry;
}

entry_t* get_inc_handler()
{
    handler_t* handler = malloc(sizeof(handler_t));
    handler->handler = inc_32_16;
    handler->consumed_opcodes = 1;

    entry_t *entry = malloc(sizeof(entry_t));
    entry->ptr = handler;
    entry->is_map = 0;

    return entry;
}

entry_t* get_dec_handler()
{
    handler_t* handler = malloc(sizeof(handler_t));
    handler->handler = dec_32_16;
    handler->consumed_opcodes = 1;

    entry_t *entry = malloc(sizeof(entry_t));
    entry->ptr = handler;
    entry->is_map = 0;

    return entry;
}

entry_t* get_mov_r32_handler() {
    handler_t* handler = malloc(sizeof(handler_t));
    handler->handler = mov_r32_imm;
    handler->consumed_opcodes = 5;

    entry_t *entry = malloc(sizeof(entry_t));
    entry->ptr = handler;
    entry->is_map = 0;

    return entry;
}

entry_t* get_mov_r16_handler() {
    handler_t* handler = malloc(sizeof(handler_t));
    handler->handler = mov_r16_imm;
    handler->consumed_opcodes = 3;

    entry_t *entry = malloc(sizeof(entry_t));
    entry->ptr = handler;
    entry->is_map = 0;

    return entry;
}

entry_t* get_operand_override_map() 
{
    entry_t* entry = malloc(sizeof(entry_t));
    entry->ptr = calloc(sizeof(entry_t*), 256);
    entry->is_map = 1;

    return entry;
}

void initialize_first_map()
{
    entries[0x66] = get_operand_override_map();
    entry_t** override_map = entries[0x66]->ptr;

    entry_t *push32_h = get_push32_handler();
    entry_t *push16_h = get_push16_handler();
    for (uint8_t start = 0x50; start < 0x58; start++)
    {
        entries[start] = push32_h;

        override_map[start] = push16_h;
    }

    entry_t *pop32_h = get_pop32_handler();
    entry_t *pop16_h = get_pop16_handler();
    for (uint8_t start = 0x58; start < 0x60; start++)
    {
        entries[start] = pop32_h;

        override_map[start] = pop16_h;
    }

    entry_t *inc_h = get_inc_handler();
    for (uint8_t start = 0x40; start < 0x48; start++)
    {
        entries[start] = inc_h;
        
        entry_t** map = entries[0x66]->ptr;
        map[start] = inc_h;
    }

    entry_t *dec_h = get_dec_handler();
    for (uint8_t start = 0x48; start < 0x50; start++)
    {
        entries[start] = dec_h;

        override_map[start] = dec_h;
    }

    entry_t* mov_r32_imm_handler = get_mov_r32_handler();
    entry_t* mov_r16_imm_handler = get_mov_r16_handler();
    for (uint8_t start = 0xB8; start < 0xC0; start++) 
    {
        entries[start] = mov_r32_imm_handler;

        override_map[start] = mov_r16_imm_handler;
    }
}

void destruct_map_recursive()
{
    entry_t** override_map = entries[0x66]->ptr;

    free_entry(override_map[0x50]);
    free_entry(override_map[0x58]);
    free_entry(override_map[0xB8]);
    free_entry(entries[0x66]);

    free_entry(entries[0xB8]);
    free_entry(entries[0x50]);
    free_entry(entries[0x58]);
    free_entry(entries[0x40]);
    free_entry(entries[0x48]);
}
