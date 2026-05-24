/*
 * main.c — Point d'entrée du jeu Memo RPG
 *
 * Gère la boucle principale : menu, lancement des parties,
 * affichage du gagnant et mise à jour des statistiques.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
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

    /* Animation de démarrage */
    effacer_ecran();
    afficher_marge();
    printf(CYAN GRAS "Initialisation de Memo RPG" RESET);
    fflush(stdout);
    for (int i = 0; i < 3; i++) {
        usleep(300000);
        printf(CYAN GRAS "." RESET);
        fflush(stdout);
    }
    usleep(400000);

    do {
        choix = menu_principal();

        if (choix == 2) {
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
                afficher_joueurs(&plateau, -1); /* Pas de joueur actif au départ */
                attendre_entree();

                int gagnant = -1;
                while (gagnant == -1) {
                    for (int i = 0; i < plateau.nb_joueurs; i++) {
                        /* L'affichage initial du sous-tour est géré par tour_joueur */
                        int resultat = tour_joueur(&plateau, &plateau.joueurs[i], i, debut);
                        if (resultat == 1) {
                            gagnant = i;
                            break;
                        }
                    }
                }

                /* Fin de partie : plateau complet + bannière de victoire */
                reveler_tout(&plateau);
                effacer_ecran();
                afficher_plateau(&plateau);
                afficher_joueurs(&plateau, gagnant);

                printf(GRAS VERT "\n");
                afficher_marge();
                printf("  ██╗   ██╗██╗ ██████╗████████╗ ██████╗ ██╗██████╗ ███████╗\n");
                afficher_marge();
                printf("  ██║   ██║██║██╔════╝╚══██╔══╝██╔═══██╗██║██╔══██╗██╔════╝\n");
                afficher_marge();
                printf("  ██║   ██║██║██║        ██║   ██║   ██║██║██████╔╝█████╗  \n");
                afficher_marge();
                printf("  ╚██╗ ██╔╝██║██║        ██║   ██║   ██║██║██╔══██╗██╔══╝  \n");
                afficher_marge();
                printf("   ╚████╔╝ ██║╚██████╗   ██║   ╚██████╔╝██║██║  ██║███████╗\n");
                afficher_marge();
                printf("    ╚═══╝  ╚═╝ ╚═════╝   ╚═╝    ╚═════╝ ╚═╝╚═╝  ╚═╝╚══════╝\n");
                printf(RESET);

                afficher_marge();
                printf(GRAS "\n  Le gagnant est %s (%s)\n" RESET,
                       plateau.joueurs[gagnant].nom,
                       NomAventurier(plateau.joueurs[gagnant].type));

                afficher_marge();
                afficher_duree(debut);

                mettre_a_jour_stats(stats, &nb_stats, &plateau, gagnant);
                sauvegarder_stats(stats, nb_stats);
                printf("\n");
                afficher_marge();
                printf(BLEU "(Statistiques mises a jour)\n" RESET);

                attendre_entree();

                choix_final = menu_final(&plateau);
            } while (choix_final == 1);
        }

    } while (choix != 3);

    return 0;
}
