#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "direction.h"
#include "board.h"
#include "combat.h"
#include "display.h"
#include "saisie.h"
#include "player.h"
#include "game.h"

static const int    dx[4]      = {-1,  0, +1,  0};
static const int    dy[4]      = { 0, +1,  0, -1};
static const char  *noms[4]    = {"Nord", "Est", "Sud", "Ouest"};
static const char   lettres[4] = {'Z',    'D',   'S',   'Q'   };


int case_accessible(Joueur *joueur, Plateau *plateau, int ligne, int colonne){
    //Vérifier les limites du plateau
    if (ligne < 0 || ligne > 4 || colonne < 0 || colonne > 4){
        return 0;
    }
    //Calculer les différences
    int diff_ligne = ligne - joueur->positionLigne;
    int diff_colonne = colonne - joueur->positionColonne;

    //Vérifier l'adjacence orthogonale (haut/bas/gauche/droite uniquement)
    if (abs(diff_ligne) + abs(diff_colonne) != 1){
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


int tour_joueur(Plateau *plateau, Joueur *joueur){
    // choisir une arme
    choisirNouvelleArme(joueur);

    // lister les directions accessibles
    int disponibles[4] = {0, 0, 0, 0};
    int num = 1;
    printf("Cases accessibles :\n");
    for (int d = 0; d < 4; d++) {
        int lig = joueur->positionLigne  + dx[d];
        int col = joueur->positionColonne + dy[d];
        if (case_accessible(joueur, plateau, lig, col)) {
            disponibles[d] = 1;
            printf("  [%d/%c] %-5s -> (%d, %d)\n", num++, lettres[d], noms[d], lig + 1, col + 1);
        }
    }

    Direction dir = lire_direction(disponibles);
    int ligne   = joueur->positionLigne   + dx[dir];
    int colonne = joueur->positionColonne + dy[dir];

    deplacer_joueur(plateau, joueur, ligne, colonne);

    // afficher le plateau mis à jour
    afficher_plateau(plateau);

    //gérer ce qu'il y a sur la case
    Case c = plateau->grille[ligne][colonne];

    switch (c.type){
        case MONSTRE:
            if (combat(joueur, c.monstre) == 0)
                reset_cartes_cachees(plateau);
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

    if (joueurGagne(joueur)) {
        printf("%s a gagne !\n", joueur->nom);
        attendre_entree();
        return 1;
    }
    attendre_entree();
    return 0;
}