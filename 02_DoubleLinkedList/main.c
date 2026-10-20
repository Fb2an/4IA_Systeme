#include "dll.h"
#include "../01_LinkedList/ll.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ANZ 100000
#define WIEDERHOLUNGEN 1000

static int tests = 0;
static int failed = 0;

static void check(const char *name, int condition)
{
    tests++;
    printf("[%s] %s\n", condition ? "PASS" : "FAIL", name);
    if (!condition) failed++;
}

static int equals(const dll_ptr_t *list, const double expected[], uint64_t size)
{
    if (list->size != size) return 0;
    const dll_e_t *ptr = list->head;
    const dll_e_t *previous = NULL;
    for (uint64_t i = 0; i < size; i++)
    {
        if (ptr == NULL || ptr->data != expected[i] || ptr->prev != previous) return 0;
        previous = ptr;
        ptr = ptr->next;
    }
    return ptr == NULL && previous == list->tail;
}

int main(void)
{
    double ret = 0;
    dll_ptr_t list = {0};
    check("pop bei leerer DLL", dll_pop(&list, &ret) == -1);
    check("popBack bei leerer DLL", dll_popBack(&list, &ret) == -1);
    check("removeAt bei leerer DLL", dll_removeAt(&list, 0) == -1);

    dll_push(&list, 2);
    dll_push(&list, 1);
    check("push vorne", equals(&list, (double[]){1, 2}, 2));
    dll_pushBack(&list, 3);
    check("pushBack hinten", equals(&list, (double[]){1, 2, 3}, 3));
    check("addAt vorne", dll_addAt(&list, 0, 0) == 0 && equals(&list, (double[]){0, 1, 2, 3}, 4));
    check("addAt Mitte", dll_addAt(&list, 1.5, 2) == 0 && equals(&list, (double[]){0, 1, 1.5, 2, 3}, 5));
    check("addAt hinter Ende", dll_addAt(&list, 4, 100) == 0 && equals(&list, (double[]){0, 1, 1.5, 2, 3, 4}, 6));
    check("removeAt vorne", dll_removeAt(&list, 0) == 0 && equals(&list, (double[]){1, 1.5, 2, 3, 4}, 5));
    check("removeAt Mitte", dll_removeAt(&list, 1) == 0 && equals(&list, (double[]){1, 2, 3, 4}, 4));
    check("removeAt hinten", dll_removeAt(&list, 3) == 0 && equals(&list, (double[]){1, 2, 3}, 3));
    check("removeAt ungueltig", dll_removeAt(&list, 100) == -1 && list.size == 3);
    check("getAt erstes Element", dll_getAt(&list, 0, &ret) == 0 && ret == 1);
    check("setAt erstes Element", dll_setAt(&list, 1.25, 0) == 0 && equals(&list, (double[]){1.25, 2, 3}, 3));
    check("getAt letztes Element", dll_getAt(&list, 2, &ret) == 0 && ret == 3);
    check("getAt ungueltig", dll_getAt(&list, 100, &ret) == -1);
    check("setAt ungueltig", dll_setAt(&list, 9, 100) == -1);
    check("search findet Wert", dll_search(&list, 2) == 1);
    check("search nicht gefunden", dll_search(&list, 8) == -1);
    uint64_t size = 0;
    double *array = dll_export(&list, &size);
    check("export als Array", array != NULL && size == 3 && array[0] == 1.25 && array[1] == 2 && array[2] == 3);
    free(array);
    check("popBack liefert Wert", dll_popBack(&list, &ret) == 0 && ret == 3 && equals(&list, (double[]){1.25, 2}, 2));
    check("pop liefert Wert", dll_pop(&list, &ret) == 0 && ret == 1.25 && equals(&list, (double[]){2}, 1));
    check("popBack letzter Knoten", dll_popBack(&list, &ret) == 0 && ret == 2 && equals(&list, NULL, 0));
    dll_clear(&list);
    array = dll_export(&list, &size);
    check("export leere Liste", array == NULL && size == 0);
    free(array);

    ll_t *ll = NULL;
    dll_ptr_t dll = {0};
    double ll_push_time, ll_get_time, ll_pop_time;
    double dll_push_time, dll_get_time, dll_pop_time;
    clock_t start, ende;
    volatile double sink = 0;

    start = clock();
    for (uint64_t i = 0; i < ANZ; i++) ll_push(&ll, (double)i);
    ende = clock();
    ll_push_time = (double)(ende - start) / CLOCKS_PER_SEC;
    start = clock();
    for (uint64_t i = 0; i < WIEDERHOLUNGEN; i++)
    {
        if (ll_getAt(&ll, ANZ - 1, &ret) == 0) sink += ret;
    }
    ende = clock();
    ll_get_time = (double)(ende - start) / CLOCKS_PER_SEC;
    start = clock();
    while (ll_pop(&ll, NULL) == 0) {}
    ende = clock();
    ll_pop_time = (double)(ende - start) / CLOCKS_PER_SEC;

    start = clock();
    for (uint64_t i = 0; i < ANZ; i++) dll_push(&dll, (double)i);
    ende = clock();
    dll_push_time = (double)(ende - start) / CLOCKS_PER_SEC;
    start = clock();
    for (uint64_t i = 0; i < WIEDERHOLUNGEN; i++)
    {
        if (dll_getAt(&dll, ANZ - 1, &ret) == 0) sink += ret;
    }
    ende = clock();
    dll_get_time = (double)(ende - start) / CLOCKS_PER_SEC;
    start = clock();
    while (dll_pop(&dll, NULL) == 0) {}
    ende = clock();
    dll_pop_time = (double)(ende - start) / CLOCKS_PER_SEC;

    printf("\n===== ZEITVERGLEICH =====\n");
    printf("Elemente: %d, getAt-Wiederholungen: %d\n", ANZ, WIEDERHOLUNGEN);
    printf("%-15s %15s %15s\n", "Operation", "LL (s)", "DLL (s)");
    printf("%-15s %15.6f %15.6f\n", "push", ll_push_time, dll_push_time);
    printf("%-15s %15.6f %15.6f\n", "getAt(last)", ll_get_time, dll_get_time);
    printf("%-15s %15.6f %15.6f\n", "pop", ll_pop_time, dll_pop_time);
    printf("Pruefsumme: %.0f\n", sink);
    printf("Tests: %d, bestanden: %d, fehlgeschlagen: %d\n", tests, tests - failed, failed);
    return failed == 0 ? 0 : 1;
}
