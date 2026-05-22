#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "menu.h"
#include "display.h"
#include "saisie.h"

int main(void) {
    int choix;

    srand(time(NULL));

    do {
        choix = menu_principal();

        if (choix == 1) {
            Plateau plateau;
            int choix_final;

            choisir_joueur(&plateau);

            do {
                initialiser_plateau(&plateau);
                positionner_joueurs(&plateau);
                effacer_ecran();
                afficher_plateau(&plateau);
                attendre_entree();

                choix_final = menu_final(&plateau);
            } while (choix_final == 1);
        }

    } while (choix != 2);

    return 0;
}
