#include <stdio.h>
#include <string.h>
#include "sauvegarde.h"
#include "affichage.h"

#define FICHIER_SAUVEGARDE "save.txt"


void sauvegarder_stats(StatJoueur stats[], int nb_joueurs){
    FILE *fichier = fopen(FICHIER_SAUVEGARDE, "w");
    if (fichier == NULL){
        printf("Erreur\n");
        return;
    }
    
    fprintf(fichier, "%d\n", nb_joueurs);

    for (int i = 0; i < nb_joueurs; i++ ){
        fprintf(fichier, "%s %d %d\n", stats[i].nom, stats[i].parties_jouees, stats[i].victoires);
    }
    fclose(fichier);
}


void charger_stats(StatJoueur stats[], int *nb_joueurs){  // pointeur car on va le modifier
    FILE *fichier = fopen(FICHIER_SAUVEGARDE, "r");
    if (fichier == NULL){
        *nb_joueurs = 0;
        return;
    }
    fscanf(fichier, "%d\n", nb_joueurs);
    for (int i = 0; i < *nb_joueurs; i++){
        fscanf(fichier, "%49s %d %d\n", stats[i].nom, &stats[i].parties_jouees, &stats[i].victoires);
    }
    fclose(fichier);

}


void afficher_stats(StatJoueur stats[], int nb_joueurs){
    printf(GRAS "=== STATISTIQUES ===\n" RESET);
    if(nb_joueurs == 0){
        printf("Aucun joueur enregistre\n");
        return;
    }

    /* Tri à bulles décroissant par victoires */
    for (int i = 0; i < nb_joueurs - 1; i++) {
        for (int j = 0; j < nb_joueurs - 1 - i; j++) {
            if (stats[j].victoires < stats[j + 1].victoires) {
                StatJoueur tmp = stats[j];
                stats[j]       = stats[j + 1];
                stats[j + 1]   = tmp;
            }
        }
    }

    for (int i = 0; i < nb_joueurs; i++) {
        printf("%-20s  parties : %d  victoires : %d\n",
               stats[i].nom, stats[i].parties_jouees, stats[i].victoires);
    }
}

void mettre_a_jour_stats(StatJoueur stats[], int *nb_stats, Plateau *plateau, int index_gagnant) {
    for (int i = 0; i < plateau->nb_joueurs; i++) {
        Joueur *j = &plateau->joueurs[i];

        int trouve = -1;
        for (int k = 0; k < *nb_stats; k++) {
            if (strcmp(stats[k].nom, j->nom) == 0) {
                trouve = k;
                break;
            }
        }

        if (trouve != -1) {
            stats[trouve].parties_jouees++;
            if (i == index_gagnant)
                stats[trouve].victoires++;
        } else if (*nb_stats < MAX_JOUEURS_SAUVEGARDES) {
            strncpy(stats[*nb_stats].nom, j->nom, 49);
            stats[*nb_stats].nom[49] = '\0';
            stats[*nb_stats].parties_jouees = 1;
            stats[*nb_stats].victoires = (i == index_gagnant) ? 1 : 0;
            (*nb_stats)++;
        }
    }
}