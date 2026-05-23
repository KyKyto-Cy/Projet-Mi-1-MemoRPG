#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "menu.h"
#include "affichage.h"
#include "saisie.h"
#include "jeu.h"
#include "chrono.h"
#include "sauvegarde.h"

int main(void) {
    int choix;

    StatJoueur stats[MAX_JOUEURS_SAUVEGARDES];
    int nb_stats = 0;
    charger_stats(stats, &nb_stats);

    srand(time(NULL));

    do {
        choix = menu_principal();

        if (choix == 2) {
            effacer_ecran();
            afficher_stats(stats, nb_stats);
            attendre_entree();
        } else if (choix == 1) {
            Plateau plateau;
            int choix_final;

            choisir_joueur(&plateau);

            do {
                initialiser_plateau(&plateau);
                positionner_joueurs(&plateau);
                time_t debut = chrono_demarrer();
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

                mettre_a_jour_stats(stats, &nb_stats, &plateau, gagnant);
                sauvegarder_stats(stats, nb_stats);
                printf(BLEU "\n  (Statistiques mises a jour)\n" RESET);

                attendre_entree();

                choix_final = menu_final(&plateau);
            } while (choix_final == 1);
        }

    } while (choix != 3);

    return 0;
}
