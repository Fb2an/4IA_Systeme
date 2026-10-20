#include "ll.h"
#include <stdint.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

static int tests = 0;
static int failed = 0;

static void check(const char *name, int condition)
{
    tests++;
    printf("[%s] %s\n", condition ? "PASS" : "FAIL", name);
    if (!condition) failed++;
}

static int equals(const ll_t *list, const double expected[], uint64_t size)
{
    for (uint64_t i = 0; i < size; i++)
    {
        if (list == NULL || list->data != expected[i]) return 0;
        list = list->next;
    }
    return list == NULL;
}

int main(void)
{
    ll_t *list = NULL;
    double ret = 0;

    check("pop auf leerer Liste", ll_pop(&list, &ret) == -1);
    check("popBack auf leerer Liste", ll_popBack(&list, &ret) == -1);
    check("removeAt auf leerer Liste", ll_removeAt(&list, 0) == -1);

    ll_push(&list, 2);
    ll_push(&list, 1);
    check("push vorne", equals(list, (double[]){1, 2}, 2));

    ll_pushBack(&list, 3);
    check("pushBack hinten", equals(list, (double[]){1, 2, 3}, 3));

    check("addAt vorne", ll_addAt(&list, 0, 0) == 0 &&
          equals(list, (double[]){0, 1, 2, 3}, 4));
    check("addAt Mitte", ll_addAt(&list, 1.5, 2) == 0 &&
          equals(list, (double[]){0, 1, 1.5, 2, 3}, 5));
    check("addAt hinter Ende", ll_addAt(&list, 4, 100) == 0 &&
          equals(list, (double[]){0, 1, 1.5, 2, 3, 4}, 6));

    check("removeAt erstes Element", ll_removeAt(&list, 0) == 0 &&
          equals(list, (double[]){1, 1.5, 2, 3, 4}, 5));
    check("removeAt Mitte", ll_removeAt(&list, 1) == 0 &&
          equals(list, (double[]){1, 2, 3, 4}, 4));
    check("removeAt letztes Element", ll_removeAt(&list, 3) == 0 &&
          equals(list, (double[]){1, 2, 3}, 3));
    check("removeAt ausserhalb", ll_removeAt(&list, 100) == -1 &&
          equals(list, (double[]){1, 2, 3}, 3));

    check("getAt (0-basiert)",
          ll_getAt(&list, 1, &ret) == 0 && ret == 2);
    check("setAt (0-basiert)",
          ll_setAt(&list, 2.5, 1) == 0 &&
          equals(list, (double[]){1, 2.5, 3}, 3));

    check("popBack liefert letzten Wert",
          ll_popBack(&list, &ret) == 0 && ret == 3 &&
          equals(list, (double[]){1, 2.5}, 2));
    check("pop liefert ersten Wert",
          ll_pop(&list, &ret) == 0 && ret == 1 &&
          equals(list, (double[]){2.5}, 1));
    check("popBack bei einem Knoten",
          ll_popBack(&list, &ret) == 0 && ret == 2.5 && list == NULL);

    ll_pushBack(&list, 7);
    ll_clear(&list);
    check("clear leert Liste", list == NULL);
    ll_clear(&list);
    check("clear auf leerer Liste", list == NULL);

    ll_pushBack(&list, 4);
    ll_pushBack(&list, 5);
    check("search findet Element", ll_search(list, 5) == 1);
    check("search nicht vorhanden", ll_search(list, 999) == -1);
    uint64_t size = 0;
    double *array = ll_export(list, &size);
    check("export als Array", array != NULL && size == 2 && array[0] == 4 && array[1] == 5);
    free(array);
    check("getAt ausserhalb", ll_getAt(&list, 100, &ret) == -1);
    check("setAt ausserhalb", ll_setAt(&list, 7, 100) == -1);
    ll_clear(&list);
    array = ll_export(list, &size);
    check("export leere Liste", array == NULL && size == 0);
    free(array);

    // Kleiner Benchmark statt 100 Millionen Knoten (hoher RAM-Bedarf).
    const uint64_t anz = 100000;
    clock_t start = clock();
    for (uint64_t i = 0; i < anz; i++) ll_push(&list, (double)i);
    clock_t nachPush = clock();
    for (uint64_t i = 0; i < anz; i++) ll_pop(&list, NULL);
    clock_t nachPop = clock();
    check("Benchmark: Liste am Ende leer", list == NULL);

    printf("\nTests: %d, bestanden: %d, fehlgeschlagen: %d\n",
           tests, tests - failed, failed);
    printf("ll_push: %.6f s, ll_pop: %.6f s (je %llu Elemente)\n",
           (double)(nachPush - start) / CLOCKS_PER_SEC,
           (double)(nachPop - nachPush) / CLOCKS_PER_SEC,
           (unsigned long long)anz);
    return failed == 0 ? 0 : 1;
}
