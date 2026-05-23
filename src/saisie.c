#include <stdio.h>
#include <string.h>
#include <ctype.h>
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


void attendre_entree(void){
    printf("\nAppuyez sur Entree pour continuer...");
    fflush(stdout);
    getchar();
}

Direction lire_direction(int disponibles[4]) {
    static const char lettres[4] = {'Z', 'D', 'S', 'Q'};

    Direction liste[4];
    int nb = 0;
    for (int i = 0; i < 4; i++)
        if (disponibles[i])
            liste[nb++] = (Direction)i;

    char saisie[10];
    while (1) {
        printf("Votre choix : ");
        lire_chaine(saisie, sizeof(saisie));
        char c = toupper((unsigned char)saisie[0]);

        if (c >= '1' && c <= '0' + nb)
            return liste[c - '1'];

        for (int i = 0; i < 4; i++)
            if (c == lettres[i] && disponibles[i])
                return (Direction)i;

        printf("Direction invalide ou inaccessible, recommencez.\n");
    }
}

int lire_entier(int min, int max){
    int choix = 0;
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