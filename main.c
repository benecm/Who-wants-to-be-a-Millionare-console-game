#include <stdio.h>
#include <stdlib.h>
#include "jatek.h"
#include "dicsoseg.h"
#include <stdbool.h>
#include <stdio.h>



int main(){
#ifdef _WIN32
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
#endif
    printf("Üdvözöllek a Legyen Ön Is Milliomos Játékban!\n\n");
    printf("A menüben való navigáláshoz ird be a kívánt utasítást és nyomd meg az entert!\n");
    char menu_valasz;
    printf("1. Játék indítása\n");
    printf("2. Dicsõséglista\n");
    printf("3. Kilépés.\n");
    scanf("%c", &menu_valasz);
    m:
        switch(menu_valasz){
            case '1': if(jatek()==0);break;
            case '2': dkiir();break;
            case '3': exit(0);break;
            default: printf("Érvénytelen válasz!");
    }
    return 0;
}
