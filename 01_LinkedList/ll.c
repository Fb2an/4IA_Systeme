//
// Created by fabian on 9/16/26.
//
#include "ll.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void push(ll_t **list, double data)
{
    ll_t *newE = malloc(sizeof(ll_t));
    newE->data = data;
    newE->next = *list;
    *list = newE;
}

int8_t pop(ll_t** list, double* ret)
{
    if (*list == NULL)
    {
        return -1;
    }
    *ret = (*list)->data;
    ll_t *temp = *list;
    *list = temp->next;
    free(temp);
    return 0;
}

int8_t addAt(ll_t **list, double data, int_fast8_t index)
{
    if (*list == NULL)
        return -1;
    ll_t* ptr = *list;
    if (index < 0)
    {
        while (ptr->next != NULL)
        {
            ptr = ptr->next;
        }
    } else
    {
        for (int i = 1; i < index; i++)
        {
            if (ptr->next != NULL)
                ptr = ptr->next;
        }
    }

    ll_t *newE = malloc(sizeof(ll_t));
    newE->data = data;
    newE->next = ptr->next;
    ptr->next = newE;

    return 0;
}

int8_t removeAt(ll_t **list, int_fast8_t index)
{
    if (*list == NULL)
        return -1;
    ll_t* ptr = *list;
    if (index < 0)
    {
        while (ptr->next != NULL)
        {
            if (ptr->next != NULL)
            ptr = ptr->next;
        }
    } else
    {
        for (int i = 1; i < index; i++)
        {
            ptr = ptr->next;
        }
    }

    ll_t* temp = ptr->next;
    ptr->next = temp->next;
    free(temp);

    return 0;
}

void clear(ll_t **list)
{
    while (*list != NULL)
    {
        pop(list, NULL);
    }
}

int8_t getAt(ll_t **list, int_fast8_t index, double* ret)
{
    if (*list == NULL)
        return -1;
    ll_t* ptr = *list;
    if (index < 0)
    {
        while (ptr->next != NULL)
        {
            ptr = ptr->next;
        }
    } else
    {
        for (int i = 1; i < index; i++)
        {
            if (ptr->next != NULL)
                ptr = ptr->next;
        }
    }

    *ret = ptr->data;
    return 0;
}

int8_t setAt(ll_t **list, double data, int_fast8_t index)
{
    if (*list == NULL)
        return -1;
    ll_t* ptr = *list;
    if (index < 0)
    {
        while (ptr->next != NULL)
        {
            ptr = ptr->next;
        }
    } else
    {
        for (int i = 1; i < index; i++)
        {
            if (ptr->next != NULL)
                ptr = ptr->next;
        }
    }

    ptr->data = data;

    return 0;
}
