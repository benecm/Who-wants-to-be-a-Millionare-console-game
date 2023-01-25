#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "jatek.h"
#include "segitseg.h"
#include "dicsoseg.h"
#include <string.h>
#include <ctype.h>
#define SORHOSSZ 1000
#include <windows.h>

void lista_free(Kerdesek* leleje){
    Kerdesek* k = leleje;
    for(int i = 0; i < 10; i++){
        Kerdesek *kov = k->kov;
        free(k);
        k = kov;
    }
}


void my10random(int *t){
    srand(time(0));
    for(int i = 0; i != 10; ++i)
        t[i]=rand()%5000;
}

void rendezes(int *szam){
    int db = 10;
    for(int i = db-1; i>0;--i){
        for(int j = 0; j<i;++j){
            if(szam[j]>szam[j+1]){
                    int temp = szam[j];
                    szam[j]=szam[j+1];
                    szam[j+1]=temp;
            }
        }
    }
}
void listakiir(Kerdesek *elso){
    Kerdesek* mmozgo;
    for(mmozgo = elso; mmozgo != NULL; mmozgo = mmozgo->kov){
        printf("%s\n", mmozgo->soradat);
    }
}

int nehezseg_ell(Kerdesek* adat){
    int c = 0;
    while(adat->soradat[c] != '\t')
        c+=1;
    return c+1;
}

int jatek()
{
#ifdef _WIN32
    SetConsoleCP(1250);
    SetConsoleOutputCP(1250);
#endif

    //random sorszamok elkeszitese a kerdesek soraihoz
    int sorok[9];
    my10random(sorok);
    rendezes(sorok);
    //Kerdesek tipusu strukturak letrehozasa a fajlbol valo beolvasashoz
    Kerdesek* elso;

    //Terulet foglalas a strukturaknak es valtozok a beolvasashoz
    int db =0;                  //hany kerdes lett eddig beolvasva
    int kerdes_szamlalo = 0;    //hanyadik kerdest mentettuk bele a lancolt listaba
    char* kihagy = (char*)malloc(sizeof(char)*SORHOSSZ);  //elso sornak foglaltam helyet, amit beolvasás után egyből el is kell dobni.
    if(kihagy == NULL)
        printf("Nem sikerult elsosor memoriat foglalni.");
    bool olvasson = true;       // addig olvas ameddig el nem eri az utolso kerdesnek a sorát.

    FILE *fp;
    fp = fopen("loim.txt", "r");
    if(fp == NULL)
        perror("Nem sikerült megnyitni a loim.txt-t. ELlenőrizze, hogy a forrásmappában megtalálható-e.");

    fgets(kihagy, SORHOSSZ, fp);
    free(kihagy);

    elso = (Kerdesek*) malloc(sizeof(Kerdesek));
    if(elso == NULL)
        printf("Nem sikerult kerdeseknek memoriat foglalni.");
    Kerdesek* mozgo = elso;
    while(olvasson)
    {
        if(sorok[kerdes_szamlalo] != db){           //ha olyan sorban vagyunk ami nem kell azt egy ideiglenes foglalt területen eltárolom, majd fel is szabadítom.
            char* buffer = (char*)malloc(sizeof(char)*SORHOSSZ);
            fgets(buffer,SORHOSSZ,fp);
            free(buffer);
        }
        else{
            fgets(mozgo->soradat,SORHOSSZ,fp);
            kerdes_szamlalo += 1;
            if(kerdes_szamlalo<10)
                {
                    mozgo->kov = (Kerdesek*)malloc(sizeof(Kerdesek));
                    if(mozgo->kov == NULL)
                        printf("A beolvassanal nem sikerult memoriat foglalni.");
                    mozgo=mozgo->kov;
                }
        }


        if(db == sorok[9])
            olvasson = false;
        db += 1;
    }

    fclose(fp);
    mozgo = elso;

    Kerdesek* mozgos = elso;
    //Jatekos jatekos;
    char jatekos[50];
    int nyeremeny=0;

    printf("Add meg a neved: ");
    getchar();
    scanf("%[^\n]",&jatekos);
    printf("A neved: %s", jatekos);
    printf("\nA kerdes: ");
    int nyeremenyek[10] = {200000,300000,500000,800000,1500000,3000000,5000000,10000000,2000000,40000000}; //megnyerhető nyeremények
    int nyeremeny_szamolo = 0;          // számolja hányadik nyereménynél tart a játék
    int tabulatorok = 0;
    char valaszok[4] = {'a','b','c','d'};
    int valaszjel = 0;
    int felezo = 0;                     //A felező és a közönség segítsége felhasználását ellenörzi.
    int kozonseg = 0;
    int i = 0;
    char helyes;
    char megadott;
    j:                  // a j ahol a játék halad tovább és kiirja a következő kérdést.
        i = nehezseg_ell(mozgos);
        while(mozgos->soradat[i] != '\t'){
            printf("%c", mozgos->soradat[i]);
            i += 1;
        }
        i += 1;
        printf("\nA valaszlehetosegek: ");
        while(tabulatorok < 4){
            printf("%c. ", valaszok[valaszjel]);
            while(mozgos->soradat[i] != '\t'){
                printf("%c", mozgos->soradat[i]);
                i += 1;
            }
            i+=1;
            printf("\t");
            tabulatorok += 1;
            valaszjel += 1;
        }

        helyes = mozgos->soradat[i];


    i = 0;
    tabulatorok = 0;
    valaszjel = 0;

    printf("\nAdja meg a valaszat: ");
    valasz:scanf(" %c", &megadott);

    megadott = toupper(megadott);
    if(megadott == helyes){
        nyeremeny += nyeremenyek[nyeremeny_szamolo];
        nyeremeny_szamolo += 1;
        printf("Helyes valasz! \nAz eddig nyert osszeg: %d", nyeremeny);
        mozgos = mozgos->kov;
        printf("\n\n");
        if(nyeremeny_szamolo == 9){
            printf("A jatek veget ert, megnyerted a fonyermenyt!\nFelkerultel a dicsoseglistara!\n");
            dicsosegiras(jatekos,nyeremeny);
            lista_free(elso);
            return 0;
        }
        else
            goto j;
    }
    else if(megadott == 'A' || megadott == 'B' || megadott == 'C' || megadott == 'D'){
        printf("Helytelen valaszt adtal meg, a jatek most veget er.\n");
        lista_free(elso);
        return 0;
    }

    switch(megadott){
        case'X':
            printf("Koszonjuk a jatekot! A jatek most bezarul.\n");
            lista_free(elso);
            return 0;

        case'F':
            if(felezo == 0){
                segitseg(mozgos, 1);
                felezo += 1;
                goto valasz;
            }
            else{
                printf("A felezest mar elhasznaltad!");
            }
            goto valasz;
        case'K':
            if(kozonseg == 0){
                segitseg(mozgos,2);
                kozonseg += 1;
                goto valasz;
            }
            else{
                printf("A kozonség segitseget mar elhasznaltad!");
            }

            goto valasz;
        default:
            printf("Ervenytelen valasz.");
            goto valasz;
    }

    return 0;

}
