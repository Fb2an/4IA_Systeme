//
// Created by fabian on 10/13/26.
//

#include <stdint.h>

typedef struct dll_e
{
    double data;
    struct dll_e *next;
    struct dll_e *prev;
} dll_e_t;

typedef struct dll_ptr
{
    dll_e_t *head;
    dll_e_t *tail;
    uint32_t size;
} dll_ptr_t;

void push(dll_ptr_t *list, double data);

int8_t pop(dll_ptr_t *list, double* ret);

int8_t addAt(dll_ptr_t *list, double data, int_fast8_t index);

int8_t removeAt(dll_ptr_t *list, int_fast8_t index);

void clear(dll_ptr_t *list);

int8_t getAt(dll_ptr_t *list, int_fast8_t index, double* ret);

int8_t setAt(dll_ptr_t *list, double data, int_fast8_t index);
