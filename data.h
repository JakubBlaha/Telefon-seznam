#ifndef DATA_H_INCLUDED
#define DATA_H_INCLUDED

#include <stdbool.h>
#include <string.h>
#include <stdio.h>

typedef unsigned int uint;

#define MAXLEN 21

/** \brief Jeden prvek v telefonním seznamu. */
typedef struct _zaznam
{
    char jmeno[MAXLEN]; /**< Jméno osoby */
    uint cislo;         /**< Telefonní číslo */
    bool platny;        /**< True znamená, že je prvek platný, false, že je smazaný. */
} Tzaznam;

#define MAXSEZNAM 10

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
Tseznam prazdnySeznam(void);

/** \brief Přemaže existující seznam.
 *
 * \param seznam Tseznam* Existující seznam předávaný odkazem.
 */
void resetujSeznam(Tseznam *seznam);

/** \brief Vloží nový záznam do telefonního seznamu. Nekontroluje, jestli už takový záznam existuje.
 *
 * Vložení se nemusí povést, když v seznamu už není dostatek místa.
 *
 * \param seznam Tseznam* Seznam předávaný odkazem.
 * \param jmeno char*  Jméno osoby (bude se kopírovat do seznamu).
 * \param cislo uint   Telefonní číslo.
 * \return bool Vrací true, když se vložení povede, jinak vrací false.
 */
bool vlozZaznam(Tseznam *seznam, char jmeno[], uint cislo);

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
bool najdiDalsiCislo(Tseznam *seznam, char jmeno[], uint *cislo);

/** \brief Resetuje hledání, tj. nastaví index posledního nalezeného prvku na -1 (tj. nenalezeno).
 *
 * Index začátku dalšího hledání je položka nalezeny v seznamu.
 *
 * \param seznam Tseznam* Seznam předávaný odkazem.
 */
void resetujHledani(Tseznam *seznam);

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
bool odeberPosledniNalezenyZaznam(Tseznam *seznam);

/** \brief Fyzicky provede nahromaděné změny (mazání prvků, seřazení a sloučení s oblastí přeplnění).
 *
 * Volá funkci resetujHledani().
 *
 * \param seznam Tseznam* Seznam předávaný odkazem.
 */
void aktualizujSeznam(Tseznam *seznam);

#endif // DATA_H_INCLUDED
