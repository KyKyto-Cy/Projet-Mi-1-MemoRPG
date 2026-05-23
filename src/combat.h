/*
 * combat.h — Interface du module de combat
 *
 * Expose les fonctions de résolution des combats, de retour au départ
 * et de vérification de la condition de victoire.
 */

#ifndef COMBAT_H
#define COMBAT_H

#include "joueur.h"
#include "cartes.h"

/* Retourne le nom lisible du monstre. */
const char* NomMonstre(TypeMonstre monstre);

/* Retourne 1 si l'arme est efficace contre le monstre, 0 sinon. */
int armeBatMonstre(armeActive arme, TypeMonstre monstre);

/* Replace le joueur à sa case de départ (bord du plateau). */
void retourDepart(Joueur *joueur);

/* Lance un combat. Retourne 1 (victoire) ou 0 (mort → retour au départ). */
int combat(Joueur *joueur, TypeMonstre monstre);

/* Retourne 1 si le joueur a trouvé son coffre ET son arme antique. */
int joueurGagne(const Joueur *joueur);

#endif
