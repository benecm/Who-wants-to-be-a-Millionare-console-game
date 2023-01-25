#ifndef JATEK_H_INCLUDED
#define JATEK_H_INCLUDED
#include <time.h>

typedef struct Kerdesek{
    char soradat[1000];
    struct Kerdesek *kov;
}Kerdesek;

typedef struct Jatekos{
    char nev[50];
    int nyeremeny;
}Jatekos;

void lista_free(Kerdesek *leleje);
void my10random(int *t);
void rendezes(int *szam);
void listakiir(Kerdesek *elso);
int nehezseg_ell(Kerdesek* adat);
int jatek();

#endif // JATEK_H_INCLUDED
