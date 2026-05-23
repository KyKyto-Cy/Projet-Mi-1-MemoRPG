/*
 * saisie.c — Fonctions de saisie sécurisée au clavier
 *
 * Toutes les saisies utilisateur passent par ce module.
 * Il garantit que les valeurs retournées sont dans les bornes attendues
 * et que le tampon stdin est toujours vidé après la lecture.
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "saisie.h"

/*
 * Lit une chaîne non vide depuis stdin (max `taille - 1` caractères).
 * Retire le saut de ligne final et redemande si la saisie est vide.
 */
char *lire_chaine(char *chaine, int taille){
    do {
        fgets(chaine, taille, stdin);
        chaine[strcspn(chaine, "\n")] = '\0'; /* Supprime le \n de fgets */
        if (chaine[0] == '\0') {
            printf("Erreur, le nom ne peut pas etre vide : \n");
        }
    } while (chaine[0] == '\0');
    return chaine;
}

/* Attend que l'utilisateur appuie sur Entrée avant de continuer. */
void attendre_entree(void){
    printf("\nAppuyez sur Entree pour continuer...");
    fflush(stdout);
    getchar();
}

/*
 * Lit une direction parmi celles marquées comme disponibles dans disponibles[].
 * Accepte soit le chiffre (1 à nb_disponibles), soit la lettre (Z/D/S/Q).
 * Redemande en boucle jusqu'à une saisie valide.
 */
Direction lire_direction(int disponibles[4]) {
    static const char lettres[4] = {'Z', 'D', 'S', 'Q'};

    /* Construit la liste ordonnée des directions disponibles pour la numérotation */
    Direction liste[4];
    int nb = 0;
    for (int i = 0; i < 4; i++)
        if (disponibles[i])
            liste[nb++] = (Direction)i;

    char saisie[10];
    while (1) {
        printf("Votre choix : ");
        lire_chaine(saisie, sizeof(saisie));
        char c = toupper((unsigned char)saisie[0]); /* Normalise en majuscule */

        /* Saisie par numéro (1 à nb) */
        if (c >= '1' && c <= '0' + nb)
            return liste[c - '1'];

        /* Saisie par lettre (Z/D/S/Q) */
        for (int i = 0; i < 4; i++)
            if (c == lettres[i] && disponibles[i])
                return (Direction)i;

        printf("Direction invalide ou inaccessible, recommencez.\n");
    }
}

/*
 * Lit un entier dans l'intervalle [min, max] depuis stdin.
 * En cas de saisie non numérique ou hors bornes, affiche un message
 * et recommence. Vide toujours le tampon stdin après la lecture.
 */
int lire_entier(int min, int max){
    int choix = 0;
    do {
        if (scanf("%d", &choix) != 1) {
            printf("Erreur, saisissez un nombre : \n");
            choix = min - 1; /* Force la boucle à recommencer */
        } else if (choix < min || choix > max) {
            printf("Erreur, saisissez un entier entre %d et %d : \n", min, max);
        }
        while (getchar() != '\n'); /* Vide le tampon dans tous les cas */
    } while (choix < min || choix > max);
    return choix;
}
