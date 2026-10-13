//
// Created by fabian on 9/16/26.
//

#ifndef LL_H
#define LL_H

#include <stdint.h>

typedef struct ll {
    double data;
    struct ll *next;
} ll_t;

void ll_push(ll_t **list, double data);

int8_t ll_pop(ll_t **list, double* ret);

int8_t ll_addAt(ll_t **list, double data, uint64_t index);

int8_t ll_removeAt(ll_t **list, uint64_t index);

void ll_clear(ll_t **list);

int8_t ll_getAt(ll_t **list, uint64_t index, double* ret);

int8_t ll_setAt(ll_t **list, double data, uint64_t index);

#endif