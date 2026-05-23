/*
 * affichage.c — Rendu visuel du jeu dans le terminal
 *
 * Fonctions d'affichage du plateau (grille 5x5 avec bordures ASCII),
 * des joueurs, des cases individuelles, et utilitaires terminal.
 *
 * Légende des couleurs :
 *   Bleu    → case cachée [ ? ]
 *   Blanc   → case vide
 *   Rouge   → monstre
 *   Jaune   → coffre
 *   Magenta → arme antique
 *   Cyan    → portail
 *   Vert    → totem
 */

#include <stdio.h>
#include "affichage.h"
#include "joueur.h"
#include "plateau.h"

/* Efface le terminal et positionne le curseur en haut à gauche. */
void effacer_ecran(void){
    printf(EFFACER_ECRAN);
    fflush(stdout);
    printf("\n");
}

/*
 * Affiche une case individuelle avec la couleur et la lettre correspondant
 * à son contenu. Affiche [ ? ] si la case n'est pas encore révélée.
 */
void afficher_case(Case c) {
    if (c.revelee == 0){
        printf(BLEU "[ ? ]" RESET); /* Case cachée : contenu inconnu */
        return;
    }

    switch (c.type){
        case VIDE:
            printf(BLANC "[   ]" RESET);
            break;

        case MONSTRE:
            /* Chaque monstre a sa propre lettre : B=Basilic, Z=Zombie, T=Troll, H=Harpie */
            switch (c.monstre) {
                case BASILIC: printf(ROUGE "[ B ]" RESET); break;
                case ZOMBIE:  printf(ROUGE "[ Z ]" RESET); break;
                case TROLL:   printf(ROUGE "[ T ]" RESET); break;
                case HARPIE:  printf(ROUGE "[ H ]" RESET); break;
            }
            break;

        case COFFRE:
            printf(JAUNE "[ C ]" RESET);
            break;

        case ARME_ANTIQUE:
            /* E=Épée de feu, B=Bâton des familiers, G=Grimoire, D=Dague */
            switch (c.arme) {
                case EPEE_DE_FEU:         printf(MAGENTA "[ E ]" RESET); break;
                case BATON_DES_FAMILIERS: printf(MAGENTA "[ B ]" RESET); break;
                case GRIMOIRE_INTERDIT:   printf(MAGENTA "[ G ]" RESET); break;
                case DAGUE_DE_SOMMEIL:    printf(MAGENTA "[ D ]" RESET); break;
            }
            break;

        case PORTAIL:
            printf(CYAN "[ P ]" RESET);
            break;

        case TOTEM:
            printf(VERT "[ TO]" RESET);
            break;
    }
}

/* Couleurs associées à chaque joueur (P1=Rouge, P2=Vert, P3=Jaune, P4=Cyan) */
static const char* COULEURS_JOUEURS[] = { ROUGE, VERT, JAUNE, CYAN };

/* Affiche la liste des joueurs avec leur couleur, côté d'entrée et arme active. */
void afficher_joueurs(Plateau *plateau) {
    printf("\n" GRAS "Joueurs :\n" RESET);
    for (int i = 0; i < plateau->nb_joueurs; i++) {
        Joueur *j = &plateau->joueurs[i];
        const char *couleur = COULEURS_JOUEURS[i];
        printf("  %s[%d] %-12s (%s) - Cote %-6s - Arme: %s" RESET "\n",
            couleur,
            i + 1,
            j->nom,
            NomAventurier(j->type),
            NomCote(j->ligneDepart, j->colonneDepart),
            NomArme(j->armeChoisi));
    }
}

/* Légende affichée à droite du plateau pour rappeler les correspondances arme/monstre */
static const char *legende[5] = {
    GRAS "  Armes vs Monstres :" RESET,
    "  Bouclier -> Basilic",
    "  Torche   -> Zombie",
    "  Hache    -> Troll",
    "  Arc      -> Harpie"
};

/*
 * Affiche la grille 5x5 avec les joueurs positionnés sur les bords.
 * Les joueurs sur les bords (position hors grille) sont affichés en [Px]
 * coloré au Nord/Sud/Est/Ouest selon leur case de départ.
 */
void afficher_plateau(Plateau *plateau) {
    /* Identifie quel joueur se trouve sur chaque bord (-1 = personne) */
    int nord = -1, est = -1, sud = -1, ouest = -1;
    for (int i = 0; i < plateau->nb_joueurs; i++) {
        Joueur *j = &plateau->joueurs[i];
        if      (j->ligneDepart   == -1) nord  = i;
        else if (j->colonneDepart ==  5) est   = i;
        else if (j->ligneDepart   ==  5) sud   = i;
        else                             ouest = i;
    }

    /* Affiche le joueur Nord au-dessus de la grille */
    if (nord >= 0)
        printf("\n%19s%s[P%d]" RESET "\n", "", COULEURS_JOUEURS[nord], nord + 1);
    else
        printf("\n\n");

    printf("      +-----+-----+-----+-----+-----+\n");
    for (int i = 0; i < 5; i++) {
        /* Joueur Ouest affiché sur la ligne du milieu (i == 2) uniquement */
        if (i == 2 && ouest >= 0)
            printf("%s[P%d]" RESET "  ", COULEURS_JOUEURS[ouest], ouest + 1);
        else
            printf("      "); /* 6 espaces pour aligner avec [Px] */

        printf("|");
        for (int j = 0; j < 5; j++) {
            afficher_case(plateau->grille[i][j]);
            printf("|");
        }

        /* Joueur Est affiché à droite sur la ligne du milieu */
        if (i == 2 && est >= 0)
            printf("  %s[P%d]" RESET, COULEURS_JOUEURS[est], est + 1);
        else
            printf("      ");

        printf("%s\n      +-----+-----+-----+-----+-----+\n", legende[i]);
    }

    /* Affiche le joueur Sud sous la grille */
    if (sud >= 0)
        printf("%19s%s[P%d]" RESET "\n", "", COULEURS_JOUEURS[sud], sud + 1);
}
