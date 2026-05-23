#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "menu.h"
#include "display.h"
#include "saisie.h"
#include "game.h"

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
                afficher_joueurs(&plateau);
                attendre_entree();

                int gagnant = -1;
                while (gagnant == -1) {
                    for (int i = 0; i < plateau.nb_joueurs; i++) {
                        effacer_ecran();
                        afficher_plateau(&plateau);
                        afficher_joueurs(&plateau);
                        printf("Tour de %s !\n", plateau.joueurs[i].nom);

                        int resultat = tour_joueur(&plateau, &plateau.joueurs[i]);
                        if (resultat == 1) {
                            gagnant = i;
                            break;
                        }
                    }
                }
                printf("Le gagnant est %s !\n", plateau.joueurs[gagnant].nom);
                attendre_entree();

                choix_final = menu_final(&plateau);
            } while (choix_final == 1);
        }

    } while (choix != 2);

    return 0;
}
