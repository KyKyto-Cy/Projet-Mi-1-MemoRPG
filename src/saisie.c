#include <stdio.h>
#include <string.h>
#include "saisie.h"

char *lire_chaine(char *chaine, int taille){
    do {
        fgets(chaine, taille, stdin);
        chaine[strcspn(chaine, "\n")] = '\0';
        if (chaine[0] == '\0') {
            printf("Erreur, le nom ne peut pas etre vide : \n");
        }
    } while (chaine[0] == '\0');
    return chaine;
}


int lire_entier(int min, int max){
    int choix;
    do {
        if (scanf("%d", &choix) != 1) {
            printf("Erreur, saisissez un nombre : \n");
            choix = min - 1; //force la boucle à recommencer
        } else if (choix < min || choix > max) {
            printf("Erreur, saisissez un entier entre %d et %d : \n", min, max);
        }
        while (getchar() != '\n'); // vide le buffer dans tous les cas
    } while (choix < min || choix > max);
    return choix;
}