#include "ll.h"

#include <stdlib.h>

void ll_push(ll_t **list, double data)
{
    if (list == NULL) return;
    ll_t *newE = malloc(sizeof(ll_t));
    if (newE == NULL) return;
    newE->data = data;
    newE->next = *list;
    *list = newE;
}

int8_t ll_pop(ll_t **list, double *ret)
{
    if (list == NULL || *list == NULL) return -1;
    ll_t *temp = *list;
    if (ret != NULL) *ret = temp->data;
    *list = temp->next;
    free(temp);
    return 0;
}

void ll_pushBack(ll_t **list, double data)
{
    if (list == NULL) return;
    ll_t *newE = malloc(sizeof(ll_t));
    if (newE == NULL) return;
    newE->data = data;
    newE->next = NULL;

    if (*list == NULL)
    {
        *list = newE;
        return;
    }

    ll_t *ptr = *list;
    while (ptr->next != NULL) ptr = ptr->next;
    ptr->next = newE;
}

int8_t ll_popBack(ll_t **list, double *ret)
{
    if (list == NULL || *list == NULL) return -1;
    if ((*list)->next == NULL) return ll_pop(list, ret);

    ll_t *ptr = *list;
    while (ptr->next->next != NULL) ptr = ptr->next;

    ll_t *temp = ptr->next;
    if (ret != NULL) *ret = temp->data;
    ptr->next = NULL;
    free(temp);
    return 0;
}

int8_t ll_addAt(ll_t **list, double data, uint64_t index)
{
    if (list == NULL) return -1;
    if (index == 0 || *list == NULL)
    {
        ll_t *newE = malloc(sizeof(ll_t));
        if (newE == NULL) return -1;
        newE->data = data;
        newE->next = *list;
        *list = newE;
        return 0;
    }

    ll_t *ptr = *list;
    // Bei zu grossem Index wird am Ende eingefuegt.
    for (uint64_t i = 1; i < index && ptr->next != NULL; i++)
        ptr = ptr->next;

    ll_t *newE = malloc(sizeof(ll_t));
    if (newE == NULL) return -1;
    newE->data = data;
    newE->next = ptr->next;
    ptr->next = newE;
    return 0;
}

int8_t ll_removeAt(ll_t **list, uint64_t index)
{
    if (list == NULL || *list == NULL) return -1;
    if (index == 0) return ll_pop(list, NULL);

    ll_t *ptr = *list;
    for (uint64_t i = 1; i < index && ptr->next != NULL; i++)
        ptr = ptr->next;

    if (ptr->next == NULL) return -1;
    ll_t *temp = ptr->next;
    ptr->next = temp->next;
    free(temp);
    return 0;
}

void ll_clear(ll_t **list)
{
    if (list == NULL) return;
    while (*list != NULL) ll_pop(list, NULL);
}

int8_t ll_getAt(ll_t **list, uint64_t index, double *ret)
{
    if (list == NULL || *list == NULL || ret == NULL) return -1;
    ll_t *ptr = *list;
    // Bisheriges Verhalten beibehalten: 1 = erstes Element.
    for (uint64_t i = 1; i < index && ptr->next != NULL; i++)
        ptr = ptr->next;
    *ret = ptr->data;
    return 0;
}

int8_t ll_setAt(ll_t **list, double data, uint64_t index)
{
    if (list == NULL || *list == NULL) return -1;
    ll_t *ptr = *list;
    // Bisheriges Verhalten beibehalten: 1 = erstes Element.
    for (uint64_t i = 1; i < index && ptr->next != NULL; i++)
        ptr = ptr->next;
    ptr->data = data;
    return 0;
}
