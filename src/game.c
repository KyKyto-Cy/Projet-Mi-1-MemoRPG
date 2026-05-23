#include <stdio.h>
#include <string.h>
#include "board.h"
#include "combat.h"
#include "saisie.h"
#include "player.h"
#include "game.h"


int case_accessible(Joueur *joueur, Plateau *plateau, int ligne, int colonne){
    if (ligne < 0 || ligne > 4 || colonne < 0 || colonne > 4){
        return 0;
    }
    if (plateau->grille[ligne][colonne].revelee == 1){
        return 0;
    }
    return 1;
}

