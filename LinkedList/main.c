//
// Created by fabian on 9/22/26.
//
#include "ll.h"
#include <stdio.h>
#include <stdlib.h>

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
}
