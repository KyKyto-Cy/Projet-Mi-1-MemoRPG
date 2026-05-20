#ifndef BOARD_H
#define BOARD_H

/* Dimensions du plateau et limites */
#define TAILLE_PLATEAU 5                        /* Nombre de cases par côté (plateau 5x5) */
#define NB_JOUEUR_MAX 4                         /* Nombre maximum de joueurs simultanés */
#define NB_CARTES (TAILLE_PLATEAU * TAILLE_PLATEAU) /* Nombre total de cases sur le plateau */

#include "player.h"

/* Type de contenu d'une case du plateau */


/* Représente une case individuelle du plateau */
typedef struct {
    TypeCase type;       /* Type de contenu de la case */
    TypeMonstre monstre; /* Monstre présent (valide si type == MONSTRE) */
    TypeArmeAntique arme;/* Arme présente (valide si type == ARME_ANTIQUE) */
    int revelee;         /* 1 si la case a été révélée, 0 sinon */
} Case;

/* Représente l'état global du plateau de jeu */
typedef struct {
    Case grille[TAILLE_PLATEAU][TAILLE_PLATEAU]; /* Grille 2D des cases */
    Joueur joueurs[NB_JOUEUR_MAX];               /* Tableau des joueurs en jeu */
    int nb_joueurs;                              /* Nombre de joueurs actifs */
} Plateau;

#endif