#include "segitseg.h"
#include "jatek.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


int segitseg(Kerdesek* kerdessor,int melyik){


    int nehezseg;
    char kerdes[300];
    char valasza[150];
    char valaszb[150];
    char valaszc[150];
    char valaszd[150];
    char helyes;
    //char kategoria[150];
    Kerdesek* mozgo_segitseg = kerdessor;
    int i = nehezseg_ell(mozgo_segitseg);
    int j = 0;

    nehezseg = mozgo_segitseg->soradat[i];
    i += 2;
    while(mozgo_segitseg->soradat[i] != '\t'){
        kerdes[j]= mozgo_segitseg->soradat[i];
        i += 1;
        j += 1;
    }
    j =0;
    i += 1;

    while(mozgo_segitseg->soradat[i] != '\t'){
        valasza[j]= mozgo_segitseg->soradat[i];
        i += 1;
        j += 1;
    }
    j =0;
    i += 1;

    while(mozgo_segitseg->soradat[i] != '\t'){
        valaszb[j]= mozgo_segitseg->soradat[i];
        i += 1;
        j += 1;
    }
    j =0;
    i += 1;

    while(mozgo_segitseg->soradat[i] != '\t'){
        valaszc[j]= mozgo_segitseg->soradat[i];
        i += 1;
        j += 1;
    }
    j =0;
    i += 1;

    while(mozgo_segitseg->soradat[i] != '\t'){
        valaszd[j]= mozgo_segitseg->soradat[i];
        i += 1;
        j += 1;
    }
    j =0;
    i += 1;
    helyes= mozgo_segitseg->soradat[i];

    srand(time(NULL));

    char helytelen[3];
    char jelek[5] = {'A','B','C','D'};
    int l = 0;
    for(int k = 0; k != 4; k++){
        if(jelek[k] != helyes){
            helytelen[l] = jelek[k];
            l+=1;
        }
    }
    int kivalaszt = rand()%3;

    if(melyik == 1){ //felezes
        printf("A megmaradt lehetosegek:\n");
        printf("%c\t", helyes);
        printf("%c\nA válaszod", helytelen[kivalaszt]);
    }
    if(melyik == 2){ //kozonseg szavazata
        int esely = rand()%101;
        if(esely>25){ //75% esély van arra hogy a közönség kitálalja a megfelelõ választ.
            printf("A közönseg szavazata: %c", helyes);
        }
        else{
            printf("A közoönseg szavazata. %c", helytelen[kivalaszt]);
        }
    }

    return 0;
}



