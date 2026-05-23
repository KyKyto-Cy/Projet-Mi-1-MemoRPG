#ifndef PLATEAU_H
#define PLATEAU_H

/* Dimensions du plateau et limites */
#define TAILLE_PLATEAU 5                        /* Nombre de cases par côté (plateau 5x5) */
#define NB_JOUEUR_MAX 4                         /* Nombre maximum de joueurs simultanés */


#include "joueur.h"
#include "cartes.h"

/* Représente l'état global du plateau de jeu */
typedef struct {
    Case grille[TAILLE_PLATEAU][TAILLE_PLATEAU]; /* Grille 2D des cases */
    Joueur joueurs[NB_JOUEUR_MAX];               /* Tableau des joueurs en jeu */
    int nb_joueurs;                              /* Nombre de joueurs actifs */
} Plateau;

void initialiser_plateau(Plateau *plateau);     /* Mélange et place les cartes sur la grille */
const char* NomCote(int ligneDepart, int colonneDepart); /* Retourne "Nord"/"Est"/"Sud"/"Ouest" selon la position de départ */
void positionner_joueurs(Plateau *plateau);     /* Positionne chaque joueur sur un côté du plateau */
void reset_cartes_cachees(Plateau *plateau);    /* Remet toutes les cases face cachée */
void reveler_tout(Plateau *plateau);            /* Met toutes les cases face visible */

#endif
