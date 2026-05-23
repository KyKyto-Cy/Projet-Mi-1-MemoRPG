#include <stdio.h>
#include <string.h>
#include "board.h"
#include "combat.h"
#include "saisie.h"
#include "player.h"
#include "game.h"


int case_accessible(Joueur *joueur, Plateau *plateau, int ligne, int colonne){
    //Vérifier les limites du plateau
    if (ligne < 0 || ligne > 4 || colonne < 0 || colonne > 4){
        return 0;
    }
    //Calculer les différences
    int diff_ligne = ligne - joueur->positionLigne;
    int diff_colonne = colonne - joueur->positionColonne;

    //Vérifier l'adjacence
    if (abs(diff_ligne) > 1 || abs(diff_colonne) > 1){
        return 0;
    }
    if (diff_ligne == 0 && diff_colonne == 0){
        return 0;
    }
    //Vérifier que la case est cachée
    if (plateau->grille[ligne][colonne].revelee == 1){
        return 0;
    }
    return 1;
}

