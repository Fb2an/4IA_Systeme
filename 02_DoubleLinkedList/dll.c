// Created by fabian on 10/13/26.
#include "dll.h"
#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>

void dll_push(dll_ptr_t *list, double data)
{
    if (list == NULL) return;
    dll_e_t *e = malloc(sizeof(dll_e_t));
    if (e == NULL) return;
    e->data = data;
    e->next = list->head;
    e->prev = NULL;
    if (list->head != NULL) list->head->prev = e;
    else list->tail = e;
    list->head = e;
    list->size++;
}

int8_t dll_pop(dll_ptr_t *list, double *ret)
{
    if (list == NULL || list->head == NULL) return -1;
    dll_e_t *e = list->head;
    if (ret != NULL) *ret = e->data;
    list->head = e->next;
    if (list->head != NULL) list->head->prev = NULL;
    else list->tail = NULL;
    free(e);
    list->size--;
    return 0;
}

void dll_pushBack(dll_ptr_t *list, double data)
{
    if (list == NULL) return;
    dll_e_t *e = malloc(sizeof(dll_e_t));
    if (e == NULL) return;
    e->data = data;
    e->prev = list->tail;
    e->next = NULL;
    if (list->tail != NULL) list->tail->next = e;
    else list->head = e;
    list->tail = e;
    list->size++;
}

int8_t dll_popBack(dll_ptr_t *list, double *ret)
{
    if (list == NULL || list->tail == NULL) return -1;
    dll_e_t *e = list->tail;
    if (ret != NULL) *ret = e->data;
    list->tail = e->prev;
    if (list->tail != NULL) list->tail->next = NULL;
    else list->head = NULL;
    free(e);
    list->size--;
    return 0;
}

// Wie bisher wird ein zu grosser Einfuegeindex ans Ende gesetzt.
int8_t dll_addAt(dll_ptr_t *list, double data, uint64_t index)
{
    if (list == NULL) return -1;
    if (index == 0)
    {
        uint64_t oldSize = list->size;
        dll_push(list, data);
        return list->size == oldSize + 1 ? 0 : -1;
    }
    if (index >= list->size)
    {
        uint64_t oldSize = list->size;
        dll_pushBack(list, data);
        return list->size == oldSize + 1 ? 0 : -1;
    }
    dll_e_t *ptr = list->head;
    if (index < list->size / 2)
    {
        for (uint64_t i = 0; i < index; i++) ptr = ptr->next;
    }
    else
    {
        ptr = list->tail;
        for (uint64_t i = list->size - 1; i > index; i--) ptr = ptr->prev;
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

int8_t dll_removeAt(dll_ptr_t *list, uint64_t index)
{
    if (list == NULL || index >= list->size) return -1;
    if (index == 0) return dll_pop(list, NULL);
    if (index == list->size - 1) return dll_popBack(list, NULL);
    dll_e_t *ptr;
    if (index < list->size / 2)
    {
        ptr = list->head;
        for (uint64_t i = 0; i < index; i++) ptr = ptr->next;
    }
    else
    {
        ptr = list->tail;
        for (uint64_t i = list->size - 1; i > index; i--) ptr = ptr->prev;
    }
    ptr->prev->next = ptr->next;
    ptr->next->prev = ptr->prev;
    free(ptr);
    list->size--;
    return 0;
}

void dll_clear(dll_ptr_t *list)
{
    if (list == NULL) return;
    while (list->head != NULL) dll_pop(list, NULL);
}

int8_t dll_getAt(const dll_ptr_t *list, uint64_t index, double *ret)
{
    if (list == NULL || ret == NULL || index >= list->size) return -1;
    const dll_e_t *ptr;
    if (index < list->size / 2)
    {
        ptr = list->head;
        for (uint64_t i = 0; i < index; i++) ptr = ptr->next;
    }
    else
    {
        ptr = list->tail;
        for (uint64_t i = list->size - 1; i > index; i--) ptr = ptr->prev;
    }
    *ret = ptr->data;
    return 0;
}

int8_t dll_setAt(dll_ptr_t *list, double data, uint64_t index)
{
    if (list == NULL || index >= list->size) return -1;
    dll_e_t *ptr;
    if (index < list->size / 2)
    {
        ptr = list->head;
        for (uint64_t i = 0; i < index; i++) ptr = ptr->next;
    }
    else
    {
        ptr = list->tail;
        for (uint64_t i = list->size - 1; i > index; i--) ptr = ptr->prev;
    }
    ptr->data = data;
    return 0;
}

int64_t dll_search(const dll_ptr_t *list, double data)
{
    if (list == NULL) return -1;
    int64_t index = 0;
    for (const dll_e_t *ptr = list->head; ptr != NULL; ptr = ptr->next, index++)
        if (ptr->data == data) return index;
    return -1;
}

double *dll_export(const dll_ptr_t *list, uint64_t *size)
{
    if (size == NULL) return NULL;
    *size = list == NULL ? 0 : list->size;
    if (*size == 0 || *size > SIZE_MAX / sizeof(double)) return NULL;
    double *array = malloc((size_t)*size * sizeof(double));
    if (array == NULL) return NULL;
    uint64_t i = 0;
    for (const dll_e_t *ptr = list->head; ptr != NULL; ptr = ptr->next)
        array[i++] = ptr->data;
    return array;
}
