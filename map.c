#include "map.h"

#include <stdlib.h>

entry_t *entries[256] = {0};

entry_t *get_push_handler()
{
    handler_t *handler = malloc(sizeof(handler_t));
    handler->handler = push;
    handler->consumed_opcodes = 1;

    entry_t *entry = malloc(sizeof(entry_t));
    entry->ptr = handler;
    entry->is_map = 0;

    return entry;
}

entry_t *get_pop_handler()
{
    handler_t *handler = malloc(sizeof(handler_t));
    handler->handler = pop;
    handler->consumed_opcodes = 1;

    entry_t *entry = malloc(sizeof(entry_t));
    entry->ptr = handler;
    entry->is_map = 0;

    return entry;
}

entry_t *get_inc_handler()
{
    handler_t *handler = malloc(sizeof(handler_t));
    handler->handler = inc;
    handler->consumed_opcodes = 1;

    entry_t *entry = malloc(sizeof(entry_t));
    entry->ptr = handler;
    entry->is_map = 0;

    return entry;
}

entry_t *get_dec_handler()
{
    handler_t *handler = malloc(sizeof(handler_t));
    handler->handler = dec;
    handler->consumed_opcodes = 1;

    entry_t *entry = malloc(sizeof(entry_t));
    entry->ptr = handler;
    entry->is_map = 0;

    return entry;
}

void initialize_first_map()
{
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
    }

    entry_t *dec_h = get_dec_handler();
    for (uint8_t start = 0x48; start < 0x50; start++)
    {
        entries[start] = dec_h;
    }
}

void destruct_map_recursive()
{
    free(entries[0x50]->ptr);
    free(entries[0x50]);
    free(entries[0x58]->ptr);
    free(entries[0x58]);
    free(entries[0x40]->ptr);
    free(entries[0x40]);
    free(entries[0x48]->ptr);
    free(entries[0x48]);
}
