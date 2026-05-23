/*
 * chrono.c — Mesure de la durée d'une partie
 *
 * Utilise time_t (<time.h>) pour capturer l'instant de début,
 * et difftime() pour calculer le nombre de secondes écoulées.
 */

#include <stdio.h>
#include <time.h>
#include "chrono.h"

/* Retourne l'instant courant (utilisé comme point de départ du chrono). */
time_t chrono_demarrer(void) {
    return time(NULL);
}

/*
 * Calcule et affiche la durée écoulée depuis `debut` au format MM:SS.
 * %02d garantit que les secondes s'affichent sur 2 chiffres (ex: 03:07).
 */
void afficher_duree(time_t debut) {
    time_t maintenant = time(NULL);
    int duree    = (int)difftime(maintenant, debut); /* Durée totale en secondes */
    int minutes  = duree / 60;
    int secondes = duree % 60;
    printf("Duree de la partie : %02d:%02d\n", minutes, secondes);
}
