/*
 * jeu.h — Interface du module de jeu
 *
 * Expose les fonctions qui gèrent le déplacement des joueurs
 * et le déroulement des tours.
 */

#ifndef JEU_H
#define JEU_H

#include <time.h>
#include "plateau.h"
#include "joueur.h"

/* Retourne 1 si (ligne, colonne) est adjacente au joueur et non encore révélée. */
int case_accessible(Joueur *joueur, Plateau *plateau, int ligne, int colonne);

/* Déplace le joueur sur (ligne, colonne) et révèle la case. */
void deplacer_joueur(Plateau *plateau, Joueur *joueur, int ligne, int colonne);

/*
 * Exécute le tour complet d'un joueur.
 * index_joueur : index 0-based dans plateau->joueurs (pour les ré-affichages).
 * debut        : instant de début de la partie (pour le chrono).
 * Retourne 1 si victoire, 0 sinon.
 */
int tour_joueur(Plateau *plateau, Joueur *joueur, int index_joueur, time_t debut);

#endif
