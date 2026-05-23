#ifndef GAME_H
#define GAME_H

#include <stdio.h>
#include <string.h>
#include "board.h"
#include "combat.h"


int case_accessible(Plateau *plateau, int ligne, int colonne);
void deplacer_joueur(Plateau *plateau, Joueur *joueur, int ligne, int colonne);
void tour_joueur(Plateau *plateau, Joueur *joueur);


#endif