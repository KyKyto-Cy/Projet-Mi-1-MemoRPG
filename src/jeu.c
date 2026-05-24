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
#include <unistd.h>
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
    if (ligne < 0 || ligne > TAILLE_PLATEAU - 1 || colonne < 0 || colonne > TAILLE_PLATEAU - 1){
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
int tour_joueur(Plateau *plateau, Joueur *joueur, int index_joueur, time_t debut){
    int continuer = 1;

    while (continuer) {

        /* --- Affichage propre en début de chaque sous-tour --- */
        effacer_ecran();
        afficher_plateau(plateau);
        afficher_joueurs(plateau, index_joueur);
        afficher_banniere_tour(joueur, index_joueur, debut);
        afficher_objectifs(joueur);

        /* --- 1. Choix d'arme --- */
        choisirNouvelleArme(joueur);

        /* --- 2. Choix de la case à visiter --- */
        int ligne, colonne;

        if (joueur->portail_actif == 1) {
            printf("\n"); afficher_marge(); printf("=== TELEPORTATION ! Choisissez une case cachee ===\n");
            do {
                afficher_marge(); printf("Ligne (1-5) : ");
                ligne   = lire_entier(1, 5) - 1;
                afficher_marge(); printf("Colonne (1-5) : ");
                colonne = lire_entier(1, 5) - 1;
                if (plateau->grille[ligne][colonne].revelee == 1)
                    { afficher_marge(); printf("Cette case est deja revelee. Choisissez une case cachee.\n"); }
            } while (plateau->grille[ligne][colonne].revelee == 1);

            joueur->portail_actif = 0;

        } else {
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
                printf("\n"); afficher_marge(); printf("Vous etes bloque dans le labyrinthe ! Fin du tour.\n");
                retourDepart(joueur);
                reset_cartes_cachees(plateau);
                continuer = 0;
                attendre_entree();
                continue;
            }

            printf("\n"); afficher_marge(); printf("Cases accessibles :\n");
            int num = 1;
            for (int d = 0; d < 4; d++) {
                if (disponibles[d]) {
                    int lig = joueur->positionLigne  + dx[d];
                    int col = joueur->positionColonne + dy[d];
                    afficher_marge(); printf("  [%d/%c] %-5s -> (%d, %d)\n", num++, lettres[d], noms[d], lig + 1, col + 1);
                }
            }

            Direction dir = lire_direction(disponibles);
            ligne   = joueur->positionLigne   + dx[dir];
            colonne = joueur->positionColonne + dy[dir];
        }

        /* --- 3. Déplacement : révèle la case, puis suspense, puis ré-affichage --- */
        deplacer_joueur(plateau, joueur, ligne, colonne);

        printf("\n"); afficher_marge(); printf("Vous revelez la case...\n");
        fflush(stdout);
        usleep(500000);

        effacer_ecran();
        afficher_plateau(plateau);
        afficher_joueurs(plateau, index_joueur);
        afficher_banniere_tour(joueur, index_joueur, debut);

        /* --- 4. Traitement du contenu de la case révélée --- */
        Case c = plateau->grille[ligne][colonne];

        switch (c.type) {
            case MONSTRE:
                if (combat(joueur, c.monstre) == 0) {
                    reset_cartes_cachees(plateau);
                    continuer = 0;
                }
                break;

            case COFFRE:
                printf("\n"); afficher_marge(); printf("Vous avez trouve un coffre au tresor ! ");
                joueur->trouveCoffre = 1;
                if (joueur->trouveArmeAntique)
                    printf("(Arme antique deja trouvee : continuez pour gagner !)\n");
                else
                    printf("(Il vous reste a trouver votre arme antique : %s)\n",
                           NomArmeAntique(joueur->armeRecherchee));
                break;

            case ARME_ANTIQUE:
                if (c.arme == joueur->armeRecherchee) {
                    printf("\n"); afficher_marge();
                    printf("Vous avez trouve VOTRE arme antique : %s !\n",
                           NomArmeAntique(c.arme));
                    joueur->trouveArmeAntique = 1;
                    if (joueur->trouveCoffre)
                        { afficher_marge(); printf("(Vous avez aussi le coffre : continuez pour gagner !)\n"); }
                    else
                        { afficher_marge(); printf("(Il vous reste a trouver un coffre.)\n"); }
                } else {
                    printf("\n"); afficher_marge();
                    printf("Vous decouvrez une arme antique : %s. Ce n'est pas la votre, continuez !\n",
                           NomArmeAntique(c.arme));
                }
                break;

            case PORTAIL:
                printf("\n"); afficher_marge();
                printf("Portail magique decouvert ! Au prochain tour, vous pourrez vous teleporter n'importe ou sur le plateau.\n");
                joueur->portail_actif = 1;
                continuer = 0;
                break;

            case TOTEM: {
                printf("\n"); afficher_marge();
                printf("Totem de transmutation ! Choisissez une autre case cachee : elle sera echangee avec ce totem.\n");

                int lig_cible, col_cible;
                do {
                    afficher_marge(); printf("Ligne (1-5) : ");
                    lig_cible = lire_entier(1, 5) - 1;
                    afficher_marge(); printf("Colonne (1-5) : ");
                    col_cible = lire_entier(1, 5) - 1;
                    if (plateau->grille[lig_cible][col_cible].revelee == 1)
                        { afficher_marge(); printf("Cette case est deja revelee. Choisissez une case cachee.\n"); }
                    else if (lig_cible == ligne && col_cible == colonne)
                        { afficher_marge(); printf("C'est la case du totem elle-meme. Choisissez une autre case.\n"); }
                } while (plateau->grille[lig_cible][col_cible].revelee == 1
                         || (lig_cible == ligne && col_cible == colonne));

                Case tmp = plateau->grille[ligne][colonne];
                plateau->grille[ligne][colonne]       = plateau->grille[lig_cible][col_cible];
                plateau->grille[lig_cible][col_cible] = tmp;

                retourDepart(joueur);
                reset_cartes_cachees(plateau);
                continuer = 0;
                break;
            }

            case VIDE:
                printf("\n"); afficher_marge(); printf("Case vide. Vous pouvez continuer votre exploration.\n");
                break;
        }

        /* --- 5. Test de victoire --- */
        if (joueurGagne(joueur)) {
            printf("\n"); afficher_marge(); printf(GRAS VERT "%s a gagne !\n" RESET, joueur->nom);
            attendre_entree();
            return 1;
        }

        /* --- 6. Pause avant le sous-tour suivant --- */
        attendre_entree();
    }

    return 0;
}