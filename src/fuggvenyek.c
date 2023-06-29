#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>



#include "fuggvenyek.h"
#include "debugmalloc.h"
#include "econio.h"
#include "menuk.h"

char *tetsz_hossz_str(){

    int hossz = 0;
/*  lefoglal egy 1 karakter hosszu "tombot" */
    char *str = (char*) malloc(sizeof(char) * 1);
/*  egyetlen elemet lezaro nullanak allitja be */
    str[0] = '\0';
    char kovetkezo;
/*  uj sor karakterig olvassa a karaktereket a keszulo stringebe */
    while(scanf("%c", &kovetkezo) == 1 && kovetkezo != '\n'){
        /*  minden iteracioval megnyujtja a tombot, ugy, hogy +1 karakter elferjen benne */
        char *nyujtott = (char*) malloc(sizeof(char) * (hossz+1+1));
        /*  eddig beolvasott karaktereket minden iteracióval atmasolja */
        for(int i = 0; i < hossz; ++i)
            nyujtott[i] = str[i];
        /*  felszabaditja a tombot ahonnan masolja */
        free(str);
        /*  az uj tomb a megnyujtott lesz */
        str = nyujtott;
        /*  utolso elotti karakter az epp beolvasott, */
        nyujtott[hossz] = kovetkezo;
        /*  az utolso pedig a lezaro nulla */
        nyujtott[hossz+1] = '\0';
        ++hossz;
    }
    /*  visszater a beolvasott stringgel */
    return str;
}


FILE* fajl_betolt(){
/*  Bekeri a megnyitni kivant fajl nevet, amit egy tetszoleges hosszusagu karaktertombbe ir, */
   printf("Betolteni kivant fajl (pelda.txt vagy pelda.vcf formatumban):\n");

    char *fajlnev = tetsz_hossz_str();

/*  majd megnyitja azt.*/
    FILE* fp = fopen(fajlnev,"r");
/*  Sikeres megnyitas eseten bezarja a fajlt es ujra megnyitja azt append+ modban,
    majd visszater a file pointerrel */
    if( fp != NULL){
        fclose(fp);
        fp = fopen(fajlnev,"a+");
        free(fajlnev);
        return fp;
    }
/*  Sikertelen megnyitas eseten NULL pointerrel ter vissza. */
    else{
        free(fajlnev);
        return NULL;
    }
/*  Futas végén mindket esetben felszabaditja a fajlnevnek foglalt
    karaktertombot. */
}


int nevjegyek_szama(FILE *pt){
    int nevjegyek_db = 0;
    char buf[500];
/*  Amig el nem eri a fajl veget (vagyis az fgets nem NULL-al ter vissza), olvassa a sorokat
    es minden beolvasott sornal noveli a nevjegyek szamat (1 sor == 1 nevjegy)*/
    while(fgets(buf,500,pt) != NULL){
        nevjegyek_db++;
    }
/*  Amikor vegiger a szovegen a fajl-pointert visszaallitja a fajl elejere
    (kulonben a tobbi fuggvény a fajl vegetol probalna olvasni az adatokat) */
    fseek(pt, 0, SEEK_SET);
/* Futas vegen visszater a nevjegyek szamaval */
return nevjegyek_db;
}


bool dintomb_foglal(Dintomb *dt, int const meret){
/*  A dinamikus tomb altal tarolt meretet a kivant meretre allitjuk, */
    dt->meret = meret;
/*  es lefoglaljuk a megfelelo meretu memoriateruletet */
    dt->adat = (Adatok*) malloc(meret * sizeof(Adatok));
/*  adatmezoket NULL-ra inicializaljuk */
    for(int i = 0; i < meret; i++){
        dt->adat[i].nev = NULL;
        dt->adat[i].foglalkozas = NULL;
        dt->adat[i].lakcim = NULL;
        dt->adat[i].telefonszam = NULL;
        dt->adat[i].email = NULL;
    }
/*  Visszaterunk igazzal vagy hamissal, annak fuggvenyeben, hogy sikerult-e a foglalas*/
    return dt->adat != NULL;
}


void dintomb_szabadit(Dintomb *dt){
/*  osszes adatot felszabaditjuk */
    for(int i = 0; i < dt->meret; i++){
/*  megfelelo adatmezoket felszabaditjuk, annak fuggvenyeben, hogy meg lettek-e adva
    (a nevnel es a telefonszamnal ezt nem kell ellenorizni, mert kotelezo a megadasuk) */
        free(dt->adat[i].nev);
        if(dt->adat[i].f_megadva)
            free(dt->adat[i].foglalkozas);
        if(dt->adat[i].l_megadva)
            free(dt->adat[i].lakcim);
        free(dt->adat[i].telefonszam);
        if(dt->adat[i].e_megadva)
            free(dt->adat[i].email);
    }
/*  vegul magat a tombot is felszabaditjuk */
    free(dt->adat);
    dt->meret = 0;
}


void dintomb_feltolt(FILE *pt, Dintomb *dt){
    int meret = dt->meret;

    char sor[500+1], *nev, *foglalkozas, *lakcim, *tel_szam, *email;
/*  vegigiteralunk az adatokat tartalmazo TXT-fileon, soronkent beolvasva azt
    a sorokat az strtok fuggvennyel tordeljuk, lefoglaljuk a megfelelo meretu karaktertomboket az adatoknak
    majd atmasoljuk oket a dinamikus tombbe*/
    for(int i = 0; i < meret; i++){

        fgets(sor,500,pt);

        nev = strtok(sor,"\t");
        int n_hossz = strlen(nev) + 1;

        foglalkozas = strtok(NULL,"\t");
        int f_hossz = strlen(foglalkozas) + 1;

        lakcim = strtok(NULL,"\t");
        int l_hossz = strlen(lakcim) + 1;

        tel_szam = strtok(NULL,"\t");
        int t_hossz = strlen(tel_szam) + 1;

        email = strtok(NULL,"\n");
        int e_hossz = strlen(email) + 1;

        dt->adat[i].nev = malloc(sizeof(char) * n_hossz);
        dt->adat[i].foglalkozas = malloc(sizeof(char) * f_hossz);
        dt->adat[i].lakcim = malloc(sizeof(char) * l_hossz);
        dt->adat[i].telefonszam = malloc(sizeof(char) * t_hossz);
        dt->adat[i].email = malloc(sizeof(char) * e_hossz);

        strcpy(dt->adat[i].nev, nev);
        strcpy(dt->adat[i].foglalkozas,foglalkozas);
        strcpy(dt->adat[i].lakcim,lakcim);
        strcpy(dt->adat[i].telefonszam,tel_szam);
        strcpy(dt->adat[i].email,email);
    }
}


bool dintomb_atmeretez(Dintomb *dt, int ujmeret){
/*  Lefoglaljuk az uj memoriateruletet */
    Adatok *ujadat = (Adatok*) malloc(ujmeret * sizeof(Adatok));
/*  Ha nem sikerult a foglalas hamissal terunk vissza */
    if (ujadat == NULL)
        return false;
/*  Az uj adatokat inicializaljuk */
    for(int i = 0; i < ujmeret; i++){
        ujadat[i].nev = NULL;
        ujadat[i].foglalkozas = NULL;
        ujadat[i].lakcim = NULL;
        ujadat[i].telefonszam = NULL;
        ujadat[i].email = NULL;
        ujadat[i].n_megadva = false;
        ujadat[i].f_megadva = false;
        ujadat[i].l_megadva = false;
        ujadat[i].t_megadva = false;
        ujadat[i].e_megadva = false;
    }
/*  megnezzuk az uj vagy a regi meret-e a kisebb */
    int kisebb = ujmeret < dt->meret ? ujmeret : dt->meret;
/*  atmasoljuk az adatokat */
    for(int i = 0; i < kisebb; i++)
        ujadat[i] = dt->adat[i];
/*  regi memoriateruletet felszabaditjuk */
    free(dt->adat);
/*  dinamikus tombbe atmasoljuk az uj adatok memoriateruletet es meretet*/
    dt->adat = ujadat;
    dt->meret = ujmeret;
/*  Visszaterunk igazzal, a sikeres foglalas jelzesekent */
    return true;
}


void nevjegy_kiir(Tomb bemenet, int i){
/* Egy-egy adatot akkor ir ki, ha az adatra mutato pointer nem NULL, vagy a string nem a "(null)" */

    if(bemenet.dt->adat[i].nev != NULL && !null_str(bemenet.dt->adat[i].nev))
        printf("%s", bemenet.dt->adat[i].nev);

    if(bemenet.dt->adat[i].foglalkozas != NULL && !null_str(bemenet.dt->adat[i].foglalkozas))
        printf(", %s", bemenet.dt->adat[i].foglalkozas);

    if(bemenet.dt->adat[i].telefonszam != NULL)
        printf(", %s", bemenet.dt->adat[i].telefonszam);

}


void nevjegy_kiir_reszletes(Tomb bemenet, int i){
    econio_clrscr();
    printf("NEVJEGY ADATAI\n"
           "##############\n\n");

/*  Egy-egy adatot akkor ir ki, ha az adatra mutato pointer nem NULL, vagy a string nem a "(null)" */

    if(bemenet.dt->adat[i].nev != NULL && !null_str(bemenet.dt->adat[i].nev))
        printf("Nev: %s\n", bemenet.dt->adat[i].nev);

    if(bemenet.dt->adat[i].foglalkozas != NULL && !null_str(bemenet.dt->adat[i].foglalkozas))
        printf("Foglalkozas: %s\n", bemenet.dt->adat[i].foglalkozas);

    if(bemenet.dt->adat[i].lakcim != NULL && !null_str(bemenet.dt->adat[i].lakcim))
        printf("Lakcim: %s\n", bemenet.dt->adat[i].lakcim);

    if(bemenet.dt->adat[i].telefonszam != NULL)
        printf("Telefonszam: %s\n", bemenet.dt->adat[i].telefonszam);

    if(bemenet.dt->adat[i].email != NULL && !null_str(bemenet.dt->adat[i].email))
        printf("E-mail cim: %s\n\n", bemenet.dt->adat[i].email);


    printf("\n[8] Exportalas vCard fajlba\n"
           "[9] Vissza (NEVJEGY KERESESE)\n");

    int opcio;
    scanf("%d",&opcio);
    getchar();
/*  Adatok megjelenitese utan a felhasznalo exportalhatja vCard-ba a nevjegyet,
    vagy vissza lephet a telefonkonyv menujebe */
    switch(opcio){
        case 8:
            vcard_ment(bemenet,i);
            break;
        case 9:
            tkonyv_menu(bemenet);
            break;
    }
}


void nevjegy_torol(Tomb bemenet, int idx){
    printf("BIZTOSAN TORLI A NEVJEGYET? (I/N)\n");

    int utolso_idx = bemenet.dt->meret;

    char opcio;
    scanf("%c",&opcio);
    if(opcio != '\n')
        getchar();

    if(opcio == 'i' || opcio == 'I'){

        if(utolso_idx != 1){
/*          torolni kivant nevjegy adatmezoinek memoriateruleteit felszabaditjuk */
            free(bemenet.dt->adat[idx].nev);
            free(bemenet.dt->adat[idx].foglalkozas);
            free(bemenet.dt->adat[idx].lakcim);
            free(bemenet.dt->adat[idx].telefonszam);
            free(bemenet.dt->adat[idx].email);
/*          majd a megmaradt nevjegyeket "visszatoljuk" eggyel */
            for(int i = idx; i < bemenet.dt->meret; i++){
                bemenet.dt->adat[i].nev = bemenet.dt->adat[i+1].nev;
                bemenet.dt->adat[i].foglalkozas = bemenet.dt->adat[i+1].foglalkozas;
                bemenet.dt->adat[i].lakcim = bemenet.dt->adat[i+1].lakcim;
                bemenet.dt->adat[i].telefonszam = bemenet.dt->adat[i+1].telefonszam;
                bemenet.dt->adat[i].email = bemenet.dt->adat[i+1].email;
            }
/*          vegul átméretezzük eggyel kisebbre a dinamikus tömböt */
            dintomb_atmeretez(bemenet.dt, utolso_idx - 1);
        }else{
            fomenu(bemenet);
        }

        printf("SIKERES TORLES!\n"
               "Folytatashoz: ENTER\n");
        getchar();
    }
    tkonyv_menu(bemenet);
}


void nev_megad(Tomb bemenet,int idx){
    econio_clrscr();
/*  ha a nev mar meg lett megadva, akkor van mit felszabaditani */

    if(bemenet.dt->adat[idx].n_megadva)
        free(bemenet.dt->adat[idx].nev);

    printf("NEV MEGADASA\n"
           "############\n\n");
/*  nev beolvasasa */
    char *nev = tetsz_hossz_str();
    bool ervenyes_nev = true;

/*  minden karakterre megnezi betu vagy whitespace karakter-e */
    for(int i = 0; i < strlen(nev) && ervenyes_nev == true; i++){
            ervenyes_nev = (isalpha(nev[i]) || nev[i] == ' ');
    }
/*  0 karakteres, vagy nem csak betuket es whitespacet tartalmazo nev nem engedelyezett.
    nem megfelelo nev eseten hibauzenet, majd ennek a fuggvenynek az ujboli hivasa */
    if(strlen(nev) == 0 || !ervenyes_nev){
        bemenet.dt->adat[idx].n_megadva = false;
        printf("ERVENYTELEN NEV!\n"
               "Folytatashoz: ENTER\n");
        free(nev);
        getchar();
        nev_megad(bemenet, idx);
    }else{
/*  egyebkent a megfelelo helyre beirjuk a nevet es megadottra allitjuk */
        bemenet.dt->adat[idx].n_megadva = true;
        bemenet.dt->adat[idx].nev = nev;
    }

    if(bemenet.dt->adat[idx].n_megadva)
        nevjegy_modosit(bemenet, idx);
    else
        nevjegy_felvesz(bemenet);
}


void foglalkozas_megad(Tomb bemenet, int idx){
    econio_clrscr();

/*  ha a foglalkozas mar meg lett megadva, akkor van mit felszabaditani */
    if(bemenet.dt->adat[idx].f_megadva)
        free(bemenet.dt->adat[idx].foglalkozas);

    printf("FOGLALKOZAS MEGADASA\n"
           "####################\n\n");
/*  foglalkozas beolvasasa */
    char *foglalkozas = tetsz_hossz_str();

/*  0 karakteres foglalkozas nem engedelyezett.
    nem megfelelo foglalkozas eseten hibauzenet, majd ennek a fuggvenynek az ujboli hivasa */
    if(strlen(foglalkozas) == 0){
        econio_clrscr();
        bemenet.dt->adat[idx].f_megadva = false;
        printf("ERVENYTELEN FOGLALKOZAS!\n"
               "Folytatashoz: ENTER\n");
        getchar();
        free(foglalkozas);
        foglalkozas_megad(bemenet, idx);
    }else{
/*  egyebkent a megfelelo helyre beirjuk a foglalkozast es megadottra allitjuk */
        bemenet.dt->adat[idx].f_megadva = true;
        bemenet.dt->adat[idx].foglalkozas = foglalkozas;
    }

    if(bemenet.dt->adat[idx].n_megadva)
        nevjegy_modosit(bemenet, idx);
    else
        nevjegy_felvesz(bemenet);
}


void lakcim_megad(Tomb bemenet, int idx){
    econio_clrscr();

/*  ha a lakcim mar meg lett megadva, akkor van mit felszabaditani */
    if(bemenet.dt->adat[idx].l_megadva)
        free(bemenet.dt->adat[idx].lakcim);

    printf("LAKCIM MEGADASA\n"
           "###############\n\n");
/*  lakcim beolvasasa */
    char *lakcim = tetsz_hossz_str();

/*  0 karakteres lakcim nem engedelyezett.
    nem megfelelo lakcim eseten hibauzenet, majd ennek a fuggvenynek az ujboli hivasa */
    if(strlen(lakcim) == 0){
        econio_clrscr();
        bemenet.dt->adat[idx].l_megadva = false;
        printf("ERVENYTELEN LAKCIM!\n"
               "Folytatashoz: ENTER\n");
        getchar();
        free(lakcim);
        lakcim_megad(bemenet, idx);
    }else{
/*  egyebkent a megfelelo helyre beirjuk a lakcimet es megadottra allitjuk */
        bemenet.dt->adat[idx].l_megadva = true;
        bemenet.dt->adat[idx].lakcim = lakcim;
    }

    if(bemenet.dt->adat[idx].n_megadva)
        nevjegy_modosit(bemenet, idx);
    else
        nevjegy_felvesz(bemenet);
}


void telefonszam_megad(Tomb bemenet, int idx){
    econio_clrscr();

/*  ha a tel.szam mar meg lett megadva, akkor van mit felszabaditani */
    if(bemenet.dt->adat[idx].t_megadva)
        free(bemenet.dt->adat[idx].telefonszam);

    printf("TELEFONSZAM MEGADASA\n"
           "####################\n\n");

/*  tel.szam beolvasasa */
    char *telefonszam = tetsz_hossz_str();
    bool ervenyes_tel = true;

/*  megnezzuk, hogy csak szamokbol all-e */
    for(int i = 0; i < strlen(telefonszam) && ervenyes_tel == true ; i++)
        ervenyes_tel = isdigit(telefonszam[i]);

/*  ha nem, akkor ervenytelen, felszabaditjuk a beolvasott telefonszamot es ujrahivjuk a fuggvenyt */
    if(!ervenyes_tel){
        econio_clrscr();
        bemenet.dt->adat[idx].t_megadva = false;
        printf("ERVENYTELEN TELEFONSZAM!\n"
               "Folytatashoz: ENTER\n");
        getchar();
        free(telefonszam);
        telefonszam_megad(bemenet, idx);
    }else{
/*  egyebkent a megfelelo helyre beirjuk a tel.szamot es megadottra allitjuk */
        bemenet.dt->adat[idx].t_megadva = true;
        bemenet.dt->adat[idx].telefonszam = telefonszam;
    }


    if(bemenet.dt->adat[idx].n_megadva)
        nevjegy_felvesz(bemenet);
    else
        nevjegy_modosit(bemenet, idx);
}


void email_megad(Tomb  bemenet, int idx){
    econio_clrscr();

/*  ha az email mar meg lett megadva, akkor van mit felszabaditani */
    if(bemenet.dt->adat[idx].e_megadva)
        free(bemenet.dt->adat[idx].email);

    printf("EMAIL MEGADASA\n"
           "###############\n\n");

/*  beolvassuk az e-mail cimet */
    char *email = tetsz_hossz_str();
    int kukac_db = 0;
    int pont_db = 0;
/*  megnezzuk van e benne @ es . karakter */
    for(int i = 0; i < strlen(email); i++){
        if(email[i] == '@')
            kukac_db++;
        if(email[i] == '.')
            pont_db++;
    }
/*  ha nincs, akkor ervenytelen, felszabaditjuk a beolvasott e-mail cimet es ujrahivjuk a fuggvenyt */
    if(kukac_db != 1 || pont_db < 1){
        econio_clrscr();
        bemenet.dt->adat[idx].e_megadva = false;
        printf("ERVENYTELEN EMAIL!\n"
               "Folytatashoz: ENTER\n");
        getchar();
        free(email);
        email_megad(bemenet, idx);
    }else{
/*  egyebkent a megfelelo helyre beirjuk az e-mail cimet, es megadottra allitjuk */
        bemenet.dt->adat[idx].e_megadva = true;
        bemenet.dt->adat[idx].email = email;
    }
    if(bemenet.dt->adat[idx].n_megadva)
        nevjegy_modosit(bemenet, idx);
    else
        nevjegy_felvesz(bemenet);
}


bool null_str(char *str){
    if(strcmp(str,"(null)") == 0)
        return true;

    return false;
}


FILE* fajl_ment(){
// Bekeri a fajlnak szant nevet, amit egy tetszoleges hosszusagu tombbe ir,
   printf("Milyen neven legyen elmentve a fajl? (pelda.txt vagy pelda.vcf formatumban):\n");
    char *fajlnev = tetsz_hossz_str();
// majd megnyitja azt write modban.
    FILE* fp = fopen(fajlnev,"w");
// Sikeres megnyitas eseten visszater a file-pointerrel.
    if( fp != NULL){
        free(fajlnev);
        return fp;
    }else{
// Sikertelen megnyitas eseten NULL pointerrel ter vissza.
        free(fajlnev);
        return NULL;
    }
}


bool str_keres(char *keresett, char *hol_keres, int k, int h){
/*  megnezzuk, hogy a keresett szoveg jelenlegi karakter a lezaro nulla-e */
    if (keresett[k] == '\0'){
/*      ha a szovegben ahol keresunk a jelenlegi karakter a lezaro nulla akkor igazzal terunk vissza*/
        return hol_keres[h] == '\0';
/*  egyebkent megnezzuk, hogy a keresett szoveg jelenlegi karakter a csillag-e */
    }else if(keresett[k] == '*'){
/*      amig el nem erjuk a szoveg veget */
        while(hol_keres[h] != '\0'){
/*          noveljuk a keresett szoveg vizsgalt karakterenek indexet */
            h++;
/*          osszehasonlitjuk a karaktereket */
            if (str_keres(keresett, hol_keres, k+1, h))
                return true;
        }
        return str_keres(keresett, hol_keres, k+1, h);
    }else if(keresett[k] != hol_keres[h]){
        return false;
    }else{
        return str_keres(keresett, hol_keres, k+1, h+1);
  }
}


void vcard_ment(Tomb bemenet, int idx){
/*  megnyitjuk a fajlt */
    FILE *fp = fajl_ment();
/*  beirjuk a fajlba az adatokat */
    fprintf(fp, "BEGIN:VCARD\n"
                "VERSION:4.0\n");

    if(bemenet.dt->adat[idx].nev != NULL && !null_str(bemenet.dt->adat[idx].nev))
        fprintf(fp,"FN:%s\n", bemenet.dt->adat[idx].nev);

    if(bemenet.dt->adat[idx].email != NULL && !null_str(bemenet.dt->adat[idx].email))
        fprintf(fp,"EMAIL:%s\n", bemenet.dt->adat[idx].email);

    if(bemenet.dt->adat[idx].foglalkozas != NULL && !null_str(bemenet.dt->adat[idx].foglalkozas))
        fprintf(fp,"ORG:%s\n", bemenet.dt->adat[idx].foglalkozas);

    if(bemenet.dt->adat[idx].telefonszam != NULL)
        fprintf(fp,"TEL:%s\n", bemenet.dt->adat[idx].telefonszam);

    if(bemenet.dt->adat[idx].lakcim != NULL && !null_str(bemenet.dt->adat[idx].lakcim))
        fprintf(fp,"ADR:%s\n", bemenet.dt->adat[idx].lakcim);

    fprintf(fp,"END:VCARD\n");
/*  majd bezarjuk a fajlt es meghivju ka telefonkonyv menut */
    fclose(fp);
    tkonyv_menu(bemenet);
}


void vcard_beolvas(Tomb bemenet){
    econio_clrscr();
    FILE *pt = fajl_betolt();

    if(pt == NULL){
        printf("NEM LETEZO FAJL!\n"
               "Folytatashoz: ENTER\n");
        dintomb_atmeretez(bemenet.dt, bemenet.dt->meret - 1);
        getchar();
        tkonyv_menu(bemenet);
    }

    dintomb_atmeretez(bemenet.dt, bemenet.dt->meret + 1);

    int sorok = 0, idx = bemenet.dt->meret - 1;
    char sor[500+1], *beolvasott, *adat_tipus;


/*  fajl vege karakterig olvassa a fajlt */
    while(fgets(sor,500,pt) != NULL){
        sorok++;
    }
/*  file-pointer visszaallitasa, hogy el tudjuk vegezni a muveleteket */
    fseek(pt, 0, SEEK_SET);
    econio_clrscr();
    printf("A KOVETKEZO ADATOK KERULTEK BEOLVASASRA:\n\n");
    for(int i = 0; i < sorok - 1; i++){
/*      sorok beolvasasa */
        fgets(sor,500,pt);
/*      kettospont elotti string az adat tipusat adja meg */
        adat_tipus = strtok(sor,":");
        beolvasott = strtok(NULL,"\n");
        if(i != 0 && i != 1)
        printf("%s\n",beolvasott);
        int str_hossz = strlen(beolvasott) + 1;
/*      adattipus alapjan kivalasztjuk a megfelelot, az adat letezeset mutato flaget igazra allitjuk,
        lefoglaljuk a memoriateruletet, majd atmasoljuk az adatot a dinamikus tombbe */
        if(strstr(adat_tipus,"FN")){

            bemenet.dt->adat[idx].n_megadva = true;
            bemenet.dt->adat[idx].nev = malloc(sizeof(char) * str_hossz);
            strcpy(bemenet.dt->adat[idx].nev, beolvasott);


        }else if(strstr(adat_tipus,"EMAIL")){

            bemenet.dt->adat[idx].e_megadva = true;
            bemenet.dt->adat[idx].email = malloc(sizeof(char) * str_hossz);
            strcpy(bemenet.dt->adat[idx].email, beolvasott);


        }else if(strstr(adat_tipus,"ORG")){

            bemenet.dt->adat[idx].f_megadva = true;
            bemenet.dt->adat[idx].foglalkozas = malloc(sizeof(char) * str_hossz);
            strcpy(bemenet.dt->adat[idx].foglalkozas, beolvasott);


        }else if(strstr(adat_tipus,"TEL")){

            bemenet.dt->adat[idx].t_megadva = true;
            bemenet.dt->adat[idx].telefonszam = malloc(sizeof(char) * str_hossz);
            strcpy(bemenet.dt->adat[idx].telefonszam, beolvasott);


        }else if(strstr(adat_tipus,"ADR")){

            bemenet.dt->adat[idx].l_megadva = true;
            bemenet.dt->adat[idx].lakcim = malloc(sizeof(char) * str_hossz);
            strcpy(bemenet.dt->adat[idx].lakcim, beolvasott);


        }else{}
    }
    fclose(pt);
    printf("\nKivanja menteni? (I/N)\n");
    char opcio;
    scanf("%c", &opcio);
    getchar();
    if(opcio == 'i' || opcio == 'I')
        printf("Sikeres mentes!\n");
    else{
        free(bemenet.dt->adat[idx].nev);
        free(bemenet.dt->adat[idx].foglalkozas);
        free(bemenet.dt->adat[idx].lakcim);
        free(bemenet.dt->adat[idx].telefonszam);
        free(bemenet.dt->adat[idx].email);
        dintomb_atmeretez(bemenet.dt, bemenet.dt->meret - 1);
    }

    printf("Folytatashoz: ENTER\n");
    getchar();
    tkonyv_menu(bemenet);
}



