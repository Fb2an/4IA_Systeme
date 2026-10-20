
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

void printBinary(uint16_t value);
void printValues(uint16_t a, uint16_t b);
void waitForEnter(void);
void clearInputBuffer(void);

int main(void)
{
    int choice = -1;
    int bit;
    uint16_t a = 0;
    uint16_t b = 0;

    printf("Druecken Sie Enter zum Starten des Programms...");
    getchar();

    while (choice != 0)
    {
        printf("\n[1] A eingeben (Hex)\n");
        printf("[2] B eingeben (Hex)\n");
        printf("[3] A = A + B\n");
        printf("[4] A = A UND B\n");
        printf("[5] A = A ODER B\n");
        printf("[6] A = A XOR B\n");
        printf("[7] A = NICHT A\n");
        printf("[8] A um B Stellen nach links schieben\n");
        printf("[9] A um B Stellen nach rechts schieben\n");
        printf("[10] Ein Bit in A setzen\n");
        printf("[11] Ein Bit in A loeschen\n");
        printf("[12] Ein Bit in A umschalten\n");
        printf("[13] Ein Bit in A pruefen\n");
        printf("[0] Beenden\n");

        printf("\nOption: ");
        fflush(stdout);

        if (scanf("%d", &choice) != 1)
        {
            if (feof(stdin))
                break;

            printf("Ungueltige Eingabe!\n");
            clearInputBuffer();
            waitForEnter();
            continue;
        }

        clearInputBuffer();

        if (choice < 0 || choice > 13)
        {
            printf("Ungueltige Auswahl!\n");
            waitForEnter();
            continue;
        }

        switch (choice)
        {
            case 1:
            {
                printf("Geben Sie den Wert fuer A ein (Hex): ");

                if (scanf("%" SCNx16, &a) != 1)
                {
                    printf("Ungueltige Eingabe!\n");
                }

                clearInputBuffer();
                break;
            }

            case 2:
            {
                printf("Geben Sie den Wert fuer B ein (Hex): ");

                if (scanf("%" SCNx16, &b) != 1)
                {
                    printf("Ungueltige Eingabe!\n");
                }

                clearInputBuffer();
                break;
            }

            case 3:
                a = a + b;
                break;

            case 4:
                a = a & b;
                break;

            case 5:
                a = a | b;
                break;

            case 6:
                a = a ^ b;
                break;

            case 7:
                a = ~a;
                break;

            case 8:
                if (b < 16)
                    a = a << b;
                else
                    printf("Ungueltige Verschiebung!\n");
                break;

            case 9:
                if (b < 16)
                    a = a >> b;
                else
                    printf("Ungueltige Verschiebung!\n");
                break;

            case 10:
            case 11:
            case 12:
            case 13:
            {
                printf("Geben Sie die Bitposition (0-15) ein: ");

                if (scanf("%d", &bit) != 1)
                {
                    printf("Ungueltige Eingabe!\n");
                    clearInputBuffer();
                    break;
                }

                clearInputBuffer();

                if (bit < 0 || bit > 15)
                {
                    printf("Ungueltige Bitposition!\n");
                    break;
                }

                switch (choice)
                {
                    case 10:
                        a |= (1U << bit);
                        break;

                    case 11:
                        a &= ~(1U << bit);
                        break;

                    case 12:
                        a ^= (1U << bit);
                        break;

                    case 13:
                        if (a & (1U << bit))
                            printf("Bit %d ist 1\n", bit);
                        else
                            printf("Bit %d ist 0\n", bit);
                        break;
                }

                break;
            }

            case 0:
                printf("Programm beendet.\n");
                break;
        }

        if (choice == 0)
            break;

        printValues(a, b);
        waitForEnter();
    }

    return 0;
}

void printBinary(uint16_t value)
{
    for (int i = 15; i >= 0; i--)
    {
        printf("%u", (unsigned)((value >> i) & 1U));

        if (i % 4 == 0 && i != 0)
            printf(" ");
    }
}

void printValues(uint16_t a, uint16_t b)
{
    printf("\nCurrent Values:\n");

    printf("A:\tHex: %04" PRIx16 "\n\tBin: ", a);
    printBinary(a);
    printf("\n");

    printf("B:\tHex: %04" PRIx16 "\n\tBin: ", b);
    printBinary(b);
    printf("\n");
}

void clearInputBuffer(void)
{
    int c;

    while ((c = getchar()) != '\n' && c != EOF)
    {
    }
}

void waitForEnter(void)
{
    printf("\nDruecken Sie Enter, um fortzufahren...");
    fflush(stdout);

    clearInputBuffer();
}
