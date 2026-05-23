#ifndef SAISIE_H
#define SAISIE_H

#include "direction.h"

char *lire_chaine(char *chaine, int taille);
int lire_entier(int min, int max);
void attendre_entree(void);
Direction lire_direction(int disponibles[4]); /* Lit Z/D/S/Q ou 1-4, valide contre disponibles[] */

#endif