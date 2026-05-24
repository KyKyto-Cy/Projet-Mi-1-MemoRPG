/*
 * menu.c — Menus de navigation du jeu
 *
 * Gère le menu principal (nouvelle partie / statistiques / quitter),
 * la saisie des joueurs en début de partie,
 * et le menu de fin (rejouer ou retour au menu).
 */

#include <stdio.h>
#include "affichage.h"
#include "menu.h"
#include "saisie.h"

/*
 * Affiche le menu principal et retourne le choix du joueur :
 *   1 = Nouvelle partie
 *   2 = Statistiques
 *   3 = Quitter
 */
int menu_principal(void){
    int choix = 0;

    effacer_ecran();

    /* Titre ANSI Shadow */
    printf(GRAS CYAN);
    printf("  ███╗   ███╗███████╗███╗   ███╗ ██████╗     ██████╗ ██████╗  ██████╗ \n");
    printf("  ████╗ ████║██╔════╝████╗ ████║██╔═══██╗    ██╔══██╗██╔══██╗██╔════╝ \n");
    printf("  ██╔████╔██║█████╗  ██╔████╔██║██║   ██║    ██████╔╝██████╔╝██║  ███╗\n");
    printf("  ██║╚██╔╝██║██╔══╝  ██║╚██╔╝██║██║   ██║    ██╔══██╗██╔═══╝ ██║   ██║\n");
    printf("  ██║ ╚═╝ ██║███████╗██║ ╚═╝ ██║╚██████╔╝    ██║  ██║██║     ╚██████╔╝\n");
    printf("  ╚═╝     ╚═╝╚══════╝╚═╝     ╚═╝ ╚═════╝     ╚═╝  ╚═╝╚═╝      ╚═════╝ \n");
    printf(RESET "\n");

    /* Menu avec bordures Unicode */
    printf(CYAN "  ╔══════════════════════════════════════╗\n");
    printf("  ║                                      ║\n");
    printf("  ║    " GRAS "1." RESET CYAN "  Nouvelle partie              ║\n");
    printf("  ║                                      ║\n");
    printf("  ║    " GRAS "2." RESET CYAN "  Statistiques                 ║\n");
    printf("  ║                                      ║\n");
    printf("  ║    " GRAS "3." RESET CYAN "  Quitter                      ║\n");
    printf("  ║                                      ║\n");
    printf("  ╚══════════════════════════════════════╝\n" RESET);

    printf("\nVotre choix : ");
    choix = lire_entier(1, 3);

    return choix;
}

/*
 * Demande le nombre de joueurs et crée chaque joueur interactivement.
 * Les joueurs sont stockés directement dans plateau->joueurs[].
 */
void choisir_joueur(Plateau *plateau){
    int nb = 0;

    effacer_ecran();
    printf(GRAS CYAN "\n  ╔══════════════════════════════════╗\n");
    printf("  ║       CHOIX DES JOUEURS          ║\n");
    printf("  ╚══════════════════════════════════╝\n" RESET "\n");

    printf("Nombre de joueurs (2 a 4) : ");
    nb = lire_entier(2, 4);

    plateau->nb_joueurs = nb;

    for (int i = 0; i < nb; i++){
        effacer_ecran();
        printf(GRAS "\n  ┌─ Joueur %d ─────────────────────┐\n" RESET, i + 1);
        printf(GRAS "  └────────────────────────────────┘\n" RESET "\n");
        creerJoueur(&plateau->joueurs[i]);
    }
}

/*
 * Affiche le menu de fin de partie et retourne le choix :
 *   1 = Rejouer avec les mêmes joueurs (remet les flags à zéro)
 *   2 = Retour au menu principal
 */
int menu_final(Plateau *plateau){
    int choix = 0;

    effacer_ecran();
    printf(GRAS VERT "\n  ╔══════════════════════════════════╗\n");
    printf("  ║          FIN DE PARTIE           ║\n");
    printf("  ╚══════════════════════════════════╝\n" RESET "\n");

    printf("  1. Rejouer avec les memes joueurs\n");
    printf("  2. Retour au menu principal\n\n");
    printf("  Votre choix : ");
    choix = lire_entier(1, 2);

    /* Réinitialise les compteurs de progression pour une nouvelle partie */
    if(choix == 1){
        for(int i = 0; i < plateau->nb_joueurs; i++){
            plateau->joueurs[i].trouveCoffre      = 0;
            plateau->joueurs[i].trouveArmeAntique = 0;
            plateau->joueurs[i].portail_actif     = 0;
        }
    }

    return choix;
}
