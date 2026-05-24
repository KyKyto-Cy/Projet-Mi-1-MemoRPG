/* cartes.c — Création et mélange du jeu de 25 cartes */

#include "cartes.h"
#include <stdlib.h>

/* Remplit et mélange le tableau de 25 cartes (toutes face cachée). */
void creer_cartes(Case cartes[]){
    int i;

    for (i = 0; i < 4; i++) {
        cartes[i].type    = MONSTRE;
        cartes[i].monstre = BASILIC;
        cartes[i].revelee = 0;
    }

    for (i = 4; i < 8; i++) {
        cartes[i].type    = MONSTRE;
        cartes[i].monstre = ZOMBIE;
        cartes[i].revelee = 0;
    }

    for (i = 8; i < 12; i++) {
        cartes[i].type    = MONSTRE;
        cartes[i].monstre = TROLL;
        cartes[i].revelee = 0;
    }

    for (i = 12; i < 16; i++) {
        cartes[i].type    = MONSTRE;
        cartes[i].monstre = HARPIE;
        cartes[i].revelee = 0;
    }

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

    cartes[20].type  = COFFRE;
    cartes[20].revelee = 0;

    cartes[21].type  = COFFRE;
    cartes[21].revelee = 0;

    cartes[22].type  = PORTAIL;
    cartes[22].revelee = 0;

    cartes[23].type  = TOTEM;
    cartes[23].revelee = 0;

    cartes[24].type  = TOTEM;
    cartes[24].revelee = 0;

    melanger_fisher_yates(cartes);
}

/* Mélange les cartes en place (Fisher-Yates). Requiert srand() préalable. */
void melanger_fisher_yates(Case cartes[]) {
    for (int i = NB_CARTES - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        Case tmp = cartes[i];
        cartes[i] = cartes[j];
        cartes[j] = tmp;
    }
}
