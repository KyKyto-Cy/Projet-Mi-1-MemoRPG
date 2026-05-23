#ifndef GAME_H
#define GAME_H

#include <stdio.h>
#include <string.h>
#include "board.h"
#include "combat.h"
#include "saisie.h"
#include "player.h"

//Vérifie si une case est accessible (adjacente et cachée)
int case_accessible(Joueur *joueur, Plateau *plateau, int ligne, int colonne); 

//Déplace le joueur sur une case et la révèle
void deplacer_joueur(Plateau *plateau, Joueur *joueur, int ligne, int colonne);
// Gère un tour complet d'un joueur — retourne 1 si ce joueur a gagné, 0 sinon
int tour_joueur(Plateau *plateau, Joueur *joueur);


#endif