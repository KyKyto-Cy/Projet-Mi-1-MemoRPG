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
    int continuer = 1;

    while (continuer) {

        // 1. Choix d'arme
        choisirNouvelleArme(joueur);

        // 2. Choix de case
        int ligne, colonne;

        if (joueur->portail_actif == 1) {
            printf("=== TELEPORTATION ! Choisissez une case cachee ===\n");
            do {
                printf("Ligne (1-5) : ");
                ligne = lire_entier(1, 5) - 1;
                printf("Colonne (1-5) : ");
                colonne = lire_entier(1, 5) - 1;
                if (plateau->grille[ligne][colonne].revelee == 1) {
                    printf("Cette case est deja revelee. Choisissez une case cachee.\n");
                }
            } while (plateau->grille[ligne][colonne].revelee == 1);

            joueur->portail_actif = 0;
        } else {
            // Première passe : compter les cases accessibles
            int disponibles[4] = {0, 0, 0, 0};
            int nb_accessibles = 0;
            for (int d = 0; d < 4; d++) {
                int lig = joueur->positionLigne  + dx[d];
                int col = joueur->positionColonne + dy[d];
                if (case_accessible(joueur, plateau, lig, col)) {
                    disponibles[d] = 1;
                    nb_accessibles++;
                }
            }

            if (nb_accessibles == 0) {
                printf("Vous etes bloque dans le labyrinthe ! Fin du tour.\n");
                retourDepart(joueur);
                reset_cartes_cachees(plateau);
                continuer = 0;
                attendre_entree();
                continue;
            }

            // Deuxième passe : afficher la liste
            printf("Cases accessibles :\n");
            int num = 1;
            for (int d = 0; d < 4; d++) {
                if (disponibles[d]) {
                    int lig = joueur->positionLigne  + dx[d];
                    int col = joueur->positionColonne + dy[d];
                    printf("  [%d/%c] %-5s -> (%d, %d)\n", num++, lettres[d], noms[d], lig + 1, col + 1);
                }
            }

            Direction dir = lire_direction(disponibles);
            ligne   = joueur->positionLigne   + dx[dir];
            colonne = joueur->positionColonne + dy[dir];
        }

        // 3. Déplacement + affichage
        deplacer_joueur(plateau, joueur, ligne, colonne);
        afficher_plateau(plateau);

        // 4. Traitement du contenu
        Case c = plateau->grille[ligne][colonne];

        switch (c.type) {
            case MONSTRE:
                if (combat(joueur, c.monstre) == 0) {
                    reset_cartes_cachees(plateau);
                    continuer = 0;
                }
                break;
            case COFFRE:
                printf("Vous avez trouve un coffre au tresor !\n");
                joueur->trouveCoffre = 1;
                break;
            case ARME_ANTIQUE:
                if (c.arme == joueur->armeRecherchee) {
                    printf("Vous avez trouve votre arme antique !\n");
                    joueur->trouveArmeAntique = 1;
                } else {
                    printf("Ce n'est pas votre arme antique, continuez !\n");
                }
                break;
            case PORTAIL:
                printf("Vous avez trouve un portail magique ! Au prochain tour, vous pourrez vous teleporter n'importe ou.\n");
                joueur->portail_actif = 1;
                continuer = 0;
                break;
            case TOTEM: {
                printf("Vous avez trouve un totem de transmutation ! Choisissez une case cachee a echanger avec le totem.\n");
                afficher_plateau(plateau);

                int lig_cible, col_cible;
                do {
                    printf("Ligne (1-5) : ");
                    lig_cible = lire_entier(1, 5) - 1;
                    printf("Colonne (1-5) : ");
                    col_cible = lire_entier(1, 5) - 1;
                    if (plateau->grille[lig_cible][col_cible].revelee == 1) {
                        printf("Cette case est deja revelee. Choisissez une case cachee.\n");
                    } else if (lig_cible == ligne && col_cible == colonne) {
                        printf("C'est la case du totem elle-meme. Choisissez une autre case.\n");
                    }
                } while (plateau->grille[lig_cible][col_cible].revelee == 1
                         || (lig_cible == ligne && col_cible == colonne));

                Case tmp = plateau->grille[ligne][colonne];
                plateau->grille[ligne][colonne] = plateau->grille[lig_cible][col_cible];
                plateau->grille[lig_cible][col_cible] = tmp;

                retourDepart(joueur);
                reset_cartes_cachees(plateau);
                continuer = 0;
                break;
            }
            case VIDE:
                printf("Case vide, continuez !\n");
                break;
        }

        // 5. Test de victoire
        if (joueurGagne(joueur)) {
            printf("%s a gagne !\n", joueur->nom);
            attendre_entree();
            return 1;
        }

        // 6. Pause entre sous-tours
        attendre_entree();
    }

    return 0;
}