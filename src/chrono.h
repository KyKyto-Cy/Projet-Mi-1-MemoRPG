/*
 * chrono.h — Mesure du temps de jeu
 *
 * Interface simple : chrono_demarrer() capture l'instant de départ,
 * afficher_duree() calcule et affiche l'écart au format MM:SS.
 */

#ifndef CHRONO_H
#define CHRONO_H

#include <time.h>

time_t chrono_demarrer(void);       /* Retourne l'instant courant (point de départ) */
void   afficher_duree(time_t debut); /* Affiche "Durée : MM:SS" depuis debut */

#endif
