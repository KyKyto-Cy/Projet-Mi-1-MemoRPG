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
    printf(GRAS CYAN "\n");
    printf("==================================================== \n");
    printf("|||                                              ||| \n");
    printf("|||                    MEMO RPG                  ||| \n");
    printf("|||                                              ||| \n");
    printf("|||                                              ||| \n");
    printf("|||                                              ||| \n");
    printf("|||                                              ||| \n");
    printf("|||               1. NOUVELLE PARTIE             ||| \n");
    printf("|||                                              ||| \n");
    printf("|||           2. STATISTIQUES                    ||| \n");
    printf("|||                                              ||| \n");
    printf("|||                                              ||| \n");
    printf("|||                                              ||| \n");
    printf("|||  3.QUITTER                                   ||| \n");
    printf("==================================================== \n");
    printf(RESET "\n");
    printf("Votre choix : \n");
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
    printf(GRAS "\n     ======= CHOIX DES JOUEURS =======   \n\n" RESET);

    printf("Nombre de joueurs de 2 a 4 joueurs : ");
    nb = lire_entier(2, 4);

    plateau->nb_joueurs = nb;

    for (int i = 0; i < nb; i++){
        effacer_ecran();
        printf("\n===== Joueur %d =====\n", i + 1);
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
    printf(GRAS "\n === FIN DE PARTIE ===\n\n" RESET);

    printf(" 1. Rejouer avec les memes joueurs\n");
    printf(" 2. Retour au menu principal\n");
    printf(" Votre choix : \n");
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
