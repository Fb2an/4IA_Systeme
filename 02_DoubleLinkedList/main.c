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


static void print_ll(const char *label, const ll_t *list)
{
    uint64_t size = 0;
    double *values = ll_export(list, &size);
    printf("%s (%llu): [", label, (unsigned long long)size);
    for (uint64_t i = 0; i < size; i++) printf("%s%.2f", i ? ", " : "", values[i]);
    puts("]");
    free(values);
}

static void print_dll(const char *label, const dll_ptr_t *list)
{
    uint64_t size = 0;
    double *values = dll_export(list, &size);
    printf("%s (%llu): [", label, (unsigned long long)size);
    for (uint64_t i = 0; i < size; i++) printf("%s%.2f", i ? ", " : "", values[i]);
    puts("]");
    free(values);
}

static double seconds(clock_t start)
{
    return (double)(clock() - start) / CLOCKS_PER_SEC;
}

// Operationen muessen wirklich ausgefuehrt werden, nicht wegoptimiert.
static volatile double checksum = 0;
static void benchmark(void)
{
    const uint32_t n = 12000;
    const uint32_t middleOperations = 1200;
    const char *names[] = {
        "Einfuegen vorne", "Einfuegen hinten",
        "Suchen (Mitte)", "Loeschen (Mitte)", "Entfernen hinten"
    };
    double times[5][2] = {{0}};
    ll_t *ll = NULL;
    dll_ptr_t dll = {0};
    clock_t start;
    double ret = 0;

    // 1. Einfuegen vorne: bei beiden O(1) pro Operation.
    start = clock();
    for (uint32_t i = 0; i < n; ++i) ll_push(&ll, (double)i);
    times[0][0] = seconds(start);
    ll_clear(&ll);
    start = clock();
    for (uint32_t i = 0; i < n; ++i) dll_push(&dll, (double)i);
    times[0][1] = seconds(start);
    dll_clear(&dll);

    // 2. Einfuegen hinten: LL O(N^2), DLL O(N) insgesamt.
    start = clock();
    for (uint32_t i = 0; i < n; ++i) ll_pushBack(&ll, (double)i);
    times[1][0] = seconds(start);
    start = clock();
    for (uint32_t i = 0; i < n; ++i) dll_pushBack(&dll, (double)i);
    times[1][1] = seconds(start);

    // 3. Identische Suche nach einem Wert in der Mitte.
    start = clock();
    for (uint32_t i = 0; i < middleOperations; ++i)
        checksum += (double)ll_search(ll, (double)(n / 2));
    times[2][0] = seconds(start);
    start = clock();
    for (uint32_t i = 0; i < middleOperations; ++i)
        checksum += (double)dll_search(&dll, (double)(n / 2));
    times[2][1] = seconds(start);

    // 4. Wiederholt den mittleren Knoten entfernen (gleiche Listengroessen).
    start = clock();
    for (uint32_t i = 0; i < middleOperations; ++i)
        checksum += ll_removeAt(&ll, (n - i) / 2);
    times[3][0] = seconds(start);
    start = clock();
    for (uint32_t i = 0; i < middleOperations; ++i)
        checksum += dll_removeAt(&dll, (n - i) / 2);
    times[3][1] = seconds(start);
    ll_clear(&ll);
    dll_clear(&dll);

    // 5. Hinten entfernen: LL muss jedes Mal bis zum Vorletzten laufen.
    for (uint32_t i = 0; i < n; ++i)
    {
        ll_push(&ll, (double)i);
        dll_push(&dll, (double)i);
    }
    start = clock();
    for (uint32_t i = 0; i < n; ++i)
        if (ll_popBack(&ll, &ret) == 0) checksum += ret;
    times[4][0] = seconds(start);
    start = clock();
    for (uint32_t i = 0; i < n; ++i)
        if (dll_popBack(&dll, &ret) == 0) checksum += ret;
    times[4][1] = seconds(start);
    printf("\n===== PERFORMANCE-VERGLEICH =====\n");
    printf("N = %u Elemente, mittlere Operationen = %u\n", n, middleOperations);
    printf("%-21s %12s %12s %12s\n", "Operation", "LL (s)", "DLL (s)", "LL / DLL");
    for (uint32_t i = 0; i < 5; ++i)
    {
        printf("%-21s %12.6f %12.6f ", names[i], times[i][0], times[i][1]);
        if (times[i][1] > 0.0) printf("%11.2fx\n", times[i][0] / times[i][1]);
        else puts("   n/a");
    }
    printf("Pruefsumme (gegen Optimierung): %.0f\n", checksum);
    printf("Erwartung: Anfang O(1), Ende anhaengen/entfernen LL O(N), DLL O(1).\n");
    printf("Suche ab Head bleibt bei beiden O(N); DLL hat Vorteile bei Zugriffen nahe Tail.\n");
    ll_clear(&ll);
    dll_clear(&dll);
}

int main(void)
{
    double ret = 0;
    dll_ptr_t list = {0};
    check("pop bei leerer DLL", dll_pop(&list, &ret) == -1);
    check("popBack bei leerer DLL", dll_popBack(&list, &ret) == -1);
    check("removeAt bei leerer DLL", dll_removeAt(&list, 0) == -1);

    puts("\n===== FUNKTIONSTEST DLL =====");
    dll_push(&list, 2);
    print_dll("Nach push 2", &list);
    dll_push(&list, 1);
    check("push vorne", equals(&list, (double[]){1, 2}, 2));
    dll_pushBack(&list, 3);
    print_dll("Nach push vorne und pushBack 3", &list);
    check("pushBack hinten", equals(&list, (double[]){1, 2, 3}, 3));
    check("addAt vorne", dll_addAt(&list, 0, 0) == 0 && equals(&list, (double[]){0, 1, 2, 3}, 4));
    check("addAt Mitte", dll_addAt(&list, 1.5, 2) == 0 && equals(&list, (double[]){0, 1, 1.5, 2, 3}, 5));
    check("addAt hinter Ende", dll_addAt(&list, 4, 100) == 0 && equals(&list, (double[]){0, 1, 1.5, 2, 3, 4}, 6));
    print_dll("Nach addAt", &list);
    check("removeAt vorne", dll_removeAt(&list, 0) == 0 && equals(&list, (double[]){1, 1.5, 2, 3, 4}, 5));
    check("removeAt Mitte", dll_removeAt(&list, 1) == 0 && equals(&list, (double[]){1, 2, 3, 4}, 4));
    check("removeAt hinten", dll_removeAt(&list, 3) == 0 && equals(&list, (double[]){1, 2, 3}, 3));
    print_dll("Nach removeAt", &list);
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
    print_dll("Export-Ausgabe DLL", &list);
    check("export als Array", array != NULL && size == 3 && array[0] == 1.25 && array[1] == 2 && array[2] == 3);
    free(array);
    check("popBack liefert Wert", dll_popBack(&list, &ret) == 0 && ret == 3 && equals(&list, (double[]){1.25, 2}, 2));
    check("pop liefert Wert", dll_pop(&list, &ret) == 0 && ret == 1.25 && equals(&list, (double[]){2}, 1));
    check("popBack letzter Knoten", dll_popBack(&list, &ret) == 0 && ret == 2 && equals(&list, NULL, 0));
    dll_clear(&list);
    array = dll_export(&list, &size);
    check("export leere Liste", array == NULL && size == 0);
    free(array);

    // Auch die LL in derselben Anwendung schrittweise vorfuehren.
    puts("\n===== FUNKTIONSTEST LL =====");
    ll_t *single = NULL;
    ll_push(&single, 2.25);
    print_ll("Nach push vorne", single);
    ll_pushBack(&single, 3.50);
    print_ll("Nach pushBack hinten", single);
    check("LL addAt", ll_addAt(&single, 2.75, 1) == 0);
    print_ll("Nach addAt Mitte", single);
    check("LL search", ll_search(single, 2.75) == 1);
    check("LL removeAt", ll_removeAt(&single, 1) == 0);
    print_ll("Nach removeAt Mitte", single);
    check("LL popBack", ll_popBack(&single, &ret) == 0 && ret == 3.50);
    print_ll("Nach popBack", single);
    check("LL pop", ll_pop(&single, &ret) == 0 && ret == 2.25);
    ll_push(&single, 1.25);
    ll_clear(&single);
    check("LL clear", single == NULL);
    print_ll("Nach clear", single);
    benchmark();
    printf("\nTests: %d, bestanden: %d, fehlgeschlagen: %d\n", tests, tests - failed, failed);
    return failed == 0 ? 0 : 1;
}
