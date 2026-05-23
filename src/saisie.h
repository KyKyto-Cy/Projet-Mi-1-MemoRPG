/*
 * saisie.h — Interface des fonctions de saisie sécurisée
 *
 * Toutes les lectures clavier du jeu passent par ce module
 * pour garantir la robustesse contre les saisies invalides.
 */

#ifndef SAISIE_H
#define SAISIE_H

#include "direction.h"

/* Lit une chaîne non vide (max taille-1 caractères). */
char *lire_chaine(char *chaine, int taille);

/* Lit un entier dans [min, max], recommence si invalide. */
int lire_entier(int min, int max);

/* Attend un appui sur Entrée avant de continuer. */
void attendre_entree(void);

/* Lit une direction valide parmi celles disponibles (lettre ou numéro). */
Direction lire_direction(int disponibles[4]);

#endif
