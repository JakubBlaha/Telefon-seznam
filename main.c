/*
 * C-cvičení
 *
 * Téma 11-vyhledavani
 * Vyhledávání v telefonním seznamu
 *
// TODO 1: Podepiš se
 * Autor: Adam Špiřík, Jakub Bláha
 *
 * Kostra programu - Copyright (c) David Martinek, 2020
 */

// TODO 2: Popřemýšlej nad zadáním. Rozšiř ho, specifikuj ho. Ujasni si ho.
//Zadání: Vyrob program s modulem pro efektivní práci s telefonním seznamem.

//Jaké operace budu chtít dělat?
// -> Přidávat, oděbírat, měnit

//S jakými hodnotami budu pracovat?
// -> Jméno, telefonní číslo

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <math.h>
#include <float.h>

// TODO 3: Založ si nový modul (soubory data.h a data.c: File-New-File...)
#include "data.h"

// TODO 4. Testuj postupně operace, které budeš vytvářet v modulu.

void testInicializace(void)
{
}

void testVlozeni(void)
{
}

void testHledani(void)
{
}

void clear()
{
    // Clearne konzoli
    system("cls");
}

void vypisMenu()
{
    clear();

    char menuString[] =
        "Ukoncit .............. 0\n"
        "Vypsat seznam ........ 1\n"
        "Pridat zaznam ........ 2\n"
        "Vyhledat jmeno ....... 3\n"
        "Odebrat posl. nalezeny 4\n"
        "Aktualizovat seznam .. 5\n";

    printf(menuString);
}

int nactiVolbu()
{
    printf("\nVase volba: ");

    fflush(stdin);

    int volba;
    scanf("%d", &volba);

    return volba;
}

void enterProPokracovani()
{
    fflush(stdin);
    printf("\nStisknete enter pro pokracovani...");
    getchar();
}

void vypisZaznam(int index, Tzaznam zaznam)
{
    printf("Zaznam na pozici: %d, Jmeno: %-20s Cislo: %9d\n", index, zaznam.jmeno, zaznam.cislo);
}

void vypisSeznam(Tseznam *seznam)
{
    Tzaznam zaznam;

    // Vypíšeme...
    for (int i = 0; i < seznam->pocet; i++)
    {
        zaznam = seznam->zaznam[i];

        // Pokud záznam není platný, přeskočíme ho a nebudeme ho vypisovat
        // if (!zaznam.platny)
        // {
        //     continue;
        // }

        // Jinak ho vypíšeme
        vypisZaznam(i, seznam->zaznam[i]);
    }

    // A počkáme, než uživatel zmáčkne enter
    enterProPokracovani();
}

void pridatZaznam(Tseznam *seznam)
{
    // Necháme uživatele zadat jméno
    printf("Zadejte jmeno: ");

    char jmeno[MAXLEN];
    scanf("%20s", jmeno);

    // Necháme uživatele zadat číslo
    printf("Zadejte telefoni cislo: ");

    uint cislo;
    scanf("%d", &cislo);

    bool success = vlozZaznam(seznam, jmeno, cislo);

    if (success)
    {
        puts("Zaznam pridan.");
    }
    else
    {
        puts("Nepodarilo se pridat zaznam.");
    }
}

void vyhledat(Tseznam *seznam)
{
    printf("Zadejte jmeno, ktere chcete vyhledat: ");

    char jmeno[MAXLEN];
    scanf("%20s", jmeno);

    printf("Vyhledavam %s...\n", jmeno);

    // Zresetujeme progress hledání
    resetujHledani(seznam);

    // Vytvoříme čislo, abychom na nej mohli předat odkaz z funkce najdiDalsiCislo
    uint cislo;

    while (true)
    {
        bool success = najdiDalsiCislo(seznam, jmeno, &cislo);

        // Pokud nebylo nalezeno žádné číslo, dáme vědět uživateli
        if (!success)
        {
            puts("Zadna dalsi data.");
            break;
        }

        // Vypiseme vysledek
        printf("Nalezeno cislo: %d\n", cislo);
    }

    puts("Vyhledavani skoncilo.");
    enterProPokracovani();
}

void odebratPosledniNalezeny(Tseznam *seznam)
{
    puts("Odebirani posledniho nalezeneho zaznamu...");

    bool success = odeberPosledniNalezenyZaznam(seznam);

    if (success)
    {
        puts("Povedlo se.");
    }
    else
    {
        puts("Nepovedlo se.");
    }

    enterProPokracovani();
}

void aktualizovatSeznam(Tseznam *seznam)
{
    puts("Aktualizuji seznam...");

    aktualizujSeznam(seznam);

    enterProPokracovani();
}

int main(void)
{
    // Vytvoříme si seznam
    Tseznam seznam = prazdnySeznam(); // TODO udelat to jako pointer

    // Zresetujeme ho
    resetujSeznam(&seznam);

    // Zaplníme ho pro snadnější testování
    vlozZaznam(&seznam, "open", 1234);
    vlozZaznam(&seznam, "open", 4321);
    vlozZaznam(&seznam, "source", 1111);
    vlozZaznam(&seznam, "GitHub", 2222);

    int volba;

    while (volba != 0) // Když to bude 0, tak skončíme
    {                  // Budeme vypisovat menu pořád dokola
        vypisMenu();
        volba = nactiVolbu();

        switch (volba)
        {
        case 0:
            break;

        case 1:
            vypisSeznam(&seznam);
            break;

        case 2:
            pridatZaznam(&seznam);
            break;

        case 3:
            vyhledat(&seznam);
            break;

        case 4:
            odebratPosledniNalezeny(&seznam);
            break;

        case 5:
            aktualizovatSeznam(&seznam);
            break;

        default:
            break;
        }
    }

    return 0;
}
