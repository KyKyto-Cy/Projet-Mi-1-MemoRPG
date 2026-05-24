/*
 * plateau.c — Gestion du plateau de jeu
 *
 * Initialisation de la grille, positionnement des joueurs sur les bords,
 * et fonctions utilitaires sur l'état des cases (cacher/révéler).
 */

#include "plateau.h"
#include "cartes.h"

/*
 * Retourne le nom du côté ("Nord", "Est", "Sud", "Ouest") à partir de la
 * position de départ d'un joueur.
 * Convention : ligne == -1 → Nord (au-dessus de la grille),
 *              colonne == 5 → Est, ligne == 5 → Sud, sinon → Ouest.
 */
const char* NomCote(int ligneDepart, int colonneDepart) {
    if (ligneDepart   == -1) { return "Nord"; }
    if (colonneDepart ==  5) { return "Est"; }
    if (ligneDepart   ==  5) { return "Sud"; }
    return "Ouest";
}

/*
 * Assigne à chaque joueur une position de départ sur un bord du plateau.
 * Les positions -1 et 5 sont hors de la grille (0-4) : elles symbolisent
 * le couloir d'entrée de chaque côté.
 * Répartition selon le nombre de joueurs :
 *   2 joueurs → Nord / Sud
 *   3 joueurs → Nord / Est / Ouest
 *   4 joueurs → Nord / Sud / Est / Ouest
 */
void positionner_joueurs(Plateau *plateau) {
    int nb = plateau->nb_joueurs;

    for (int i = 0; i < nb; i++) {
        int ligne, col;

        switch (nb) {
            case 2:
                if      (i == 0) { ligne = -1; col =  2; } /* Nord */
                else              { ligne =  5; col =  2; } /* Sud  */
                break;
            case 3:
                if      (i == 0) { ligne = -1; col =  2; } /* Nord  */
                else if (i == 1) { ligne =  2; col =  5; } /* Est   */
                else              { ligne =  2; col = -1; } /* Ouest */
                break;
            default: /* 4 joueurs */
                if      (i == 0) { ligne = -1; col =  2; } /* Nord  */
                else if (i == 1) { ligne =  5; col =  2; } /* Sud   */
                else if (i == 2) { ligne =  2; col =  5; } /* Est   */
                else              { ligne =  2; col = -1; } /* Ouest */
                break;
        }

        /* ligneDepart/colonneDepart servent à retourDepart() plus tard */
        plateau->joueurs[i].ligneDepart     = ligne;
        plateau->joueurs[i].colonneDepart   = col;
        plateau->joueurs[i].positionLigne   = ligne;
        plateau->joueurs[i].positionColonne = col;
    }
}

/* Remet toutes les cases face cachée (revelee = 0).
   Appelé après une mort, un blocage ou un totem. */
void reset_cartes_cachees(Plateau *plateau) {
    for (int i = 0; i < TAILLE_PLATEAU; i++)
        for (int j = 0; j < TAILLE_PLATEAU; j++)
            plateau->grille[i][j].revelee = 0;
}

/* Met toutes les cases face visible (revelee = 1).
   Appelé en fin de partie pour que les joueurs voient le plateau complet. */
void reveler_tout(Plateau *plateau) {
    for (int i = 0; i < TAILLE_PLATEAU; i++)
        for (int j = 0; j < TAILLE_PLATEAU; j++)
            plateau->grille[i][j].revelee = 1;
}

/* Crée et mélange les cartes, puis les place sur la grille 5x5 du plateau. */
void initialiser_plateau(Plateau *plateau) {
    Case cartes[NB_CARTES];
    creer_cartes(cartes); /* Remplit et mélange le tableau de 25 cartes */

    /* Copie linéaire du tableau 1D vers la grille 2D */
    for (int row = 0; row < TAILLE_PLATEAU; row++) {
        for (int col = 0; col < TAILLE_PLATEAU; col++) {
            plateau->grille[row][col] = cartes[row * TAILLE_PLATEAU + col];
        }
    }
}
