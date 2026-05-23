#ifndef TIMER_H
#define TIMER_H

#include <time.h>

time_t timer_demarrer(void);       /* Renvoie l'instant courant */
void afficher_duree(time_t debut); /* Affiche la durée écoulée au format MM:SS */

#endif
