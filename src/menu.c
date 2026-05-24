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
 *
 * Boîte interne : 64 caractères visibles.
 */
int menu_principal(void){
    int choix = 0;

    effacer_ecran();

    /* Titre ANSI Shadow centré */
    afficher_marge();
    printf(GRAS BLANC "  ███╗   ███╗███████╗███╗   ███╗ ██████╗     ██████╗ ██████╗  ██████╗ \n" RESET);
    afficher_marge();
    printf(GRAS BLANC "  ████╗ ████║██╔════╝████╗ ████║██╔═══██╗    ██╔══██╗██╔══██╗██╔════╝ \n" RESET);
    afficher_marge();
    printf(GRAS BLANC "  ██╔████╔██║█████╗  ██╔████╔██║██║   ██║    ██████╔╝██████╔╝██║  ███╗\n" RESET);
    afficher_marge();
    printf(GRAS BLANC "  ██║╚██╔╝██║██╔══╝  ██║╚██╔╝██║██║   ██║    ██╔══██╗██╔═══╝ ██║   ██║\n" RESET);
    afficher_marge();
    printf(GRAS BLANC "  ██║ ╚═╝ ██║███████╗██║ ╚═╝ ██║╚██████╔╝    ██║  ██║██║     ╚██████╔╝\n" RESET);
    afficher_marge();
    printf(GRAS BLANC "  ╚═╝     ╚═╝╚══════╝╚═╝     ╚═╝ ╚═════╝     ╚═╝  ╚═╝╚═╝      ╚═════╝ \n" RESET);
    printf("\n");

    /* Menu — boîte 64 caractères internes */
    afficher_marge();
    printf(CYAN "╔════════════════════════════════════════════════════════════════╗\n");
    afficher_marge();
    printf("║                                                                ║\n");
    afficher_marge();
    printf("║                                                                ║\n");
    afficher_marge();
    printf("║                  " GRAS "1." RESET CYAN "   NOUVELLE PARTIE                          ║\n");
    afficher_marge();
    printf("║                                                                ║\n");
    afficher_marge();
    printf("║                  " GRAS "2." RESET CYAN "   STATISTIQUES                             ║\n");
    afficher_marge();
    printf("║                                                                ║\n");
    afficher_marge();
    printf("║                  " GRAS "3." RESET CYAN "   QUITTER                                  ║\n");
    afficher_marge();
    printf("║                                                                ║\n");
    afficher_marge();
    printf("║                                                                ║\n");
    afficher_marge();
    printf("╚════════════════════════════════════════════════════════════════╝\n" RESET);

    printf("\n");
    afficher_marge();
    printf("  Votre choix : ");
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
    afficher_marge();
    printf(GRAS CYAN "╔══════════════════════════════════════╗\n");
    afficher_marge();
    printf("║          CHOIX DES JOUEURS           ║\n");
    afficher_marge();
    printf("╚══════════════════════════════════════╝\n" RESET "\n");

    afficher_marge();
    printf("  Nombre de joueurs (2 a 4) : ");
    nb = lire_entier(2, 4);

    plateau->nb_joueurs = nb;

    for (int i = 0; i < nb; i++){
        effacer_ecran();
        afficher_marge();
        printf(GRAS "┌─ Joueur %d ─────────────────────────┐\n" RESET, i + 1);
        afficher_marge();
        printf(GRAS "└────────────────────────────────────┘\n" RESET "\n");
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
    afficher_marge();
    printf(GRAS VERT "╔══════════════════════════════════════╗\n");
    afficher_marge();
    printf("║            FIN DE PARTIE             ║\n");
    afficher_marge();
    printf("╚══════════════════════════════════════╝\n" RESET "\n");

    afficher_marge();
    printf("  1. Rejouer avec les memes joueurs\n");
    afficher_marge();
    printf("  2. Retour au menu principal\n\n");
    afficher_marge();
    printf("  Votre choix : ");
    choix = lire_entier(1, 2);

    /* Réinitialise les compteurs de progression pour une nouvelle partie */
    if (choix == 1) {
        for (int i = 0; i < plateau->nb_joueurs; i++) {
            plateau->joueurs[i].trouveCoffre      = 0;
            plateau->joueurs[i].trouveArmeAntique = 0;
            plateau->joueurs[i].portail_actif     = 0;
        }
    }

    return choix;
}
