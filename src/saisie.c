#include <stdio.h>
#include <string.h>
#include "saisie.h"

char *lire_chaine(char *chaine, int taille){
    fgets(chaine, taille, stdin);
    chaine[strcspn(chaine, "\n")] = '\0';
    return chaine;
}


int lire_entier(int min, int max){
    int choix;
    do{
        scanf("%d", &choix);

    }while(choix < min || choix > max);
    return choix;

}