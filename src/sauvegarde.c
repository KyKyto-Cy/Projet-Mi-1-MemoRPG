/*
 * sauvegarde.c — Persistance des statistiques de jeu
 *
 * Les statistiques (parties jouées, victoires) sont stockées dans save.txt,
 * une ligne par joueur au format : "nom parties_jouees victoires".
 * La première ligne du fichier contient le nombre total de joueurs enregistrés.
 */

#include <stdio.h>
#include <string.h>
#include "sauvegarde.h"
#include "affichage.h"

#define FICHIER_SAUVEGARDE "save.txt"

/* Écrit toutes les statistiques dans save.txt (écrase le contenu existant). */
void sauvegarder_stats(StatJoueur stats[], int nb_joueurs){
    FILE *fichier = fopen(FICHIER_SAUVEGARDE, "w");
    if (fichier == NULL){
        printf("Erreur : impossible d'ouvrir le fichier de sauvegarde.\n");
        return;
    }

    fprintf(fichier, "%d\n", nb_joueurs); /* Nombre de joueurs en première ligne */

    for (int i = 0; i < nb_joueurs; i++){
        fprintf(fichier, "%s %d %d\n",
                stats[i].nom, stats[i].parties_jouees, stats[i].victoires);
    }
    fclose(fichier);
}

/*
 * Charge les statistiques depuis save.txt dans le tableau stats[].
 * Si le fichier n'existe pas (première exécution), *nb_joueurs reste à 0.
 * %49s limite la lecture à 49 caractères pour éviter un dépassement de tampon.
 */
void charger_stats(StatJoueur stats[], int *nb_joueurs){
    FILE *fichier = fopen(FICHIER_SAUVEGARDE, "r");
    if (fichier == NULL){
        *nb_joueurs = 0; /* Pas de fichier : aucune statistique à charger */
        return;
    }
    fscanf(fichier, "%d\n", nb_joueurs);
    for (int i = 0; i < *nb_joueurs; i++){
        fscanf(fichier, "%49s %d %d\n",
               stats[i].nom, &stats[i].parties_jouees, &stats[i].victoires);
    }
    fclose(fichier);
}

/*
 * Affiche les statistiques triées par nombre de victoires décroissant.
 * Le tri à bulles modifie l'ordre du tableau en place — cela n'affecte pas
 * la recherche par nom dans mettre_a_jour_stats qui utilise strcmp.
 */
void afficher_stats(StatJoueur stats[], int nb_joueurs){
    printf(GRAS "=== STATISTIQUES ===\n" RESET);
    if (nb_joueurs == 0){
        printf("Aucun joueur enregistre\n");
        return;
    }

    /* Tri à bulles décroissant par victoires pour un effet "classement" */
    for (int i = 0; i < nb_joueurs - 1; i++) {
        for (int j = 0; j < nb_joueurs - 1 - i; j++) {
            if (stats[j].victoires < stats[j + 1].victoires) {
                StatJoueur tmp  = stats[j];
                stats[j]        = stats[j + 1];
                stats[j + 1]    = tmp;
            }
        }
    }

    for (int i = 0; i < nb_joueurs; i++) {
        printf("%-20s  parties : %d  victoires : %d\n",
               stats[i].nom, stats[i].parties_jouees, stats[i].victoires);
    }
}

/*
 * Met à jour le tableau stats[] après une partie.
 * Pour chaque joueur de la partie :
 *   - Si déjà connu (trouvé par strcmp) → incrémente ses compteurs.
 *   - Sinon → l'ajoute comme nouvelle entrée (si la capacité le permet).
 */
void mettre_a_jour_stats(StatJoueur stats[], int *nb_stats, Plateau *plateau, int index_gagnant) {
    for (int i = 0; i < plateau->nb_joueurs; i++) {
        Joueur *j = &plateau->joueurs[i];

        /* Recherche du joueur dans le tableau existant par son nom */
        int trouve = -1;
        for (int k = 0; k < *nb_stats; k++) {
            if (strcmp(stats[k].nom, j->nom) == 0) {
                trouve = k;
                break;
            }
        }

        if (trouve != -1) {
            /* Joueur connu : mise à jour de ses compteurs */
            stats[trouve].parties_jouees++;
            if (i == index_gagnant)
                stats[trouve].victoires++;
        } else if (*nb_stats < MAX_JOUEURS_SAUVEGARDES) {
            /* Nouveau joueur : création d'une entrée */
            strncpy(stats[*nb_stats].nom, j->nom, 49);
            stats[*nb_stats].nom[49] = '\0'; /* Garantit la terminaison de la chaîne */
            stats[*nb_stats].parties_jouees = 1;
            stats[*nb_stats].victoires = (i == index_gagnant) ? 1 : 0;
            (*nb_stats)++;
        }
    }
}
