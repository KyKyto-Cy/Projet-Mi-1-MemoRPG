/*
 * main.c — Point d'entrée du jeu Memo RPG
 *
 * Gère la boucle principale : menu, lancement des parties,
 * affichage du gagnant et mise à jour des statistiques.
 */

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

    /* Chargement des statistiques persistantes depuis save.txt.
       Si le fichier n'existe pas, nb_stats reste à 0. */
    StatJoueur stats[MAX_JOUEURS_SAUVEGARDES];
    int nb_stats = 0;
    charger_stats(stats, &nb_stats);

    /* Initialise le générateur de nombres aléatoires avec l'heure courante
       pour que chaque partie ait un plateau différent. */
    srand(time(NULL));

    do {
        choix = menu_principal();

        if (choix == 2) {
            /* Option "Statistiques" : affiche le classement des joueurs */
            effacer_ecran();
            afficher_stats(stats, nb_stats);
            attendre_entree();

        } else if (choix == 1) {
            /* Option "Nouvelle partie" */
            Plateau plateau;
            int choix_final;

            choisir_joueur(&plateau);

            /* Boucle de rejeu : même groupe de joueurs, nouveau plateau */
            do {
                initialiser_plateau(&plateau);
                positionner_joueurs(&plateau);
                time_t debut = chrono_demarrer(); /* Démarre le chrono de la partie */
                effacer_ecran();
                afficher_plateau(&plateau);
                afficher_joueurs(&plateau);
                attendre_entree();

                /* Boucle de jeu : tourne jusqu'à ce qu'un joueur gagne */
                int gagnant = -1;
                while (gagnant == -1) {
                    /* Chaque joueur joue son tour à la suite */
                    for (int i = 0; i < plateau.nb_joueurs; i++) {
                        effacer_ecran();
                        afficher_plateau(&plateau);
                        afficher_joueurs(&plateau);
                        printf("Tour de %s !\n", plateau.joueurs[i].nom);

                        /* tour_joueur retourne 1 si ce joueur a gagné */
                        int resultat = tour_joueur(&plateau, &plateau.joueurs[i]);
                        if (resultat == 1) {
                            gagnant = i;
                            break; /* Arrête la rotation des tours immédiatement */
                        }
                    }
                }

                /* Fin de partie : révéler tout le plateau puis annoncer le gagnant */
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
                afficher_duree(debut); /* Affiche la durée totale de la partie */

                /* Mise à jour et sauvegarde des statistiques après chaque partie */
                mettre_a_jour_stats(stats, &nb_stats, &plateau, gagnant);
                sauvegarder_stats(stats, nb_stats);
                printf(BLEU "\n  (Statistiques mises a jour)\n" RESET);

                attendre_entree();

                choix_final = menu_final(&plateau);
            } while (choix_final == 1);
        }

    } while (choix != 3); /* 3 = Quitter */

    return 0;
}
