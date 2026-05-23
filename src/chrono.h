#ifndef CHRONO_H
#define CHRONO_H

#include <time.h>

time_t chrono_demarrer(void);       /* Renvoie l'instant courant */
void afficher_duree(time_t debut); /* Affiche la durée écoulée au format MM:SS */

#endif
