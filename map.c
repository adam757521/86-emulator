#include "map.h"

#include <stdlib.h>

entry_t *entries[256] = {0};

void free_entry(entry_t* entry) {
    free(entry->ptr);
    free(entry);
}

entry_t *get_push_handler()
{
    entry_t *entry = malloc(sizeof(entry_t));
    entry->ptr = push;
    entry->is_map = 0;

    return entry;
}

entry_t *get_pop_handler()
{
    entry_t *entry = malloc(sizeof(entry_t));
    entry->ptr = pop;
    entry->is_map = 0;

    return entry;
}

entry_t* get_inc_handler()
{
    entry_t *entry = malloc(sizeof(entry_t));
    entry->ptr = inc_32_16;
    entry->is_map = 0;

    return entry;
}

entry_t* get_dec_handler()
{
    entry_t *entry = malloc(sizeof(entry_t));
    entry->ptr = dec_32_16;
    entry->is_map = 0;

    return entry;
}

entry_t* get_mov_r32_16_imm_handler() {
    entry_t *entry = malloc(sizeof(entry_t));
    entry->ptr = mov_r32_16_imm;
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

    entry_t *push_h = get_push_handler();
    for (uint8_t start = 0x50; start < 0x58; start++)
    {
        entries[start] = push_h;
    }

    entry_t *pop_h = get_pop_handler();
    for (uint8_t start = 0x58; start < 0x60; start++)
    {
        entries[start] = pop_h;
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

        entry_t** map = entries[0x66]->ptr;
        map[start] = dec_h;
    }

    entry_t* mov_r32_16_imm = get_mov_r32_16_imm_handler();
    for (uint8_t start = 0xB8; start < 0xC0; start++) 
    {
        entries[start] = mov_r32_16_imm;

        entry_t** map = entries[0x66]->ptr;
        map[start] = mov_r32_16_imm;
    }
}

void destruct_map_recursive()
{
    free_entry(entries[0x66]);

    free(entries[0x50]);
    free(entries[0x58]);
    free(entries[0x40]);
    free(entries[0x48]);
    free(entries[0xB8]);
}
