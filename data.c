#include "data.h"

Tseznam prazdnySeznam(void)
{
    // Vrátíme pointer na strukturu seznam typu Tseznam
    Tseznam seznam;
    return seznam;
}

void resetujSeznam(Tseznam *seznam)
{
    // Nemusíme nic přemazávat, stačí nastavit pocet záznamů na 0
    seznam->pocet = 0;

    for (int i = 0; i < MAXSEZNAM; i++)
    {
        seznam->zaznam[i].platny = false;
    }

    // Resetujeme i hledání
    resetujHledani(seznam);
}

bool vlozZaznam(Tseznam *seznam, char jmeno[], uint cislo)
{
    // Pokud je už seznam plný, vrátíme false a skončíme
    if (seznam->pocet >= MAXSEZNAM)
    {
        return false;
    }

    // Přidáme nový záznam na pozici délky, což je poslední index + 1
    // ... respektive on už tam je, akorát musíme změnit, co je v něm

    // Napřed si vezmeme pointer na ten záznam z pole. Pointer si bereme proto,
    // abychom rovnou měnili to, co je v seznamu a nevztvářeli kopii
    Tzaznam *p = &(seznam->zaznam[seznam->pocet]);

    // Změníme jméno
    strcpy(p->jmeno, jmeno);

    // Změníme telefonní číslo
    p->cislo = cislo;

    // Nastavíme zaznam na platný
    p->platny = true;

    // Zvýšíme počet záznamů
    seznam->pocet++;

    printf("%d", seznam->pocet);

    // Vrátíme, že se to povedlo
    return true;
}

bool najdiDalsiCislo(Tseznam *seznam, char jmeno[], uint *cislo)
{
    Tzaznam zaznam;

    for (int i = seznam->nalezeny + 1; i < MAXLEN; i++)
    {
        zaznam = seznam->zaznam[i];

        if (strcmp(zaznam.jmeno, jmeno) == 0)
        {
            (*cislo) = zaznam.cislo;
            seznam->nalezeny = i;
            return true;
        }
    }

    return false;
}

void resetujHledani(Tseznam *seznam)
{
    seznam->nalezeny = -1;
}

bool odeberPosledniNalezenyZaznam(Tseznam *seznam)
{
    // Vrátíme false, pokud se nic předtím nenalezlo
    if (seznam->nalezeny == -1)
    {
        return false;
    }

    // Nastavíme platnost záznamu na false
    seznam->zaznam[seznam->nalezeny].platny = false;

    // Vrátíme, že se to povedlo
    return true;
}

void vymena(Tseznam *seznam, int a, int b)
{
    Tzaznam pom = seznam->zaznam[a];
    seznam->zaznam[a] = seznam->zaznam[b];
    seznam->zaznam[b] = pom;
}

void sort(Tseznam *seznam)
{
    int minIndex = 0;

    for (int i = 0; i < MAXSEZNAM; i++)
    {
        for (int j = i + 1; j < MAXSEZNAM; j++)
        {
            printf("%s, %s\n", seznam->zaznam[j].jmeno, seznam->zaznam[minIndex].jmeno);
            if (strcmp(seznam->zaznam[j].jmeno, seznam->zaznam[minIndex].jmeno) > 0)
            {
                minIndex = j;
            }
        }

        vymena(seznam, i, minIndex);
    }
}

void aktualizujSeznam(Tseznam *seznam)
{
    // Zresetujeme hledání
    resetujHledani(seznam);

    // Přesuneme platné záznamy na místa těch neplatných
    puts("Presunuji...");

    int indexPlatny = MAXSEZNAM;
    int indexNeplatny = -1;

    while (true)
    {
        // Najdeme index dalšího platného prvku zprava
        while (seznam->zaznam[indexPlatny].platny != true)
        {
            indexPlatny--;
        }

        // Najdeme index dalšího neplatného prvku zleva
        while (seznam->zaznam[indexNeplatny].platny != false)
        {
            indexNeplatny++;
        }

        // Pokud jsme někde vylezli ze seznamu, nebo se indexy skřížili, tak toho necháme
        if (indexPlatny < 0 || indexNeplatny >= MAXSEZNAM || indexNeplatny >= indexPlatny)
        {
            break;
        }

        // Ten platný dáme na místo toho neplatného
        seznam->zaznam[indexNeplatny] = seznam->zaznam[indexPlatny];

        // Původní platný zneplatníme
        seznam->zaznam[indexPlatny].platny = false;
    }

    // Seřadíme to. Třeba selection sortem. Nic jinýho se mi momentálně nechce vymýšlet.
    puts("Sortim...");
    sort(seznam);
}