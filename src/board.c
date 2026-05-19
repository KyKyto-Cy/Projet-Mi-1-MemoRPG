
#include "board.h"

/* Mélange le tableau de cartes en place avec l'algorithme Fisher-Yates.
   Chaque carte a une probabilité égale de se retrouver à n'importe quelle position. */
void melanger_fisher_yates(Case cartes[], int nb_cartes) {
    srand((unsigned int)time(NULL));

    for (int i = nb_cartes - 1; i > 0; i--) {
        /* Choisit un indice aléatoire entre 0 et i (inclus) */
        int j = rand() % (i + 1);

        /* Échange cartes[i] et cartes[j] */
        Case tmp = cartes[i];
        cartes[i] = cartes[j];
        cartes[j] = tmp;
    }
}

void initialiser_plateau(Plateau *plateau) {
    /* Tableau temporaire de 25 cartes avant placement sur la grille */
    Case cartes[NB_CARTES] = {0};
    int i;

    /* 4 monstres BASILIC (indices 0-3) */
    for (i = 0; i < 4; i++) {
        cartes[i].type    = MONSTRE;
        cartes[i].monstre = BASILIC;
        cartes[i].revelee = 0;
    }

    /* 4 monstres ZOMBIE (indices 4-7) */
    for (i = 4; i < 8; i++) {
        cartes[i].type    = MONSTRE;
        cartes[i].monstre = ZOMBIE;
        cartes[i].revelee = 0;
    }

    /* 4 monstres TROLL (indices 8-11) */
    for (i = 8; i < 12; i++) {
        cartes[i].type    = MONSTRE;
        cartes[i].monstre = TROLL;
        cartes[i].revelee = 0;
    }

    /* 4 monstres HARPIE (indices 12-15) */
    for (i = 12; i < 16; i++) {
        cartes[i].type    = MONSTRE;
        cartes[i].monstre = HARPIE;
        cartes[i].revelee = 0;
    }

    /* 4 armes antiques (indices 16-19) */
    cartes[16].type  = ARME_ANTIQUE;
    cartes[16].arme  = EPEE_DE_FEU;
    cartes[16].revelee = 0;

    cartes[17].type  = ARME_ANTIQUE;
    cartes[17].arme  = BATON_DES_FAMILIERS;
    cartes[17].revelee = 0;

    cartes[18].type  = ARME_ANTIQUE;
    cartes[18].arme  = GRIMOIRE_INTERDIT;
    cartes[18].revelee = 0;

    cartes[19].type  = ARME_ANTIQUE;
    cartes[19].arme  = DAGUE_DE_SOMMEIL;
    cartes[19].revelee = 0;

    /* 2 coffres (indices 20-21) */
    cartes[20].type  = COFFRE;
    cartes[20].revelee = 0;

    cartes[21].type  = COFFRE;
    cartes[21].revelee = 0;

    /* 1 portail (indice 22) */
    cartes[22].type  = PORTAIL;
    cartes[22].revelee = 0;

    /* 2 totems (indices 23-24) */
    cartes[23].type  = TOTEM;
    cartes[23].revelee = 0;

    cartes[24].type  = TOTEM;
    cartes[24].revelee = 0;

    /* Mélange aléatoire des 25 cartes avec Fisher-Yates */
    melanger_fisher_yates(cartes, NB_CARTES);

    /* Placement des cartes mélangées sur la grille 5x5 du plateau */
    for (int row = 0; row < TAILLE_PLATEAU; row++) {
        for (int col = 0; col < TAILLE_PLATEAU; col++) {
            plateau->grille[row][col] = cartes[row * TAILLE_PLATEAU + col];
        }
    }
}
