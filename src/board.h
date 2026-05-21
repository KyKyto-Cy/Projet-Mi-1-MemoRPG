#ifndef BOARD_H
#define BOARD_H

/* Dimensions du plateau et limites */
#define TAILLE_PLATEAU 5                        /* Nombre de cases par côté (plateau 5x5) */
#define NB_JOUEUR_MAX 4                         /* Nombre maximum de joueurs simultanés */


#include "player.h"
#include "cards.h"

/* Type de contenu d'une case du plateau */



/* Représente l'état global du plateau de jeu */
typedef struct {
    Case grille[TAILLE_PLATEAU][TAILLE_PLATEAU]; /* Grille 2D des cases */
    Joueur joueurs[NB_JOUEUR_MAX];               /* Tableau des joueurs en jeu */
    int nb_joueurs;                              /* Nombre de joueurs actifs */
} Plateau;

#endif