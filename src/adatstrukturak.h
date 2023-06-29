#ifndef ADATSTRUKTURAK_H_INCLUDED
#define ADATSTRUKTURAK_H_INCLUDED

#include <stdbool.h>



#endif // ADATSTRUKTURAK_H_INCLUDED



/// Egy szemely adatait es az adatokhoz tartozo, fuggvenyeknel hasznalt flageket tartalmaz
typedef struct Adatok{
    char *nev;                  ///< A szemely neve.
    char *foglalkozas;          ///< A szemely foglalkozása.
    char *lakcim;               ///< A szemely lakcime.
    char *telefonszam;          ///< A szemely telefonszama.
    char *email;                ///< A szemely email-cime.
    bool n_megadva;             ///< Fuggvenyeknel hasznalt flag, mutatja, hogy meg lett-e mar adva az adott adat.
    bool f_megadva;             ///< Fuggvenyeknel hasznalt flag, mutatja, hogy meg lett-e mar adva az adott adat.
    bool l_megadva;             ///< Fuggvenyeknel hasznalt flag, mutatja, hogy meg lett-e mar adva az adott adat.
    bool t_megadva;             ///< Fuggvenyeknel hasznalt flag, mutatja, hogy meg lett-e mar adva az adott adat.
    bool e_megadva;             ///< Fuggvenyeknel hasznalt flag, mutatja, hogy meg lett-e mar adva az adott adat.
}Adatok;

/// Egy adatokat tarolo tombot es annak meretet tarolja
typedef struct Dintomb{
    Adatok *adat;              ///< Adatok tombje
    int meret;                  ///< A tomb merete
} Dintomb;

/// Dinamikus tomb cimet tarolja, konnyebbe teve a munkat veluk
typedef struct Tomb{
    Dintomb *dt;                ///< Dintomb cime
    int opcio;                  ///< Semmire nincs hasznalva, de ha el van tavolitva nem fut le a program
} Tomb;

