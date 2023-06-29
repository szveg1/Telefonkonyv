#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "menuk.h"
#include "debugmalloc.h"
#include "econio.h"
#include "fuggvenyek.h"


void fomenu(Tomb bemenet){
    econio_clrscr();
    printf("ITALRECEPT\n"
           "#######################\n\n"

           "[0] Uj receptkonyv letrehozasa\n"
           "[1] Receptkonyv megnyitasa fajlbol\n\n"

           "[9] Kilepes\n");

    char opcio;
    scanf("%c", &opcio);

    if(opcio != '\n')
        getchar();

    switch(opcio){
        case '0':
            uj_tkonyv(bemenet);
            break;
        case '1':
            tkonyv_menu(bemenet);
            break;
        case '9':
            kilepes(bemenet);
            break;
        default:
            fomenu(bemenet);
            break;
    }
}


void uj_tkonyv(Tomb bemenet){
    econio_clrscr();
/*  Lefoglalja az elso nevjegy szamara szukseges memoriateruletet */
    dintomb_foglal(bemenet.dt,1);

    printf("UJ TELEFONKONYV LETREHOZASA\n"
           "###########################\n\n"

           "[0] Elso nevjegy felvetele\n\n"

           "A fomenube valo visszatereshez: ENTER\n");

    char opcio;
    scanf("%c", &opcio);
    if(opcio != '\n')
        getchar();
/*  majd meghivja a kovetkezo alfuggvenyt a valasztasnak megfeleloen */
    switch(opcio){
        case '0':
            nevjegy_felvesz(bemenet);
            break;
        default:
            dintomb_szabadit(bemenet.dt);
            fomenu(bemenet);
            break;
    }
}


void kilepes(Tomb bemenet) {
    econio_clrscr();
    printf("BIZTOSAN KILEP? (I/N)\n");
    char opcio;
    scanf("%c", &opcio);
/*  Igen valasz eseten ellenorzi, hogy tortent-e memoriafoglalas a dinamikus tomb szamara */
    if(opcio == 'I' || opcio == 'i' ){
/*  Ha tortent akkor elobb felszabaditja, */
        if(bemenet.dt->meret != 0){
            dintomb_szabadit(bemenet.dt);
        }
/*  majd 0-as koddal kilep. */
        exit(0);
    }
/*  Egyebkent meghivja a fomenu fuggvenyt */
    else
        fomenu(bemenet);

}


void nevjegy_felvesz(Tomb bemenet){
    econio_clrscr();
/*  Nevjegy indexenek kiszamitasa (mivel uj nevjegy ezert meret-1 ) */
    int idx = bemenet.dt->meret-1;
    printf("UJ NEVJEGY FELVETELE\n"
           "####################\n\n"

           "[0] Nev* megadasa\n"
           "[1] Foglalkozas megadasa\n"
           "[2] Lakcim megadasa\n"
           "[3] Telefonszam* megadasa\n"
           "[4] E-mail cim megadasa\n\n"

           "[8] Mentes\n\n"

           "[9] Vissza\n"
           "(A *-al jelolt adatok megadasa kotelezo)\n");
    char opcio;
    scanf("%c", &opcio);
    if(opcio != '\n')
        getchar();
/*  A fuggveny megfelelo inputra meghivja a kovetkezo alfuggvenyt */
    switch(opcio){
        case '0':
            nev_megad(bemenet, idx);
            break;
        case '1':
            foglalkozas_megad(bemenet, idx);
            break;
        case '2':
            lakcim_megad(bemenet, idx);
            break;
        case '3':
            telefonszam_megad(bemenet, idx);
            break;
        case '4':
            email_megad(bemenet, idx);
            break;
        case '8':
/*      Ha a nev vagy a telefonszam nincs megadva, akkor hibauzenet, es ennek a fuggvenynek az ujrahivasa */
            if( bemenet.dt->adat[idx].nev == NULL || bemenet.dt->adat[idx].telefonszam == NULL){
                printf("KEVES INFORMACIOT ADOTT MEG!\n"

                       "A nevjegy felvetelhez valo visszatereshez valo visszatereshez nyomja le az ENTER-t!\n");
                getchar();
                nevjegy_felvesz(bemenet);
            }
            else{
                tkonyv_menu(bemenet);
            }
            break;
        case '9':
/*  Ha nem az elso felvenni kivant nevjegy volt, akkor a telefonkonyv menut hivja meg */
            if(bemenet.dt->meret == 1){
                dintomb_szabadit(bemenet.dt);
                fomenu(bemenet);
            }
/*  Egyebkent felszabaditja a nevjegynek lefoglalt memoriateruletet es meghivja a fomenu fuggvenyt */
            else{
                if(bemenet.dt->adat[idx].n_megadva)
                    free(bemenet.dt->adat[idx].nev);

                if(bemenet.dt->adat[idx].f_megadva)
                    free(bemenet.dt->adat[idx].foglalkozas);

                if(bemenet.dt->adat[idx].l_megadva)
                    free(bemenet.dt->adat[idx].lakcim);

                if(bemenet.dt->adat[idx].t_megadva)
                    free(bemenet.dt->adat[idx].telefonszam);

                if(bemenet.dt->adat[idx].e_megadva)
                    free(bemenet.dt->adat[idx].email);

                dintomb_atmeretez(bemenet.dt, bemenet.dt->meret - 1);
                tkonyv_menu(bemenet);
            }
            break;
/*  Nem ertelmezett input eseten hibauzenet es ujrahivja a jelenlegi fuggvenyt */
        default:
            printf("ervenytelen opcio");
            nevjegy_felvesz(bemenet);
            break;

    }
}


void tkonyv_menu(Tomb bemenet){
    econio_clrscr();
/*  Ha a bemenetkent kapott dinamikus tomb merete 0 akkor meghivja a fajlt betolto fuggvenyt */
    if(bemenet.dt->meret == 0){
        FILE *ptr = fajl_betolt();
        if(ptr != NULL){
/*  Sikeres megnyitas eseten kiszamolja hany nevjegyet tartalmaz a fajl */
        int db = nevjegyek_szama(ptr);
/*  es lefoglalja a megfelelo meretu memoriateruletet, */
        dintomb_foglal(bemenet.dt,db);
/*  majd betolti a nevjegyeket a fajlbol a tombbe */
        dintomb_feltolt(ptr,bemenet.dt);
/*  vegul bezarja a fajlt. */
        fclose(ptr);
        }
/*  Sikertelen megnyitas eseten hibauzenet, majd vissza a fomenube */
        else{
            printf("Ervenytelen fajlnev!\n"
               "A fomenube valo visszatereshez: ENTER\n");
            getchar();
            fomenu(bemenet);
        }
    }
    econio_clrscr();
    printf("TELEFONKONYV\n"
           "############\n\n"

           "[0] Telefonkonyv modositasa\n"
           "[1] Kereses\n"
           "[2] Nevjegyek listazasa\n"
           "[3] Telefonkonyv mentese\n\n"

           "[9] Vissza a fomenube\n");
        char opcio;
        scanf("%c", &opcio);
        if(opcio != '\n')
            getchar();
/*  A fuggveny megfelelo inputra meghivja a kovetkezo alfuggvenyt. */
        switch(opcio){
            case '0':
                tkonyv_modosit(bemenet);
                break;
            case '1':
                kereses(bemenet, false);
                break;
            case '2':
                nevjegyek_listaz(bemenet,0, false);
                break;
            case '3':
                tkonyv_ment(bemenet);
                break;
            case '9':
                dintomb_szabadit(bemenet.dt);
                bemenet.dt->meret = 0;
                fomenu(bemenet);
                break;
/*  Barmi mas nem ertelmezett inputra ujrahivja a jelenlegi fuggvenyt. */
            default:
                tkonyv_menu(bemenet);
                break;
        }
}


void tkonyv_modosit(Tomb bemenet){
    econio_clrscr();
    printf("TELEFONKONYV MODOSITASA\n"
           "#######################\n\n"

           "[0] Uj nevjegy felvetele\n"
           "[1] Meglevo nevjegy modositasa\n"
           "[2] Nevjegy beolvasasa vCard fajlbol\n\n"

           "[9] Vissza (TELEFONKONYV)\n");
    char opcio;
    scanf("%c", &opcio);
    if(opcio != '\n')
        getchar();
/*  A fuggveny megfelelo inputra meghivja kovetkezo alfuggvenyt. */
    switch(opcio){
        case '0':
            dintomb_atmeretez(bemenet.dt, bemenet.dt->meret + 1);
            nevjegy_felvesz(bemenet);
            break;
        case '1':
            modositas_mod(bemenet);
            break;
        case '2':
            vcard_beolvas(bemenet);
            break;
        case '9':
            tkonyv_menu(bemenet);
/*  Barmi mas nem ertelmezett inputra ujrahivja a jelenlegi fuggvenyt. */
        default:
            tkonyv_modosit(bemenet);
            break;
    }
}


void tkonyv_ment(Tomb bemenet){
/*  Letrehozza a menteni kivant fajlra mutato pointert */
    FILE *fp = fajl_ment();
/*  Ha nem sikerul megnyitni, akkor hibauzenet */
    if(fp == NULL){
        printf("Sikertelen mentes!");
        getchar();
    }
/*  Egyebkent megfelelo formazassal kiirja a nevjegy tombben tarolt adatokat a fajlba */
    else{
        for(int i = 0; i < bemenet.dt->meret; i++){
            fprintf(fp,"%s\t%s\t%s\t%s\t%s\n",bemenet.dt->adat[i].nev, bemenet.dt->adat[i].foglalkozas,
                bemenet.dt->adat[i].lakcim, bemenet.dt->adat[i].telefonszam, bemenet.dt->adat[i].email);
        }
/*  Bezarja a fajlt */
    fclose(fp);
/*  Megerosit a mentes sikeressegerol */
    printf("Sikeres mentes!\n");
    getchar();
    }
/*  vegul meghivja a telefonkonyv menut */
    tkonyv_menu(bemenet);
}


void nevjegyek_listaz(Tomb bemenet, int n, bool modositas){
    econio_clrscr();

    int nevjegy_db = bemenet.dt->meret;
    printf("%d. oldal\n",n+1);

    printf("TAROLT NEVJEGYEK\n"
           "################\n\n");
/* Hetesevel kiirjuk a nevjegyek rovid valtozatat, es szamoljuk mennyit irtunk eddig ki */
    for(int i = n * 7; i < (n + 1) * 7; ++i){ //< i mindig az adott oldalszám 7x-e
        if(i < nevjegy_db){
            printf("[%d] ", (i - n * 7));
            nevjegy_kiir(bemenet,i);
            printf("\n");
        }
    }

    printf("\n[7] Elozo\n"
           "[8] Kovetkezo\n"
           "[9] Vissza\n");

    int opcio;
    scanf("%d",&opcio);
    getchar();

/*  A fuggveny megfelelo inputra meghivja a kovetkezo alfuggvenyt. */
    switch(opcio){
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
            if( opcio + (n * 7) > nevjegy_db - 1 ){
                printf("Nem letezo nevjegy!\n");
                getchar();
                nevjegyek_listaz(bemenet, n, modositas);
            }
            else{
                if(modositas){
                    nevjegy_modosit(bemenet,(n * 7) + opcio);
                }else{
                    nevjegy_kiir_reszletes(bemenet, (n * 7) + opcio );
                }

            }
            break;
/* 7-es opciora az elozo oldalt hivja meg, ha az oldalszam nem nulla. */
        case 7:
            if(n != 0){
                n--;
                nevjegyek_listaz(bemenet, n, modositas);
            }
            else{
                econio_clrscr();
                printf("Nincs tobb nevjegy!\n"
                       "Folytatashoz: ENTER\n");
                getchar();
                nevjegyek_listaz(bemenet, n, modositas);
            }
            break;
/* 8-as opciora a kovetkezo oldalt hivja meg, ha van meg nevjegy ami nem fert ki. */
        case 8:
            if(nevjegy_db - 1< (n + 1) * 7){
                econio_clrscr();
                printf("Nincs tobb nevjegy!\n"
                       "Folytatashoz: ENTER\n");
                getchar();
                nevjegyek_listaz(bemenet, n, modositas);

            }
            else{
                n++;
                nevjegyek_listaz(bemenet, n, modositas);
            }
            break;
/* Ha nincs tobb oldal valamelyik iranyban akkor hibauzenet. */
/* 9-es opciora vissza a telefonkonyv menujebe */
        case 9:
            tkonyv_menu(bemenet);
            break;
        default:
            nevjegyek_listaz(bemenet, n, modositas);
            break;
    }
}


void nevjegy_modosit(Tomb bemenet, int idx){
    econio_clrscr();
    printf("%s\n", bemenet.dt->adat[idx].nev);
/* Megfelelo szamu hashtag kiírása */
    int nev_hossz = strlen(bemenet.dt->adat[idx].nev);
    for(int i = 0; i < nev_hossz ; i++){
        printf("#");
    }
    printf("\n\n[0] Nev modositasa\n"
           "[1] Foglalkozas modositasa\n"
           "[2] Lakcim modositasa\n"
           "[3] Telefonszam modositasa\n"
           "[4] E-mail cim modositasa\n"
           "[5] Nevjegy torlese\n\n"

           "[8] Mentes\n\n"

           "[9] Vissza\n");
    char opcio;
    scanf("%c", &opcio);
    if(opcio != '\n')
        getchar();
/*  A fuggveny megfelelo inputra meghivja a kovetkezo alfuggvenyt. */
    switch(opcio){
        case '0':
            nev_megad(bemenet, idx);
            break;
        case '1':
            foglalkozas_megad(bemenet, idx);
        case '2':
            lakcim_megad(bemenet, idx);
            break;
        case '3':
            telefonszam_megad(bemenet, idx);
            break;
        case '4':
            email_megad(bemenet, idx);
            break;
        case '5':
            nevjegy_torol(bemenet, idx);
            break;
        case '8':
/*      Ha a nev vagy a telefonszam nincs megadva, akkor hibauzenet, es ennek a fuggvenynek az ujrahivasa */
            if( bemenet.dt->adat[idx].nev == NULL || bemenet.dt->adat[idx].telefonszam == NULL){
                printf("KEVES INFORMACIOT ADOTT MEG!\n"

                       "A nevjegy felvetelhez valo visszatereshez valo visszatereshez nyomja le az ENTER-t!\n");
                getchar();
                if(bemenet.dt->adat[idx].n_megadva)
                    nevjegy_modosit(bemenet, idx);
                else
                    nevjegy_felvesz(bemenet);
            }
            else{
                tkonyv_menu(bemenet);
            }
            break;
        case '9':
            if(bemenet.dt->meret!=1)
                tkonyv_menu(bemenet);
            else{
                fomenu(bemenet);
                dintomb_szabadit(bemenet.dt);
            }
            break;
/// Nem értelmezett input esetén hibaüzenet és újra hívja a jelenlegi függvényt
        default:
            printf("ERVENYTELEN OPCIO!\n"
                   "Folytatashoz: ENTER\n");
            getchar();
            nevjegy_modosit(bemenet, idx);
            break;

    }
}


void modositas_mod(Tomb bemenet){
    econio_clrscr();
    printf("NEVJEGY MODOSITASA\n"
           "##################\n\n"

           "[0] Nevjegy keresese\n"
           "[1] Nevjegy manualis kivalasztasa\n\n"

           "[9] Vissza (TELEFONKONYV MODOSITASA)\n");
     char opcio;
    scanf("%c", &opcio);
    if(opcio != '\n')
        getchar();
/// A függvény megfelelő inputra meghívja a következő alfüggvényt.
    switch(opcio){
        case '0':
            kereses(bemenet, true);
            break;
        case '1':
            nevjegyek_listaz(bemenet, 0, true);
            break;
/// Nem értelmezett input esetén újrahívja a jelenlegi függvényt
        default:
            modositas_mod(bemenet);
            break;

    }
}


void kereses(Tomb bemenet, bool modositas){
    econio_clrscr();
    printf("NEVJEGY KERESESE\n"
           "################\n\n"

           "[0] Nev szerint\n"
           "[1] Foglalkozas szerint\n"
           "[2] Lakcim szerint\n"
           "[3] Telefonszam szerint\n"
           "[4] E-mail cim szerint\n\n"

           "[9] Vissza (TELEFONKONYV)\n");
    char opcio;
    scanf("%c", &opcio);

    if(opcio != '\n')
        getchar();

    switch(opcio){
        case '0':
            n_keres(bemenet, 0, modositas, NULL, 0);
            break;
        case '1':
            f_keres(bemenet, 0, modositas, NULL, 0);
            break;
        case '2':
            l_keres(bemenet, 0, modositas, NULL, 0);
            break;
        case '3':
            t_keres(bemenet, 0, modositas, NULL, 0);
            break;
        case '4':
            e_keres(bemenet, 0, modositas, NULL, 0);
            break;
        case '9':
            tkonyv_menu(bemenet);
            break;
        default:
            printf("ERVENYTELEN OPCIO!\n"
                   "Folytatashoz: ENTER\n");
            getchar();
            kereses(bemenet, modositas);
            break;
        }
}


void n_keres(Tomb bemenet, int oldalszam, bool modositas, char *nev, int talalatok){
/*  ha először hívjuk a függvényt */
    if(nev == NULL){
        econio_clrscr();
        printf("NEV SZERINTI KERESES\n"
               "####################\n");
/*      keresett nevet beolvassa */
        nev = tetsz_hossz_str();
        talalatok = 0;

/*      megszamolja hany string tartalmazza a keresett nevet */
        for(int i = 0; i < bemenet.dt->meret; i++){
            if(str_keres(nev, bemenet.dt->adat[i].nev, 0, 0)){
                    talalatok++;
            }
        }
    }
/*  ha van találat */
    if(talalatok != 0){
        econio_clrscr();
        int j = 0;
/*      létrehoz egy egész számokból álló tömböt, ami a találatok indexét tárolja */
        int *talalatok_idx = malloc(sizeof(int) * talalatok);
/*      mégegyszer végigmegy a névjegyek tömbjén, ahol megtalálja a keresett nevet,
        ott beírja az indexelő tömb következő helyére a keresett név névjegy tömbön belüli indexét */
        for(int i = 0; i < bemenet.dt->meret; i++){
            if(str_keres(nev, bemenet.dt->adat[i].nev , 0, 0)){
                talalatok_idx[j] = i;
                j++;
            }
        }

        printf("TALALATOK (%d. oldal)\n", oldalszam + 1);

/*      kiírja a találatokat az indexelő tömb alapján */
        for(int i = oldalszam * 7; i < (oldalszam + 1) * 7; i++){
            if(i < talalatok){
                printf("[%d]", i - oldalszam * 7);
                nevjegy_kiir(bemenet,talalatok_idx[i]);
                printf("\n");
            }
        }

        printf( "\n[7] Elozo\n"
                "[8] Kovetkezo\n"
                "[9] Vissza\n");

        int opcio;
        scanf("%d",&opcio);
        getchar();
/*      felhasználó kiválaszthatja a kívánt névjegyet */
        switch(opcio){
            case 0:
            case 1:
            case 2:
            case 3:
            case 4:
            case 5:
            case 6:
/*              ha olyan indexű névjegyet probál választani, amilyen nem volt kiírva, akkor
                hibaüzenet, majd keresési menü újbóli hívása */
                free(nev);
                if(opcio + (oldalszam * 7) > talalatok - 1 ){
                    free(talalatok_idx);
                    printf("Nem letezo nevjegy!\n"
                           "Uj kereseshez: ENTER\n");
                    getchar();
                    kereses(bemenet, modositas);
                }
/*              egyébként attól függően, hogy honnan lett hívva a függvény kiírja a névjegy
                összes rendelkezsére álló adatát, vagy meghívja a módosító függvényt */
                else{
/*                  index változónak átadjuk a megfelelő értéket az indexelő tömbből */
                    int idx = talalatok_idx[opcio + oldalszam * 7];
/*                  majd felszabadítjuk az indexelő tömböt */
                    free(talalatok_idx);
                    if(modositas)
                        nevjegy_modosit(bemenet, idx);
                    else
                        nevjegy_kiir_reszletes(bemenet,idx);
                }
                break;
            case 7:
/*              elozo oldal logika */
                free(talalatok_idx);
/*              ha az oldalszam nem nulla (tehát biztosan volt előtte adat), */
                if(oldalszam != 0)
/*                  akkor elozo oldal hivasa. */
                    n_keres(bemenet, oldalszam - 1 , modositas, nev, talalatok);
/*              egyebkent hibauzenet, es jelenlegi oldal ujrahivasa */
                else{
                    printf("Nincs tobb nevjegy!\n"
                           "Uj kereseshez: ENTER\n");
                    getchar();
                    n_keres(bemenet, oldalszam, modositas, nev, talalatok);
                }
                break;
            case 8:
/*              kovetkezo oldal logika */
                free(talalatok_idx);
/*              ha kevesebb a kiirt nevjegyek szama, mint ahany talalat van, */
                if((oldalszam + 1) * 7 < talalatok )
/*                  akkor következő oldal hívása. */
                    n_keres(bemenet, oldalszam + 1 , modositas, nev, talalatok);
/*              egyebkent hibauzenet, es jelenlegi oldal ujrahivasa */
                else{
                    printf("Nincs tobb nevjegy!\n"
                           "Folytatashoz: ENTER\n");
                    getchar();
                    n_keres(bemenet, oldalszam, modositas, nev, talalatok);
                }
                break;
            case 9:
                free(nev);
                free(talalatok_idx);
                kereses(bemenet, modositas);
                break;
        }
    }
/*  ha nem volt talalat, akkor a keresett nevnek foglalt memoria felszabaditasa, hibauzenet, majd
    vissza a keresesi menube */
    else{
        free(nev);
        printf("Nincs talalat!\n"
               "Folytatashoz: ENTER");
        getchar();
        kereses(bemenet, modositas);
    }
}


void f_keres(Tomb bemenet, int oldalszam, bool modositas, char *foglalkozas, int talalatok){
/*  ha először hívjuk a függvényt */
    if(foglalkozas == NULL){
        econio_clrscr();
        printf("FOGLALKOZAS SZERINTI KERESES\n"
               "############################\n");
/*      keresett foglalkozas beolvassa */
        foglalkozas = tetsz_hossz_str();
        talalatok = 0;

/*      megszamolja hany string tartalmazza a keresett foglalkozast */
        for(int i = 0; i < bemenet.dt->meret; i++){
            if(str_keres(foglalkozas, bemenet.dt->adat[i].foglalkozas, 0, 0)){
                    talalatok++;
            }
        }
    }
/*  ha van találat */
    if(talalatok != 0){
        econio_clrscr();
        int j = 0;
/*      létrehoz egy egész számokból álló tömböt, ami a találatok indexét tárolja */
        int *talalatok_idx = malloc(sizeof(int) * talalatok);
/*      mégegyszer végigmegy a névjegyek tömbjén, ahol megtalálja a keresett foglalkozast,
        ott beírja az indexelő tömb következő helyére a keresett foglalkozas névjegy tömbön belüli indexét */
        for(int i = 0; i < bemenet.dt->meret; i++){
            if(str_keres(foglalkozas, bemenet.dt->adat[i].foglalkozas , 0, 0)){
                talalatok_idx[j] = i;
                j++;
            }
        }

        printf("TALALATOK (%d. oldal)\n", oldalszam + 1);

/*      kiírja a találatokat az indexelő tömb alapján */
        for(int i = oldalszam * 7; i < (oldalszam + 1) * 7; i++){
            if(i < talalatok){
                printf("[%d]", i - oldalszam * 7);
                nevjegy_kiir(bemenet,talalatok_idx[i]);
                printf("\n");
            }
        }

        printf( "\n[7] Elozo\n"
                "[8] Kovetkezo\n"
                "[9] Vissza\n");

        int opcio;
        scanf("%d",&opcio);
        getchar();
/*      felhasználó kiválaszthatja a kívánt névjegyet */
        switch(opcio){
            case 0:
            case 1:
            case 2:
            case 3:
            case 4:
            case 5:
            case 6:
/*              ha olyan indexű névjegyet probál választani, amilyen nem volt kiírva, akkor
                hibaüzenet, majd keresési menü újbóli hívása */
                free(foglalkozas);
                if(opcio + (oldalszam * 7) > talalatok - 1 ){
                    free(talalatok_idx);
                    printf("Nem letezo nevjegy!\n"
                           "Uj kereseshez: ENTER\n");
                    getchar();
                    kereses(bemenet, modositas);
                }
/*              egyébként attól függően, hogy honnan lett hívva a függvény kiírja a névjegy
                összes rendelkezsére álló adatát, vagy meghívja a módosító függvényt */
                else{
/*                  index változónak átadjuk a megfelelő értéket az indexelő tömbből */
                    int idx = talalatok_idx[opcio + oldalszam * 7];
/*                  majd felszabadítjuk az indexelő tömböt */
                    free(talalatok_idx);
                    if(modositas)
                        nevjegy_modosit(bemenet, idx);
                    else
                        nevjegy_kiir_reszletes(bemenet,idx);
                }
                break;
            case 7:
/*              elozo oldal logika */
                free(talalatok_idx);
/*              ha az oldalszam nem nulla (tehát biztosan volt előtte adat), */
                if(oldalszam != 0)
/*                  akkor elozo oldal hivasa. */
                    f_keres(bemenet, oldalszam - 1 , modositas, foglalkozas, talalatok);
/*              egyebkent hibauzenet, es jelenlegi oldal ujrahivasa */
                else{
                    printf("Nincs tobb nevjegy!\n"
                           "Uj kereseshez: ENTER\n");
                    getchar();
                    f_keres(bemenet, oldalszam, modositas, foglalkozas, talalatok);
                }
                break;
            case 8:
/*              kovetkezo oldal logika */
                free(talalatok_idx);
/*              ha kevesebb a kiirt nevjegyek szama, mint ahany talalat van, */
                if((oldalszam + 1) * 7 < talalatok )
/*                  akkor következő oldal hívása. */
                    f_keres(bemenet, oldalszam + 1 , modositas, foglalkozas, talalatok);
/*              egyebkent hibauzenet, es jelenlegi oldal ujrahivasa */
                else{
                    printf("Nincs tobb nevjegy!\n"
                           "Folytatashoz: ENTER\n");
                    getchar();
                    f_keres(bemenet, oldalszam, modositas, foglalkozas, talalatok);
                }
                break;
            case 9:
                free(foglalkozas);
                free(talalatok_idx);
                kereses(bemenet, modositas);
                break;
        }
    }
/*  ha nem volt talalat, akkor a keresett nevnek foglalt memoria felszabaditasa, hibauzenet, majd
    vissza a keresesi menube */
    else{
        free(foglalkozas);
        printf("Nincs talalat!\n"
               "Folytatashoz: ENTER");
        getchar();
        kereses(bemenet, modositas);
    }
}


void l_keres(Tomb bemenet, int oldalszam, bool modositas, char *lakcim, int talalatok){
/*  ha először hívjuk a függvényt */
    if(lakcim == NULL){
        econio_clrscr();
        printf("LAKCIM SZERINTI KERESES\n"
               "#######################\n");
/*      keresett lakcimet beolvassa */
        lakcim = tetsz_hossz_str();
        talalatok = 0;

/*      megszamolja hany string tartalmazza a keresett lakcimet */
        for(int i = 0; i < bemenet.dt->meret; i++){
            if(str_keres(lakcim, bemenet.dt->adat[i].lakcim, 0, 0)){
                    talalatok++;
            }
        }
    }
/*  ha van találat */
    if(talalatok != 0){
        econio_clrscr();
        int j = 0;
/*      létrehoz egy egész számokból álló tömböt, ami a találatok indexét tárolja */
        int *talalatok_idx = malloc(sizeof(int) * talalatok);
/*      mégegyszer végigmegy a névjegyek tömbjén, ahol megtalálja a keresett lakcimet,
        ott beírja az indexelő tömb következő helyére a keresett lakcim névjegy tömbön belüli indexét */
        for(int i = 0; i < bemenet.dt->meret; i++){
            if(str_keres(lakcim, bemenet.dt->adat[i].lakcim , 0, 0)){
                talalatok_idx[j] = i;
                j++;
            }
        }

        printf("TALALATOK (%d. oldal)\n", oldalszam + 1);

/*      kiírja a találatokat az indexelő tömb alapján */
        for(int i = oldalszam * 7; i < (oldalszam + 1) * 7; i++){
            if(i < talalatok){
                printf("[%d]", i - oldalszam * 7);
                nevjegy_kiir(bemenet,talalatok_idx[i]);
                printf("\n");
            }
        }

        printf( "\n[7] Elozo\n"
                "[8] Kovetkezo\n"
                "[9] Vissza\n");

        int opcio;
        scanf("%d",&opcio);
        getchar();
/*      felhasználó kiválaszthatja a kívánt névjegyet */
        switch(opcio){
            case 0:
            case 1:
            case 2:
            case 3:
            case 4:
            case 5:
            case 6:
/*              ha olyan indexű névjegyet probál választani, amilyen nem volt kiírva, akkor
                hibaüzenet, majd keresési menü újbóli hívása */
                free(lakcim);
                if(opcio + (oldalszam * 7) > talalatok - 1 ){
                    free(talalatok_idx);
                    printf("Nem letezo nevjegy!\n"
                           "Uj kereseshez: ENTER\n");
                    getchar();
                    kereses(bemenet, modositas);
                }
/*              egyébként attól függően, hogy honnan lett hívva a függvény kiírja a névjegy
                összes rendelkezsére álló adatát, vagy meghívja a módosító függvényt */
                else{
/*                  index változónak átadjuk a megfelelő értéket az indexelő tömbből */
                    int idx = talalatok_idx[opcio + oldalszam * 7];
/*                  majd felszabadítjuk az indexelő tömböt */
                    free(talalatok_idx);
                    if(modositas)
                        nevjegy_modosit(bemenet, idx);
                    else
                        nevjegy_kiir_reszletes(bemenet,idx);
                }
                break;
            case 7:
/*              elozo oldal logika */
                free(talalatok_idx);
/*              ha az oldalszam nem nulla (tehát biztosan volt előtte adat), */
                if(oldalszam != 0)
/*                  akkor elozo oldal hivasa. */
                    l_keres(bemenet, oldalszam - 1 , modositas, lakcim, talalatok);
/*              egyebkent hibauzenet, es jelenlegi oldal ujrahivasa */
                else{
                    printf("Nincs tobb nevjegy!\n"
                           "Uj kereseshez: ENTER\n");
                    getchar();
                    l_keres(bemenet, oldalszam, modositas, lakcim, talalatok);
                }
                break;
            case 8:
/*              kovetkezo oldal logika */
                free(talalatok_idx);
/*              ha kevesebb a kiirt nevjegyek szama, mint ahany talalat van, */
                if((oldalszam + 1) * 7 < talalatok )
/*                  akkor következő oldal hívása. */
                    l_keres(bemenet, oldalszam + 1 , modositas, lakcim, talalatok);
/*              egyebkent hibauzenet, es jelenlegi oldal ujrahivasa */
                else{
                    printf("Nincs tobb nevjegy!\n"
                           "Folytatashoz: ENTER\n");
                    getchar();
                    l_keres(bemenet, oldalszam, modositas, lakcim, talalatok);
                }
                break;
            case 9:
                free(lakcim);
                free(talalatok_idx);
                kereses(bemenet, modositas);
                break;
        }
    }
/*  ha nem volt talalat, akkor a keresett lakcimnek foglalt memoria felszabaditasa, hibauzenet, majd
    vissza a keresesi menube */
    else{
        free(lakcim);
        printf("Nincs talalat!\n"
               "Folytatashoz: ENTER");
        getchar();
        kereses(bemenet, modositas);
    }
}


void t_keres(Tomb bemenet, int oldalszam, bool modositas, char *telefonszam, int talalatok){
/*  ha először hívjuk a függvényt */
    if(talalatok == 0){
        econio_clrscr();
        printf("TELEFONSZAM SZERINTI KERESES\n"
               "############################\n");
/*      keresett telefonszam beolvassa */
        telefonszam = tetsz_hossz_str();
        talalatok = 0;

/*      megszamolja hany string tartalmazza a keresett telefonszamot */
        for(int i = 0; i < bemenet.dt->meret; i++){
            if(str_keres(telefonszam, bemenet.dt->adat[i].telefonszam, 0, 0)){
                    talalatok++;
            }
        }
    }
/*  ha van találat */
    if(talalatok != 0){
        econio_clrscr();
        int j = 0;
/*      létrehoz egy egész számokból álló tömböt, ami a találatok indexét tárolja */
        int *talalatok_idx = malloc(sizeof(int) * talalatok);
/*      mégegyszer végigmegy a névjegyek tömbjén, ahol megtalálja a keresett telefonszamot,
        ott beírja az indexelő tömb következő helyére a keresett telefonszam névjegy tömbön belüli indexét */
        for(int i = 0; i < bemenet.dt->meret; i++){
            if(str_keres(telefonszam, bemenet.dt->adat[i].telefonszam , 0, 0)){
                talalatok_idx[j] = i;
                j++;
            }
        }

        printf("TALALATOK (%d. oldal)\n", oldalszam + 1);

/*      kiírja a találatokat az indexelő tömb alapján */
        for(int i = oldalszam * 7; i < (oldalszam + 1) * 7; i++){
            if(i < talalatok){
                printf("[%d]", i - oldalszam * 7);
                nevjegy_kiir(bemenet,talalatok_idx[i]);
                printf("\n");
            }
        }

        printf( "\n[7] Elozo\n"
                "[8] Kovetkezo\n"
                "[9] Vissza\n");

        int opcio;
        scanf("%d",&opcio);
        getchar();
/*      felhasználó kiválaszthatja a kívánt névjegyet */
        switch(opcio){
            case 0:
            case 1:
            case 2:
            case 3:
            case 4:
            case 5:
            case 6:
/*              ha olyan indexű névjegyet probál választani, amilyen nem volt kiírva, akkor
                hibaüzenet, majd keresési menü újbóli hívása */
                free(telefonszam);
                if(opcio + (oldalszam * 7) > talalatok - 1 ){
                    free(talalatok_idx);
                    printf("Nem letezo nevjegy!\n"
                           "Uj kereseshez: ENTER\n");
                    getchar();
                    kereses(bemenet, modositas);
                }
/*              egyébként attól függően, hogy honnan lett hívva a függvény kiírja a névjegy
                összes rendelkezsére álló adatát, vagy meghívja a módosító függvényt */
                else{
/*                  index változónak átadjuk a megfelelő értéket az indexelő tömbből */
                    int idx = talalatok_idx[opcio + oldalszam * 7];
/*                  majd felszabadítjuk az indexelő tömböt */
                    free(talalatok_idx);
                    if(modositas)
                        nevjegy_modosit(bemenet, idx);
                    else
                        nevjegy_kiir_reszletes(bemenet,idx);
                }
                break;
            case 7:
/*              elozo oldal logika */
                free(talalatok_idx);
/*              ha az oldalszam nem nulla (tehát biztosan volt előtte adat), */
                if(oldalszam != 0)
/*                  akkor elozo oldal hivasa. */
                    t_keres(bemenet, oldalszam - 1 , modositas, telefonszam, talalatok);
/*              egyebkent hibauzenet, es jelenlegi oldal ujrahivasa */
                else{
                    printf("Nincs tobb nevjegy!\n"
                           "Uj kereseshez: ENTER\n");
                    getchar();
                    t_keres(bemenet, oldalszam, modositas, telefonszam, talalatok);
                }
                break;
            case 8:
/*              kovetkezo oldal logika */
                free(talalatok_idx);
/*              ha kevesebb a kiirt nevjegyek szama, mint ahany talalat van, */
                if((oldalszam + 1) * 7 < talalatok )
/*                  akkor következő oldal hívása. */
                    t_keres(bemenet, oldalszam + 1 , modositas, telefonszam, talalatok);
/*              egyebkent hibauzenet, es jelenlegi oldal ujrahivasa */
                else{
                    printf("Nincs tobb nevjegy!\n"
                           "Folytatashoz: ENTER\n");
                    getchar();
                    t_keres(bemenet, oldalszam, modositas, telefonszam, talalatok);
                }
                break;
            case 9:
                free(telefonszam);
                free(talalatok_idx);
                kereses(bemenet, modositas);
                break;
        }
    }
/*  ha nem volt talalat, akkor a keresett nevnek foglalt memoria felszabaditasa, hibauzenet, majd
    vissza a keresesi menube */
    else{
        free(telefonszam);
        printf("Nincs talalat!\n"
               "Folytatashoz: ENTER");
        getchar();
        kereses(bemenet, modositas);
    }
}


void e_keres(Tomb bemenet, int oldalszam, bool modositas, char *email, int talalatok){
/*  ha először hívjuk a függvényt */
    if(talalatok == 0){
        econio_clrscr();
        printf("E-MAIL CIM SZERINTI KERESES\n"
               "###########################\n");
/*      keresett email beolvassa */
        email = tetsz_hossz_str();
        talalatok = 0;

/*      megszamolja hany string tartalmazza a keresett emailt */
        for(int i = 0; i < bemenet.dt->meret; i++){
            if(str_keres(email, bemenet.dt->adat[i].email, 0, 0)){
                    talalatok++;
            }
        }
    }
/*  ha van találat */
    if(talalatok != 0){
        econio_clrscr();
        int j = 0;
/*      létrehoz egy egész számokból álló tömböt, ami a találatok indexét tárolja */
        int *talalatok_idx = malloc(sizeof(int) * talalatok);
/*      mégegyszer végigmegy a névjegyek tömbjén, ahol megtalálja a keresett emailt,
        ott beírja az indexelő tömb következő helyére a keresett email névjegy tömbön belüli indexét */
        for(int i = 0; i < bemenet.dt->meret; i++){
            if(str_keres(email, bemenet.dt->adat[i].email , 0, 0)){
                talalatok_idx[j] = i;
                j++;
            }
        }

        printf("TALALATOK (%d. oldal)\n", oldalszam + 1);

/*      kiírja a találatokat az indexelő tömb alapján */
        for(int i = oldalszam * 7; i < (oldalszam + 1) * 7; i++){
            if(i < talalatok){
                printf("[%d]", i - oldalszam * 7);
                nevjegy_kiir(bemenet,talalatok_idx[i]);
                printf("\n");
            }
        }

        printf( "\n[7] Elozo\n"
                "[8] Kovetkezo\n"
                "[9] Vissza\n");

        int opcio;
        scanf("%d",&opcio);
        getchar();
/*      felhasználó kiválaszthatja a kívánt névjegyet */
        switch(opcio){
            case 0:
            case 1:
            case 2:
            case 3:
            case 4:
            case 5:
            case 6:
/*              ha olyan indexű névjegyet probál választani, amilyen nem volt kiírva, akkor
                hibaüzenet, majd keresési menü újbóli hívása */
                free(email);
                if(opcio + (oldalszam * 7) > talalatok - 1 ){
                    free(talalatok_idx);
                    printf("Nem letezo nevjegy!\n"
                           "Uj kereseshez: ENTER\n");
                    getchar();
                    kereses(bemenet, modositas);
                }
/*              egyébként attól függően, hogy honnan lett hívva a függvény kiírja a névjegy
                összes rendelkezsére álló adatát, vagy meghívja a módosító függvényt */
                else{
/*                  index változónak átadjuk a megfelelő értéket az indexelő tömbből */
                    int idx = talalatok_idx[opcio + oldalszam * 7];
/*                  majd felszabadítjuk az indexelő tömböt */
                    free(talalatok_idx);
                    if(modositas)
                        nevjegy_modosit(bemenet, idx);
                    else
                        nevjegy_kiir_reszletes(bemenet,idx);
                }
                break;
            case 7:
/*              elozo oldal logika */
                free(talalatok_idx);
/*              ha az oldalszam nem nulla (tehát biztosan volt előtte adat), */
                if(oldalszam != 0)
/*                  akkor elozo oldal hivasa. */
                    e_keres(bemenet, oldalszam - 1 , modositas, email, talalatok);
/*              egyebkent hibauzenet, es jelenlegi oldal ujrahivasa */
                else{
                    printf("Nincs tobb nevjegy!\n"
                           "Uj kereseshez: ENTER\n");
                    getchar();
                    e_keres(bemenet, oldalszam, modositas, email, talalatok);
                }
                break;
            case 8:
/*              kovetkezo oldal logika */
                free(talalatok_idx);
/*              ha kevesebb a kiirt nevjegyek szama, mint ahany talalat van, */
                if((oldalszam + 1) * 7 < talalatok )
/*                  akkor következő oldal hívása. */
                    e_keres(bemenet, oldalszam + 1 , modositas, email, talalatok);
/*              egyebkent hibauzenet, es jelenlegi oldal ujrahivasa */
                else{
                    printf("Nincs tobb nevjegy!\n"
                           "Folytatashoz: ENTER\n");
                    getchar();
                    e_keres(bemenet, oldalszam, modositas, email, talalatok);
                }
                break;
            case 9:
                free(email);
                free(talalatok_idx);
                kereses(bemenet, modositas);
                break;
        }
    }
/*  ha nem volt talalat, akkor a keresett nevnek foglalt memoria felszabaditasa, hibauzenet, majd
    vissza a keresesi menube */
    else{
        free(email);
        printf("Nincs talalat!\n"
               "Folytatashoz: ENTER");
        getchar();
        kereses(bemenet, modositas);
    }
}
