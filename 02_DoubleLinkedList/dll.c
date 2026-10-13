//
// Created by fabian on 10/13/26.
//
#include "dll.h"

#include <stdint.h>
#include <stdlib.h>

void push(dll_ptr_t *list, double data)
{
    dll_e_t *e = malloc(sizeof(dll_e_t));
    if (e == NULL) return;

    e->data = data;
    e->next = list->head;
    e->prev = NULL;

    if (list->head != NULL)
    {
        list->head->prev = e;
    }
    else
    {
        list->tail = e;
    }

    list->head = e;
    list->size++;
}

int8_t pop(dll_ptr_t *list, double *ret)
{
    if (list == NULL || list->head == NULL)
    {
        return -1;
    }

    dll_e_t *e = list->head;

    if (ret != NULL)
    {
        *ret = e->data;
    }

    list->head = e->next;

    if (list->head != NULL)
    {
        list->head->prev = NULL;
    }
    else
    {
        list->tail = NULL;
    }

    free(e);
    list->size--;

    return 0;
}

int8_t addAt(dll_ptr_t *list, double data, int_fast8_t index)
{
    if (list == NULL) return -1;

    if (index <= 0)
    {
        push(list, data);
        return 0;
    }

    if (index >= list->size)
    {
        dll_e_t *e = malloc(sizeof(dll_e_t));
        if (e == NULL) return -1;

        e->data = data;
        e->next = NULL;
        e->prev = list->tail;

        if (list->tail != NULL)
        {
            list->tail->next = e;
        }
        else
        {
            list->head = e;
        }

        list->tail = e;
        list->size++;
        return 0;
    }

    dll_e_t *ptr;

    if (index < list->size / 2)
    {
        ptr = list->head;
        for (int i = 0; i < index; i++)
        {
            ptr = ptr->next;
        }
    }
    else
    {
        ptr = list->tail;
        for (uint32_t i = 0; i < list->size - 1 - index; i++)
        {
            ptr = ptr->prev;
        }
    }

    dll_e_t *e = malloc(sizeof(dll_e_t));
    if (e == NULL) return -1;

    e->data = data;
    e->next = ptr;
    e->prev = ptr->prev;

    ptr->prev->next = e;
    ptr->prev = e;

    list->size++;
    return 0;
}

int8_t removeAt(dll_ptr_t *list, int_fast8_t index)
{
    if (list == NULL || list->size == 0) return -1;

    if (index < 0 || index >= list->size)
    {
        index = list->size - 1;
    }

    dll_e_t *ptr;

    if (index < list->size / 2)
    {
        ptr = list->head;
        for (int i = 0; i < index; i++)
        {
            ptr = ptr->next;
        }
    }
    else
    {
        ptr = list->tail;
        for (uint32_t i = 0; i < list->size - 1 - index; i++)
        {
            ptr = ptr->prev;
        }
    }

    if (ptr->prev != NULL)
    {
        ptr->prev->next = ptr->next;
    }
    else
    {
        list->head = ptr->next;
    }

    if (ptr->next != NULL)
    {
        ptr->next->prev = ptr->prev;
    }
    else
    {
        list->tail = ptr->prev;
    }

    free(ptr);
    list->size--;

    return 0;
}

void clear(dll_ptr_t *list)
{
    if (list == NULL) return;

    while (list->size > 0)
    {
        pop(list, NULL);
    }
}

int8_t getAt(dll_ptr_t *list, int_fast8_t index, double *ret)
{
    if (list == NULL || list->size == 0 || ret == NULL)
    {
        return -1;
    }

    if (index < 0 || index >= list->size)
    {
        *ret = list->tail->data;
        return 0;
    }

    dll_e_t *ptr;

    if (index < list->size / 2)
    {
        ptr = list->head;
        for (int i = 0; i < index; i++)
        {
            ptr = ptr->next;
        }
    }
    else
    {
        ptr = list->tail;
        for (uint32_t i = 0; i < list->size - index - 1; i++)
        {
            ptr = ptr->prev;
        }
    }

    *ret = ptr->data;
    return 0;
}

int8_t setAt(dll_ptr_t *list, double data, int_fast8_t index)
{
    if (list == NULL || list->size == 0)
    {
        return -1;
    }

    if (index < 0 || index >= list->size)
    {
        list->tail->data = data;
        return 0;
    }

    dll_e_t *ptr;

    if (index < list->size / 2)
    {
        ptr = list->head;
        for (int i = 0; i < index; i++)
        {
            ptr = ptr->next;
        }
    }
    else
    {
        ptr = list->tail;
        for (uint32_t i = 0; i < list->size - index - 1; i++)
        {
            ptr = ptr->prev;
        }
    }

    ptr->data = data;
    return 0;
}