#include <stdio.h>
#include <time.h>
#include "timer.h"

time_t timer_demarrer(void) {
    return time(NULL);
}

void afficher_duree(time_t debut) {
    time_t maintenant = time(NULL);
    int duree   = (int)difftime(maintenant, debut);
    int minutes  = duree / 60;
    int secondes = duree % 60;
    printf("Duree de la partie : %02d:%02d\n", minutes, secondes);
}
