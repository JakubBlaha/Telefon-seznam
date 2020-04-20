#ifndef DATA_H_INCLUDED
#define DATA_H_INCLUDED

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

typedef unsigned int uint;

#define MAXLEN 21

/** \brief Jeden prvek v telefonním seznamu. */
typedef struct _zaznam
{
    char jmeno[MAXLEN]; /**< Jméno osoby */
    uint cislo;         /**< Telefonní číslo */
    bool platny;        /**< True znamená, že je prvek platný, false, že je smazaný. */
} Tzaznam;

/** \brief Struktura reprezentující telefonní seznam, tedy pole záznamů. */
typedef struct
{
    Tzaznam zaznam[MAXSEZNAM]; /**< Pole záznamů. */
    uint delkaSerazene;        /**< Délka seřazené části pole. Zároveň index začátku oblasti přeplnění. */
    uint pocet;                /**< Počet využitých prvků pole (včetně smazaných). */
    uint pocetSmazanych;       /**< Aktuální počet smazaných prvků. */
    long nalezeny;             /**< Index posledního nalezeného prvku. */
} Tseznam;

/** \brief Vyrobí prázdný seznam.
 *
 * \param void
 * \return Tseznam Vrací prázdný seznam.
 */
Tseznam prazdnySeznam(void)
{
    // Vrátíme pointer na strukturu seznam typu Tseznam
    Tseznam seznam;
    return seznam;
}

/** \brief Přemaže existující seznam.
 *
 * \param seznam Tseznam* Existující seznam předávaný odkazem.
 */
void resetujSeznam(Tseznam *seznam)
{
    // Nemusíme nic přemazávat, stačí nastavit pocet záznamů na 0
    seznam->pocet = 0;

    for (int i = 0; i < MAXSEZNAM; i++)
    {
        seznam -> zaznam[i].platny = false;
    }

    // Resetujeme i hledání
    resetujHledani(seznam);
}

/** \brief Vloží nový záznam do telefonního seznamu. Nekontroluje, jestli už takový záznam existuje.
 *
 * Vložení se nemusí povést, když v seznamu už není dostatek místa.
 *
 * \param seznam Tseznam* Seznam předávaný odkazem.
 * \param jmeno char*  Jméno osoby (bude se kopírovat do seznamu).
 * \param cislo uint   Telefonní číslo.
 * \return bool Vrací true, když se vložení povede, jinak vrací false.
 */
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

/** \brief Najde další telefonní číslo pro zadané jméno.
 *
 * Každé jméno může mít uloženo několik čísel.
 * Hledání začíná od začátku, pokud ještě žádné hledání neproběhlo, nebo byla
 * před hledáním zavolána funkce resetujHledani(). V opačném případě začíná od
 * posledního výsledku.
 *
 * Pozor! Pokud se další hledání odehraje pro jiné jméno, nemusí být výsledek
 * hledání zcela správný.
 *
 * Poznámka: Pokud se implementace seznamu změní, může mít tato funkce pořád
 * stejné rozhraní.
 *
 * \param seznam Tseznam* Seznam předávaný odkazem.
 * \param jmeno char*  Jméno, podle kterého se bude v seznamu hledat.
 * \param cislo uint*  Nalezené telefonní číslo. Proměnná předávaná odkazem.
 *                     Výsledek je platný, když funkce vrátí true.
 * \return bool Vrací true, když funkce našla záznam, jinak vrací false a hodnota
 *              v parametru cislo nemá smysl.
 */
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

/** \brief Resetuje hledání, tj. nastaví index posledního nalezeného prvku na -1 (tj. nenalezeno).
 *
 * Index začátku dalšího hledání je položka nalezeny v seznamu.
 *
 * \param seznam Tseznam* Seznam předávaný odkazem.
 */
void resetujHledani(Tseznam *seznam)
{
    seznam->nalezeny = -1;
}

/** \brief Odebere poslední nalezený záznam ze seznamu.
 *
 * Index posledního nalezeného záznamu je v položce nalezeny v seznamu. Pokud je
 * tato hodnota neplatná (nastavená na -1), nic se neodebere a funkce vrátí false.
 *
 * Volá funkci resetujHledani().
 *
 * \param seznam Tseznam* Seznam předávaný odkazem.
 * \return bool Vrací true, když dojde k odebrání záznamu, jinak vrací false.
 */
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

/** \brief Fyzicky provede nahromaděné změny (mazání prvků, seřazení a sloučení s oblastí přeplnění).
 *
 * Volá funkci resetujHledani().
 *
 * \param seznam Tseznam* Seznam předávaný odkazem.
 */
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

#endif // DATA_H_INCLUDED
