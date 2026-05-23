#ifndef SAUVEGARDE_H
#define SAUVEGARDE_H
#include "plateau.h"

#define MAX_JOUEURS_SAUVEGARDES 100

typedef struct {
    char nom[50];
    int parties_jouees;
    int victoires;
} StatJoueur;

void sauvegarder_stats(StatJoueur stats[], int nb_joueurs);
void charger_stats(StatJoueur stats[], int *nb_joueurs);
void afficher_stats(StatJoueur stats[], int nb_joueurs);
void mettre_a_jour_stats(StatJoueur stats[], int *nb_stats, Plateau *plateau, int index_gagnant);

#endif