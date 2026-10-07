//
// Created by fabian on 9/22/26.
//
#include "ll.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main (void)
{
    double ret;

    // Liste initialisieren
    ll_t *list = NULL;

    // Füge der Liste 10 Elemente hinzu
    for (int i = 0; i < 10; i++)
    {
        push(&list, i);
    }

    // An der 5ten Stelle eine Zahl einfügen
    addAt(&list, 5.5, 5);
    // An der 100sten Stelle eine Zahl einfügen (sollte ans Ende geschrieben werden)
    addAt(&list, 100, 100);
    // An einer negativen Stelle eine Zahl einfügen (sollte ans Ende geschrieben werden)
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

    // Ausgabe der Liste
    for (int i = 0; i < 16; i++)
    {
        pop(&list, &ret);
        printf("%f\n", ret);
    }

    // Entfernen aller Elemente
    clear(&list);

    // Ausgabe der Liste
    for (int i = 0; i < 16; i++)
    {
        pop(&list, &ret);
        printf("%f\n", ret);
    }

    // Härtetest
    uint32_t anz = 100000000;
    clock_t start = clock();

    for (int i = 0; i < anz; i++)
    {
        push(&list, i);
    }
    clock_t ende_1 = clock();

    setAt(&list, 72.727272, anz-1);
    clock_t ende_2 = clock();

    for (int i = 0; i < anz; i++)
    {
        pop(&list, &ret);
    }
    clock_t ende_3 = clock();

    printf("\n\n\n");
    printf("Zeit für push von %hhu Elementen: %f\n", anz, (double)(ende_1 - start) / CLOCKS_PER_SEC);
    printf("Zeit für setAt vom %hhusten Element: %f\n", anz, (double)(ende_2 - ende_1) / CLOCKS_PER_SEC);
    printf("Zeit für pop von %hhu Elementen: %f\n", anz, (double)(ende_3 - ende_2) / CLOCKS_PER_SEC);


}
