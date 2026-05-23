#include <stdio.h>
#include <string.h>
#include "board.h"
#include "combat.h"
#include "saisie.h"
#include "player.h"
#include "game.h"


int case_accessible(Joueur *joueur, Plateau *plateau, int ligne, int colonne){
    //Vérifier les limites du plateau
    if (ligne < 0 || ligne > 4 || colonne < 0 || colonne > 4){
        return 0;
    }
    //Calculer les différences
    int diff_ligne = ligne - joueur->positionLigne;
    int diff_colonne = colonne - joueur->positionColonne;

    //Vérifier l'adjacence
    if (abs(diff_ligne) > 1 || abs(diff_colonne) > 1){
        return 0;
    }
    if (diff_ligne == 0 && diff_colonne == 0){
        return 0;
    }
    //Vérifier que la case est cachée
    if (plateau->grille[ligne][colonne].revelee == 1){
        return 0;
    }
    return 1;
}


void deplacer_joueur(Plateau *plateau, Joueur *joueur, int ligne, int colonne){
    joueur->positionLigne = ligne;
    joueur->positionColonne = colonne;
    plateau->grille[ligne][colonne].revelee = 1;

}


void tour_joueur(Plateau *plateau, Joueur *joueur){
    // choisir une arme
    choisirNouvelleArme(joueur);

    //  choisir une case
    int ligne, colonne;
    do {
        printf("Choisissez une ligne (1-5) : ");
        ligne = lire_entier(1, 5) - 1; // -1 car le tableau commence à 0
        printf("Choisissez une colonne (1-5) : ");
        colonne = lire_entier(1, 5) - 1;

        if (case_accessible(joueur, plateau, ligne, colonne) == 0){
            printf("Case inaccessible, choisissez une case adjacente et cachee !\n");
        }
    } while (case_accessible(joueur, plateau, ligne, colonne) == 0);

    //se deplacer sur la case
    deplacer_joueur(plateau, joueur, ligne, colonne);

    // afficher le plateau mis à jour
    afficher_plateau(plateau);

    //gérer ce qu'il y a sur la case
    Case c = plateau->grille[ligne][colonne];

    switch (c.type){
        case MONSTRE:
            combattre(joueur, &plateau->grille[ligne][colonne]);
            break;
        case COFFRE:
            printf("Vous avez trouve un coffre au tresor !\n");
            joueur->trouveCoffre = 1;
            break;
        case ARME_ANTIQUE:
            if (c.arme == joueur->armeRecherchee){
                printf("Vous avez trouve votre arme antique !\n");
                joueur->trouveArmeAntique = 1;
            } else {
                printf("Ce n'est pas votre arme antique, continuez !\n");
            }
            break;
        case PORTAIL:
            printf("Vous avez trouve un portail magique !\n");
            // la prochaine case peut etre n'importe où
            break;
        case TOTEM:
            printf("Vous avez trouve un totem de transmutation !\n");
            // fin du tour
            break;
        case VIDE:
            printf("Case vide, continuez !\n");
            break;
    }
}