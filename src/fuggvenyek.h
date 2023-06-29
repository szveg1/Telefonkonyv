#ifndef FUGGVENYEK_H_INCLUDED
#define FUGGVENYEK_H_INCLUDED

#include "adatstrukturak.h"
#include <stdio.h>
#include <stdbool.h>


#endif // FUGGVENYEK_H_INCLUDED

/**
 *  Tetszoleges hosszusagu stringet beolvaso fuggveny.
 *
 *  Nincs bemenete.
 *
 *  Visszateresi erteke a beolvasott karaktertomb (string).
 */
char *tetsz_hossz_str();


/**
 *  Fajlt betolto fuggveny.
 *
 *  Nincs bemenete.
 *
 *  File-pointerrel ter vissza.
 */
FILE* fajl_betolt();


/**
 *  TXT fileban tarolt nevjegyek szamat megallapito fuggveny.
 *
 *  Bementkent a TXT file-ra mutato pointert kap.
 *
 *  Visszateresi erteke egy egesz szam
 */
int nevjegyek_szama(FILE *pt);


/**
 *  Adatok szamara memoriateruletet foglalo fuggveny.
 *
 *  Bemenetkent a dinamikus tombre mutato pointert, es a kivant meretet kapja meg
 *
 *  Visszateresi erteke igaz vagy hamis, annak fuggvenyeben, hogy sikerult e a memoriafoglalas.
 */
bool dintomb_foglal(Dintomb *dt, int const meret);


/**
 *  Adatokat tartalmazo dinamikus tombot felszabadito fuggveny.
 *
 *  Bementkent a dinamikus tombre mutato pointert kapja meg.
 *
 *  Nincs visszateresi erteke.
 */
void dintomb_szabadit(Dintomb *dt);


/**
 *  Adatokat tartalmazo dinamikus tombot TXT fajlbol adattal feltolto fuggveny.
 *
 *  Bemenetkent egy TXT-file-ra es a dinamikus tombre mutato pointert kapja meg.
 *
 *  Nincs visszateresi erteke.
 */
void dintomb_feltolt(FILE *pt, Dintomb *dt);


/**
 *  Adatokat tartalmazo dinamikus tombot atmeretezo fuggveny.
 *
 *  Bementkent megkapja a dinamikus tombre mutato pointert, es a kivant uj meretet.
 *
 *  Visszateresi erteke igaz vagy hamis, annak fuggvenyeben, hogy sikerult-e az atmeretezes.
 */
bool dintomb_atmeretez(Dintomb *dt, int ujmeret);


/**
 *  Egy szemely fontosabb adatait (nev, foglalkozas, tel.szam) kiiro fuggveny.
 *
 *  Bemenetkent a dinamikus tomb memoriacimet tartalmazo valtozot es a nevjegy indexet kapja meg.
 *
 *  Nincs visszateresi erteke.
 */
void nevjegy_kiir(Tomb bemenet, int i);


/**
 *  Egy szemely minden adatat kiiro fuggveny.
 *
 *  Bemenetkent a dinamikus tomb memoriacimet tartalmazo valtozot es a nevjegy indexet kapja meg.
 *
 *  Nincs visszateresi erteke.
 */
void nevjegy_kiir_reszletes(Tomb bemenet, int i);


/**
 *  Egy szemely minden adatat torlo fuggveny.
 *
 *  Bemenetkent a dinamikus tomb memoriacimet tartalmazo valtozot es a nevjegy indexet kapja meg.
 *
 *  Nincs visszateresi erteke.
 */
void nevjegy_torol(Tomb bemenet, int idx);


/**
 *  Megfelelo formatumu nev megadasat iranyito fuggveny.
 *
 *  Bemenetkent a dinamikus tomb memoriacimet tartalmazo valtozot es a modositani kivant nevjegy indexet kapja meg.
 *
 *  Nincs visszateresi erteke
 */
void nev_megad(Tomb bemenet, int idx);


/**
 *  Megfelelo formatumu foglalkozas megadasat iranyito fuggveny.
 *
 *  Bemenetkent a dinamikus tomb memoriacimet tartalmazo valtozot es a modositani kivant nevjegy indexet kapja meg.
 *
 *  Nincs visszateresi erteke
 */
void foglalkozas_megad(Tomb bemenet, int idx);


/**
 *  Megfelelo formatumu lakcim megadasat iranyito fuggveny.
 *
 *  Bemenetkent a dinamikus tomb memoriacimet tartalmazo valtozot es a modositani kivant nevjegy indexet kapja meg.
 *
 *  Nincs visszateresi erteke
 */
void lakcim_megad(Tomb bemenet, int idx);


/**
 *  Megfelelo formatumu telefonszam megadasat iranyito fuggveny.
 *
 *  Bemenetkent a dinamikus tomb memoriacimet tartalmazo valtozot es a modositani kivant nevjegy indexet kapja meg.
 *
 *  Nincs visszateresi erteke
 */
void telefonszam_megad(Tomb bemenet, int idx);


/**
 *  Megfelelo formatumu email-cim megadasat iranyito fuggveny.
 *
 *  Bemenetkent a dinamikus tomb memoriacimet tartalmazo valtozot es a modositani kivant nevjegy indexet kapja meg.
 *
 *  Nincs visszateresi erteke
 */
void email_megad(Tomb bemenet, int idx);


/**
 *  String tartalmat ellenorzo fuggveny.
 *  I-O muveleteknel szukseges, a nem megadott adatok helyen megjeleno "(null)" string kiszuresere.
 *
 *  Bemenetkent egy stringet kap.
 *
 *  Visszateresi erteke igaz vagy hamis.
 */
bool null_str(char *str);


/**
 *  Fajlt menteshez megnyito fuggveny.
 *
 *  Nincs bemenete.
 *
 *  Visszateresi erteke a megnyitni kivant fajlra mutato file-pointer.
 */
FILE* fajl_ment();


/**
 *  String kereso fuggveny, alkalmas wildcard keresesre is.
 *
 *  Bemenetkent megkapja a stringet amit keresunk, a stringet amiben keresunk
 *  es ket egesz szamot, amik megadjak, hogy melyi kkaraktertombnel melyik
 *  indextol hasonlitjuk ossze a stringeket
 *
 *  Visszateresi erteke igaz vagy hamis.
 */
bool str_keres(char *keresett, char *hol_keres, int k, int h);


/**
 *  Egy szemely adatait vCard formatumu fajlba mento fuggveny.
 *
 *  Bemenetkent a dinamikus tomb memoriacimet tartalmazo valtozot es a nevjegy indexet kapja meg.
 *
 *  Nincs visszateresi erteke.
 */
void vcard_ment(Tomb bemenet, int idx);


/**
 *  Egy szemely adatait vCard formatumu fajlbol kiolvaso es a dinamikus tombbe beiro fuggveny.
 *
 *  Bemenetkent a dinamikus tomb memoriacimet tartalmazo valtozot kapja meg.
 *
 *  Nincs visszateresi erteke.
 */
void vcard_beolvas(Tomb bemenet);
