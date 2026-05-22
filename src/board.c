
#include "board.h"
#include "cards.h"

/* Mélange le tableau de cartes en place avec l'algorithme Fisher-Yates.
   Chaque carte a une probabilité égale de se retrouver à n'importe quelle position. */



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
                else if (i == 1) { ligne =  2; col =  5; } /* Est   */
                else if (i == 2) { ligne =  5; col =  2; } /* Sud   */
                else              { ligne =  2; col = -1; } /* Ouest */
                break;
        }

        plateau->joueurs[i].ligneDepart    = ligne;
        plateau->joueurs[i].colonneDepart  = col;
        plateau->joueurs[i].positionLigne  = ligne;
        plateau->joueurs[i].positionColonne = col;
    }
}

void initialiser_plateau(Plateau *plateau) {
    Case cartes[NB_CARTES];
    creer_cartes(cartes);

    /* Placement des cartes mélangées sur la grille 5x5 du plateau */
    for (int row = 0; row < TAILLE_PLATEAU; row++) {
        for (int col = 0; col < TAILLE_PLATEAU; col++) {
            plateau->grille[row][col] = cartes[row * TAILLE_PLATEAU + col];
        }
    }
}
