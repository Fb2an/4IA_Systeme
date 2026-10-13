
//
// Created by fabian on 10/13/26.
//

#include "dll.h"
#include "../01_LinkedList/ll.h"

#include <stdio.h>
#include <stdint.h>
#include <time.h>

#define ANZ 100000
#define WIEDERHOLUNGEN 1000

int main(void)
{
    double ret;

    // Liste initialisieren
    dll_ptr_t list = {0};

    // Füge der Liste 10 Elemente hinzu
    for (int i = 0; i < 10; i++)
    {
        push(&list, i);
    }

    // An der 5ten Stelle eine Zahl einfügen
    addAt(&list, 5.5, 5);
    // An der 100sten Stelle eine Zahl einfügen (sollte ans Ende geschrieben werden)
    addAt(&list, 100, 100);
    // An einer negativen Stelle eine Zahl einfügen (sollte am Anfang geschrieben werden)
    addAt(&list, -1, -1);

    // Das 5te Element verändern
    setAt(&list, 5.55, 5);
    // Das 100ste Element verändern (sollte das letzte Element verändern)
    setAt(&list, 100.100, 100);
    // An einer negativen Stelle ein Element verändern (sollte das letzte Element verändern)
    setAt(&list, -1.1, -1);

    // Das 5te Element ausgeben
    getAt(&list, 5, &ret);
    printf("%f\n", ret);
    // Das 100ste Element ausgeben (sollte das letzte Element ausgeben)
    getAt(&list, 100, &ret);
    printf("%f\n", ret);
    // An einer negativen Stelle ein Element ausgeben (sollte das letzte Element ausgeben)
    getAt(&list, -1, &ret);
    printf("%f\n", ret);

    // Ein Element entfernen
    removeAt(&list, 5);

    // Ausgabe der Liste
    printf("\nListe:\n");
    while (pop(&list, &ret) == 0)
    {
        printf("%f\n", ret);
    }

    // Entfernen aller Elemente
    clear(&list);


    // ===========================
    // Härtetest / Zeitvergleich
    // ===========================

    ll_t *ll = NULL;
    dll_ptr_t dll = {0};

    double ll_push, ll_get, ll_pop;
    double dll_push, dll_get, dll_pop;

    clock_t start, ende;

    // ---------------------------
    // Singly Linked List
    // ---------------------------

    printf("\nTeste Singly Linked List...\n");

    start = clock();

    for (uint32_t i = 0; i < ANZ; i++)
    {
        push(&ll, i);
    }

    ende = clock();
    ll_push = (double)(ende - start) / CLOCKS_PER_SEC;

    // Wiederholter Zugriff auf das letzte Element
    start = clock();

    for (int i = 0; i < WIEDERHOLUNGEN; i++)
    {
        getAt(&ll, -1, &ret);
    }

    ende = clock();
    ll_get = (double)(ende - start) / CLOCKS_PER_SEC;

    // Alle Elemente entfernen
    start = clock();

    for (uint32_t i = 0; i < ANZ; i++)
    {
        pop(&ll, &ret);
    }

    ende = clock();
    ll_pop = (double)(ende - start) / CLOCKS_PER_SEC;


    // ---------------------------
    // Doubly Linked List
    // ---------------------------

    printf("Teste Doubly Linked List...\n");

    start = clock();

    for (uint32_t i = 0; i < ANZ; i++)
    {
        push(&dll, i);
    }

    ende = clock();
    dll_push = (double)(ende - start) / CLOCKS_PER_SEC;

    // Wiederholter Zugriff auf das letzte Element
    start = clock();

    for (int i = 0; i < WIEDERHOLUNGEN; i++)
    {
        getAt(&dll, -1, &ret);
    }

    ende = clock();
    dll_get = (double)(ende - start) / CLOCKS_PER_SEC;

    // Alle Elemente entfernen
    start = clock();

    for (uint32_t i = 0; i < ANZ; i++)
    {
        pop(&dll, &ret);
    }

    ende = clock();
    dll_pop = (double)(ende - start) / CLOCKS_PER_SEC;


    // ---------------------------
    // Ergebnisse ausgeben
    // ---------------------------

    printf("\n\n===== ZEITVERGLEICH =====\n");
    printf("Elemente: %u\n", (unsigned int)ANZ);
    printf("GetAt-Wiederholungen: %d\n\n", WIEDERHOLUNGEN);

    printf("%-15s %15s %15s\n", "Operation", "LL (s)", "DLL (s)");
    printf("------------------------------------------------\n");
    printf("%-15s %15.6f %15.6f\n", "push", ll_push, dll_push);
    printf("%-15s %15.6f %15.6f\n", "getAt(-1)", ll_get, dll_get);
    printf("%-15s %15.6f %15.6f\n", "pop", ll_pop, dll_pop);

    printf("\n===== GESCHWINDIGKEIT =====\n");

    if (dll_push > 0)
        printf("push: DLL ist %.2fx so schnell wie LL\n", ll_push / dll_push);

    if (dll_get > 0)
        printf("getAt: DLL ist %.2fx so schnell wie LL\n", ll_get / dll_get);

    if (dll_pop > 0)
        printf("pop: DLL ist %.2fx so schnell wie LL\n", ll_pop / dll_pop);

    return 0;
}
