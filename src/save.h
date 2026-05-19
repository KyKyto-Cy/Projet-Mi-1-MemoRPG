#ifndef SAVE_H
#define SAVE_H
#include "player.h"
// TODO: prototypes des fonctions du module save

typedef struct {
    char nom[50];
    int parties_jouees;
    int victoires;
} StatJoueur;


void sauvegarder_stats(StatJoueur stats[], int nb_joueurs);
void charger_stats(StatJoueur stats[], int *nb_joueurs);
void afficher_stats(StatJoueur stats[], int nb_joueurs);



#endif