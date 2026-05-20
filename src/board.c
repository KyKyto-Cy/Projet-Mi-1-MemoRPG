
#include "board.h"
#include "cards.h"
#include<time.h>
#include<stdlib>
/* Mélange le tableau de cartes en place avec l'algorithme Fisher-Yates.
   Chaque carte a une probabilité égale de se retrouver à n'importe quelle position. */



void initialiser_plateau(Plateau *plateau) {
   

    /* Placement des cartes mélangées sur la grille 5x5 du plateau */
    for (int row = 0; row < TAILLE_PLATEAU; row++) {
        for (int col = 0; col < TAILLE_PLATEAU; col++) {
            plateau->grille[row][col] = cartes[row * TAILLE_PLATEAU + col];
        }
    }
}
