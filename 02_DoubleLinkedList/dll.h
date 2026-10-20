// Created by fabian on 10/13/26.
#ifndef DLL_H
#define DLL_H
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
    uint64_t size;
} dll_ptr_t;

void dll_push(dll_ptr_t *list, double data);
int8_t dll_pop(dll_ptr_t *list, double *ret);
void dll_pushBack(dll_ptr_t *list, double data);
int8_t dll_popBack(dll_ptr_t *list, double *ret);
int8_t dll_addAt(dll_ptr_t *list, double data, uint64_t index);
int8_t dll_removeAt(dll_ptr_t *list, uint64_t index);
void dll_clear(dll_ptr_t *list);
int8_t dll_getAt(const dll_ptr_t *list, uint64_t index, double *ret);
int8_t dll_setAt(dll_ptr_t *list, double data, uint64_t index);
int64_t dll_search(const dll_ptr_t *list, double data);
double *dll_export(const dll_ptr_t *list, uint64_t *size);
#endif
