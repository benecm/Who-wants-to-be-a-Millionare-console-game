#include "dicsoseg.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "jatek.h"


int dicsosegiras(char *nev, int nyeremeny){
    char nevek[10][50];
    int buff;



    FILE* dicso;
    dicso = fopen("dicsolista.txt", "r");
    if(dicso == NULL){
        dicso = fopen("dicsolista.txt","w");
        fprintf(dicso, "1\t%s\n",nev);
        return 0;

    }
    else{
        for(int i = 0; i!= 10; i++){
            fscanf(dicso,"%d", &buff);
            fgetc(dicso);
            fscanf(dicso,"%[^\n]", &nevek[i]);
            fgetc(dicso);

        }
    }
    char kieso[50];
    strcpy(kieso,nevek[10]);

    for(int i = 10; i != 0; --i){
        strcpy(nevek[i],nevek[i-1]);
    }
    strcpy(nevek[0],nev);


    dicso = fopen("dicsolista.txt", "w");
    int helyezett = 1;
    for(int i = 0; i != 10; ++i){
        fprintf(dicso,"%d\t", helyezett+i);
        fprintf(dicso,"%s\n", nevek[i]);
    }
    fclose(dicso);
    return 0;
}

int dkiir(){
    FILE* dicsoseglista;
    dicsoseglista = fopen("dicsolista.txt", "r");
    if(dicsoseglista == NULL)
        perror("Nincs meg dicsoseglista.");
    else{
        printf("Sorszam\tNev\n");
        char sor[100];
        for(int i= 0; i!=10; ++i){
            fgets(sor,100,dicsoseglista);
            printf("%s", sor);
        }
    }
    fclose(dicsoseglista);
    return 0;
}
