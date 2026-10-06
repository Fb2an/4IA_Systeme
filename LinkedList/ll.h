//
// Created by fabian on 9/16/26.
//

#include <stdint.h>

typedef struct ll {
    double data;
    struct ll *next;
} ll_t;

void push(ll_t **list, double data);

int8_t pop(ll_t **list, double* ret);

int8_t addAt(ll_t **list, double data, int_fast8_t index);

int8_t removeAt(ll_t **list, int_fast8_t index);

void clear(ll_t **list);

int8_t getAt(ll_t **list, int_fast8_t index, double* ret);

int8_t setAt(ll_t **list, double data, int_fast8_t index);
