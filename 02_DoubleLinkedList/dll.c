//
// Created by fabian on 10/13/26.
//
#include "dll.h"

#include <stdint.h>
#include <stdlib.h>

void push(dll_ptr_t *list, double data)
{
    dll_e_t *e = malloc(sizeof(dll_e_t));
    e->data = data;
    e->next = list->head;
    e->prev = NULL;
    list->head = e;
    list->size++;
}

int8_t addAt(dll_ptr_t *list, double data, int_fast8_t index)
{
    if (index < 0 || index > list->size)
    {
        dll_e_t* e = malloc(sizeof(dll_e_t));
        e->data = data;
        e->next = NULL;
        e->prev = list->tail;
        list->tail = e;
        list->size++;
        return 0;
    }
    if (index > list->size - index)
    {
        for (int i = 0; i < index; i++)
        {

        }
    }
}

int8_t removeAt(dll_ptr_t *list, int_fast8_t index)
{

}

void clear(dll_ptr_t *list)
{

}

int8_t pop(dll_ptr_t *list, double* ret)
{
    if (list == NULL || list->head == NULL)
    {
        return -1;
    }
    *ret = list->head->data;
    list->head = list->head->next;
    list->size--;
    return 0;
}

int8_t getAt(dll_ptr_t *list, int_fast8_t index, double* ret)
{

}

int8_t setAt(dll_ptr_t *list, double data, int_fast8_t index)
{

}