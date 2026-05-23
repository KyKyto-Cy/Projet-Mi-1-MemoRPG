#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "menu.h"
#include "display.h"
#include "saisie.h"
#include "game.h"
#include "timer.h"

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
                time_t debut = timer_demarrer();
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
                reveler_tout(&plateau);
                effacer_ecran();
                afficher_plateau(&plateau);
                afficher_joueurs(&plateau);
                printf(GRAS VERT "\n==============================\n");
                printf("        PARTIE TERMINEE\n");
                printf("==============================\n" RESET);
                printf(GRAS "Le gagnant est %s (%s)\n" RESET,
                       plateau.joueurs[gagnant].nom,
                       NomAventurier(plateau.joueurs[gagnant].type));
                printf(GRAS VERT "==============================\n" RESET);
                afficher_duree(debut);
                attendre_entree();

                choix_final = menu_final(&plateau);
            } while (choix_final == 1);
        }

    } while (choix != 2);

    return 0;
}
