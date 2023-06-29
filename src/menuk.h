#ifndef MENUK_H_INCLUDED
#define MENUK_H_INCLUDED



#endif // MENUK_H_INCLUDED

#include "fuggvenyek.h"

/**
 *  Fomenut meghivo fuggveny.
 *
 *  Bemenetkent a dinamikus tomb cimet tarolo valtozot kap.
 *
 *  Visszateresi erteke nincs.
 */
void fomenu(Tomb bemenet);


/**
 *  Uj telefonkonyvet letrehozo fuggveny.
 *
 *  Bemenetkent a dinamikus tomb cimet tarolo valtozot kap.
 *
 *  Visszateresi erteke nincs.
 */
void uj_tkonyv(Tomb bemenet);


/**
 *  Programbol kilepo fuggveny.
 *
 *  Bemenetkent a dinamikus tomb cimet tarolo valtozot kap.
 *
 *  Visszateresi erteke nincs.
 */
void kilepes(Tomb bemenet);


/**
 *  Uj nevjegy megadasat iranyito fuggveny.
 *
 *  Bemenetkent a dinamikus tomb cimet tarolo valtozot kap.
 *
 *  Visszateresi erteke nincs.
 */
void nevjegy_felvesz(Tomb bemenet);


/**
 *  Telefonkonyvet TXT fajlbol megnyito, illetve megnyitott telefonkonyvet kezelo fuggveny.
 *
 *  Bemenetkent a dinamikus tomb cimet tarolo valtozot kap.
 *
 *  Visszateresi erteke nincs.
 */
void tkonyv_menu(Tomb bemenet);


/**
 *  Telefonkonyv adatait modosito fuggveny.
 *
 *  Bemenetkent a dinamikus tomb cimet tarolo valtozot kap.
 *
 *  Visszateresi erteke nincs.
 */
void tkonyv_modosit(Tomb bemenet);


/**
 *  Telefonkonyv adatait TXT fajlba mento fuggveny.
 *
 *  Bemenetkent a dinamikus tomb cimet tarolo valtozot kap.
 *
 *  Visszateresi erteke nincs.
 */
void tkonyv_ment(Tomb bemenet);


/**
 *  Oldalankent het nevjegy rovid valtozatat kiiro fuggveny.
 *
 *  Bemenetkent megkapja a dinamikus tomb cimet tarolo valtozot, az oldalszamot
 *  es hogy a nevjegy modositasahoz keresunk-e, vagy csak reszletesen listazni akarjuk a
 *  a szemelyek adatait.
 *
 *  Visszateresi erteke nincs.
 */
void nevjegyek_listaz(Tomb bemenet, int n, bool modositas);


/**
 *  Nevjegy modositasat iranyito fuggveny.
 *
 *  Bemenetkent a dinamikus tomb cimet tarolo valtozot es a nevjegy indexet kapja meg.
 *
 *  Visszateresi erteke nincs.
 */
void nevjegy_modosit(Tomb bemenet, int idx);

/**
 *  Modositashoz valo keresest iranyito fuggveny.
 *
 *  Bemenetkent a dinamikus tomb cimet tarolo valtozot kapja meg.
 *
 *  Visszateresi erteke nincs.
 */
void modositas_mod(Tomb bemenet);


/**
 *  Keresest iranyito fuggveny.
 *
 *  Bemenetkent a dinamikus tomb cimet tarolo valtozot es a modositast jelzo flaget kapja meg.
 *
 *  Visszateresi erteke nincs.
 */
void kereses(Tomb bemenet, bool modositas);


/**
 *  Nev szerint kereso fuggveny.
 *
 *  Bemenetkent a dinamikus tomb cimet tarolo valtozot, az oldalszamot, a modositast jelzo flaget,
 *  a keresett stringet es a talalatok szamat kapja meg.
 *
 *  Visszateresi erteke nincs.
 */
void n_keres(Tomb bemenet, int n, bool modositas, char *nev, int talalatok);


/**
 *  Foglalkozas szerint kereso fuggveny.
 *
 *  Bemenetkent a dinamikus tomb cimet tarolo valtozot, az oldalszamot, a modositast jelzo flaget,
 *  a keresett stringet es a talalatok szamat kapja meg.
 *
 *  Visszateresi erteke nincs.
 */
void f_keres(Tomb bemenet, int n, bool modositas, char *foglalkozas, int talalatok);


/**
 *  Lakcim szerint kereso fuggveny.
 *
 *  Bemenetkent a dinamikus tomb cimet tarolo valtozot, az oldalszamot, a modositast jelzo flaget,
 *  a keresett stringet es a talalatok szamat kapja meg.
 *
 *  Visszateresi erteke nincs.
 */
void l_keres(Tomb bemenet, int n, bool modositas, char *lakcim, int talalatok);


/**
 *  Telefonszam szerint kereso fuggveny.
 *
 *  Bemenetkent a dinamikus tomb cimet tarolo valtozot, az oldalszamot, a modositast jelzo flaget,
 *  a keresett stringet es a talalatok szamat kapja meg.
 *
 *  Visszateresi erteke nincs.
 */
void t_keres(Tomb bemenet, int n, bool modositas, char *telefonszam, int talalatok);


/**
 *  Email-cim szerint kereso fuggveny.
 *
 *  Bemenetkent a dinamikus tomb cimet tarolo valtozot, az oldalszamot, a modositast jelzo flaget,
 *  a keresett stringet es a talalatok szamat kapja meg.
 *
 *  Visszateresi erteke nincs.
 */
void e_keres(Tomb bemenet, int n, bool modositas, char *email, int talalatok);
