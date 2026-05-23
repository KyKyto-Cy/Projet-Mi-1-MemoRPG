/*
 * jeu.c — Logique de tour de jeu
 *
 * Gère le déroulement d'un tour : choix de la case, déplacement,
 * traitement des événements (monstre, coffre, portail, totem…)
 * et détection du blocage.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "direction.h"
#include "plateau.h"
#include "combat.h"
#include "affichage.h"
#include "saisie.h"
#include "joueur.h"
#include "jeu.h"

/*
 * Décalages ligne/colonne pour les 4 directions orthogonales.
 * Ordre : Nord, Est, Sud, Ouest — correspond à l'enum Direction.
 * Exemple : dx[NORD] = -1 (monter d'une ligne), dy[NORD] = 0 (même colonne).
 */
static const int    dx[4]      = {-1,  0, +1,  0};
static const int    dy[4]      = { 0, +1,  0, -1};
static const char  *noms[4]    = {"Nord", "Est", "Sud", "Ouest"};
static const char   lettres[4] = {'Z',    'D',   'S',   'Q'   };


/*
 * Retourne 1 si la case (ligne, colonne) est accessible depuis la position
 * actuelle du joueur, 0 sinon.
 * Conditions : dans les limites, adjacente orthogonalement (distance de Manhattan = 1),
 * et non encore révélée.
 */
int case_accessible(Joueur *joueur, Plateau *plateau, int ligne, int colonne){
    /* Vérifier les limites du plateau (0 à 4 inclus) */
    if (ligne < 0 || ligne > 4 || colonne < 0 || colonne > 4){
        return 0;
    }

    int diff_ligne   = ligne   - joueur->positionLigne;
    int diff_colonne = colonne - joueur->positionColonne;

    /* Distance de Manhattan == 1 : adjacence orthogonale stricte (pas de diagonale) */
    if (abs(diff_ligne) + abs(diff_colonne) != 1){
        return 0;
    }

    /* Une case déjà révélée est inaccessible (déjà visitée) */
    if (plateau->grille[ligne][colonne].revelee == 1){
        return 0;
    }
    return 1;
}


/* Déplace le joueur sur (ligne, colonne) et révèle cette case. */
void deplacer_joueur(Plateau *plateau, Joueur *joueur, int ligne, int colonne){
    joueur->positionLigne   = ligne;
    joueur->positionColonne = colonne;
    plateau->grille[ligne][colonne].revelee = 1; /* Retourne la carte face visible */
}


/*
 * Gère un tour complet d'un joueur.
 * Un tour est une boucle de sous-tours : le joueur continue tant qu'il tombe
 * sur des cases "positives" (coffre, bonne arme, vide, monstre vaincu).
 * Le tour s'arrête sur : mort, portail, totem, blocage, ou victoire.
 * Retourne 1 si le joueur a gagné, 0 sinon.
 */
int tour_joueur(Plateau *plateau, Joueur *joueur){
    /* continuer = 1 : le joueur rejoue un sous-tour
       continuer = 0 : fin du tour, on passe au joueur suivant */
    int continuer = 1;

    while (continuer) {

        /* --- 1. Choix d'arme --- */
        choisirNouvelleArme(joueur);

        /* --- 2. Choix de la case à visiter --- */
        int ligne, colonne;

        if (joueur->portail_actif == 1) {
            /* Mode portail : le joueur peut se téléporter n'importe où sur une case cachée.
               Le flag a été activé au tour précédent (case PORTAIL). */
            printf("=== TELEPORTATION ! Choisissez une case cachee ===\n");
            do {
                printf("Ligne (1-5) : ");
                ligne   = lire_entier(1, 5) - 1; /* Converti de 1-5 en index 0-4 */
                printf("Colonne (1-5) : ");
                colonne = lire_entier(1, 5) - 1;
                if (plateau->grille[ligne][colonne].revelee == 1) {
                    printf("Cette case est deja revelee. Choisissez une case cachee.\n");
                }
            } while (plateau->grille[ligne][colonne].revelee == 1);

            joueur->portail_actif = 0; /* Consomme le portail */

        } else {
            /* Mode normal : déplacement orthogonal vers une case adjacente cachée. */

            /* Première passe : remplir disponibles[] et compter les cases accessibles */
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

            /* Cas de blocage : aucune case accessible autour du joueur.
               continue saute le reste de l'itération (déplacement, switch, victoire) ;
               comme continuer vaut 0, le while quitte ensuite. */
            if (nb_accessibles == 0) {
                printf("Vous etes bloque dans le labyrinthe ! Fin du tour.\n");
                retourDepart(joueur);
                reset_cartes_cachees(plateau);
                continuer = 0;
                attendre_entree();
                continue;
            }

            /* Deuxième passe : afficher la liste des cases accessibles numérotées */
            printf("Cases accessibles :\n");
            int num = 1;
            for (int d = 0; d < 4; d++) {
                if (disponibles[d]) {
                    int lig = joueur->positionLigne  + dx[d];
                    int col = joueur->positionColonne + dy[d];
                    /* Affiche [numéro/lettre] Direction -> (ligne, colonne) en base 1 */
                    printf("  [%d/%c] %-5s -> (%d, %d)\n", num++, lettres[d], noms[d], lig + 1, col + 1);
                }
            }

            Direction dir = lire_direction(disponibles);
            ligne   = joueur->positionLigne   + dx[dir];
            colonne = joueur->positionColonne + dy[dir];
        }

        /* --- 3. Déplacement et affichage --- */
        deplacer_joueur(plateau, joueur, ligne, colonne);
        afficher_plateau(plateau);

        /* --- 4. Traitement du contenu de la case révélée --- */
        Case c = plateau->grille[ligne][colonne];

        switch (c.type) {
            case MONSTRE:
                /* combat() retourne 0 si le joueur est mort (arme incompatible) */
                if (combat(joueur, c.monstre) == 0) {
                    reset_cartes_cachees(plateau); /* Toutes les cartes face cachée */
                    continuer = 0;                 /* Fin du tour : mort */
                }
                /* Si victoire au combat, continuer reste à 1 */
                break;

            case COFFRE:
                printf("Vous avez trouve un coffre au tresor !\n");
                joueur->trouveCoffre = 1;
                /* continuer reste à 1 : le joueur continue d'avancer */
                break;

            case ARME_ANTIQUE:
                if (c.arme == joueur->armeRecherchee) {
                    printf("Vous avez trouve votre arme antique !\n");
                    joueur->trouveArmeAntique = 1;
                } else {
                    printf("Ce n'est pas votre arme antique, continuez !\n");
                }
                /* continuer reste à 1 dans les deux cas */
                break;

            case PORTAIL:
                /* Le portail n'agit pas immédiatement : le flag sera utilisé
                   au prochain appel de tour_joueur. */
                printf("Vous avez trouve un portail magique ! Au prochain tour, vous pourrez vous teleporter n'importe ou.\n");
                joueur->portail_actif = 1;
                continuer = 0; /* Fin du tour : le portail se consomme au tour suivant */
                break;

            case TOTEM: {
                /* Le totem échange sa case avec une case cachée choisie par le joueur,
                   puis renvoie tout le monde à sa case de départ. */
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

                /* Échange des deux cases (swap identique au Fisher-Yates de cartes.c) */
                Case tmp = plateau->grille[ligne][colonne];
                plateau->grille[ligne][colonne]          = plateau->grille[lig_cible][col_cible];
                plateau->grille[lig_cible][col_cible]    = tmp;

                retourDepart(joueur);      /* Renvoie le joueur à sa case de départ */
                reset_cartes_cachees(plateau); /* Toutes les cartes face cachée */
                continuer = 0;             /* Fin du tour */
                break;
            }

            case VIDE:
                printf("Case vide, continuez !\n");
                /* continuer reste à 1 : la case vide n'interrompt pas le tour */
                break;
        }

        /* --- 5. Test de victoire (avant la pause, pour ne pas afficher une pause inutile) --- */
        if (joueurGagne(joueur)) {
            printf("%s a gagne !\n", joueur->nom);
            attendre_entree();
            return 1;
        }

        /* --- 6. Pause entre sous-tours (ou avant de rendre la main) --- */
        attendre_entree();
    }

    return 0; /* Fin du tour sans victoire */
}