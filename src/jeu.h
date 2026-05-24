/*
 * jeu.h — Interface du module de jeu
 *
 * Expose les fonctions qui gèrent le déplacement des joueurs
 * et le déroulement des tours.
 */

#ifndef JEU_H
#define JEU_H

#include "plateau.h"
#include "joueur.h"

/* Retourne 1 si (ligne, colonne) est adjacente au joueur et non encore révélée. */
int case_accessible(Joueur *joueur, Plateau *plateau, int ligne, int colonne);

/* Déplace le joueur sur (ligne, colonne) et révèle la case. */
void deplacer_joueur(Plateau *plateau, Joueur *joueur, int ligne, int colonne);

/* Exécute le tour complet d'un joueur. Retourne 1 si victoire, 0 sinon. */
int tour_joueur(Plateau *plateau, Joueur *joueur);

#endif
