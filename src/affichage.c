/*
 * affichage.c — Rendu visuel du jeu dans le terminal
 *
 * Fonctions d'affichage du plateau (grille 5x5 avec bordures Unicode),
 * des joueurs, des cases individuelles, et utilitaires terminal.
 *
 
 *
 * Légende des couleurs :
 *   Bleu atténué → case cachée [ ? ]
 *   Gris foncé   → case vide
 *   Rouge        → monstre
 *   Jaune        → coffre
 *   Magenta      → arme antique
 *   Cyan         → portail
 *   Vert         → totem
 */

#include <stdio.h>
#include <string.h>
#include <time.h>
#include "affichage.h"
#include "joueur.h"
#include "plateau.h"

/* Efface le terminal et positionne le curseur en haut à gauche. */
void effacer_ecran(void){
    printf(EFFACER_ECRAN);
    fflush(stdout);
    printf("\n");
}

/* Imprime MARGE_GAUCHE espaces pour centrer horizontalement le contenu. */
void afficher_marge(void) {
    printf("%*s", MARGE_GAUCHE, "");
}

/*
 * Affiche une case individuelle avec la couleur et la lettre correspondant
 * à son contenu. Affiche [ ? ] si la case n'est pas encore révélée.
 */
void afficher_case(Case c) {
    if (c.revelee == 0){
        printf(BLEU_FAIBLE "[ ? ]" RESET);
        return;
    }

    switch (c.type){
        case VIDE:
            printf(GRIS_FONCE "[   ]" RESET);
            break;

        case MONSTRE:
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
            switch (c.arme) {
                case EPEE_DE_FEU:         printf(MAGENTA "[ E ]" RESET); break;
                case BATON_DES_FAMILIERS: printf(MAGENTA "[ Bt]" RESET); break;
                case GRIMOIRE_INTERDIT:   printf(MAGENTA "[ G ]" RESET); break;
                case DAGUE_DE_SOMMEIL:    printf(MAGENTA "[ D ]" RESET); break;
            }
            break;

        case PORTAIL:
            printf(CYAN "[ P ]" RESET);
            break;

        case TOTEM:
            printf(VERT "[TO ]" RESET);
            break;
    }
}

/* Couleurs associées à chaque joueur (P1=Rouge, P2=Vert, P3=Jaune, P4=Cyan) */
static const char* COULEURS_JOUEURS[] = { ROUGE, VERT, JAUNE, CYAN };

/*
 * Affiche la liste des joueurs avec couleur, côté, arme et indicateur
 * du joueur actif (index_actif >= 0 surligne ce joueur en gras).
 */
void afficher_joueurs(Plateau *plateau, int index_actif) {
    printf("\n");
    afficher_marge();
    printf(GRAS "Joueurs :\n" RESET);
    for (int i = 0; i < plateau->nb_joueurs; i++) {
        Joueur *j = &plateau->joueurs[i];
        const char *couleur = COULEURS_JOUEURS[i];
        afficher_marge();
        if (i == index_actif) {
            printf("  %s" GRAS "[%d] %-12s (%s) - Cote %-6s - Arme: %-8s - Cherche: %-32s ◄ EN JEU" RESET "\n",
                couleur, i + 1, j->nom, NomAventurier(j->type),
                NomCote(j->ligneDepart, j->colonneDepart), NomArme(j->armeChoisi),
                NomArmeAntique(j->armeRecherchee));
        } else {
            printf("  %s[%d] %-12s (%s) - Cote %-6s - Arme: %-8s - Cherche: %s" RESET "\n",
                couleur, i + 1, j->nom, NomAventurier(j->type),
                NomCote(j->ligneDepart, j->colonneDepart), NomArme(j->armeChoisi),
                NomArmeAntique(j->armeRecherchee));
        }
    }
}

/* Légende des symboles, affichée à droite du plateau (une entrée par rangée). */
static const char *legende[5] = {
    GRAS "   LEGENDE :" RESET,
    "   " ROUGE "[ B/Z/T/H ]" RESET " Monstres  " JAUNE "[ C ]" RESET " Coffre",
    "   " CYAN  "[ P ]" RESET " Portail   " VERT  "[TO ]" RESET " Totem",
    "   " MAGENTA "[ E/Bt/G/D ]" RESET " Arme antique",
    "   " GRIS_FONCE "[   ]" RESET " Vide   " BLEU_FAIBLE "[ ? ]" RESET " Cache"
};

/*
 * Affiche la grille 5x5 avec bordures Unicode et marge gauche.
 * Les joueurs encore hors grille sont affichés sur leur bord (N/S/E/O).
 * Les joueurs à l'intérieur sont affichés [Px] sur leur case courante.
 */
void afficher_plateau(Plateau *plateau) {
    /* Identifie les joueurs encore hors grille (position < 0 ou > 4) */
    int nord = -1, est = -1, sud = -1, ouest = -1;
    for (int i = 0; i < plateau->nb_joueurs; i++) {
        Joueur *j = &plateau->joueurs[i];
        if (j->positionLigne < 0 || j->positionLigne > 4) {
            if      (j->ligneDepart   == -1) nord  = i;
            else if (j->colonneDepart ==  5) est   = i;
            else if (j->ligneDepart   ==  5) sud   = i;
            else                             ouest = i;
        }
    }

    /* Joueur Nord au-dessus de la grille */
    if (nord >= 0) {
        printf("\n");
        afficher_marge();
        printf("%19s%s[P%d]" RESET "\n", "", COULEURS_JOUEURS[nord], nord + 1);
    } else {
        printf("\n\n");
    }

    afficher_marge();
    printf("      ┌─────┬─────┬─────┬─────┬─────┐\n");

    for (int i = 0; i < 5; i++) {
        afficher_marge();

        /* Joueur Ouest sur la ligne du milieu uniquement */
        if (i == 2 && ouest >= 0)
            printf("%s[P%d]" RESET "  ", COULEURS_JOUEURS[ouest], ouest + 1);
        else
            printf("      ");

        printf("│");
        for (int j = 0; j < 5; j++) {
            /* Cherche un joueur sur cette case */
            int p = -1;
            for (int k = 0; k < plateau->nb_joueurs; k++) {
                if (plateau->joueurs[k].positionLigne   == i &&
                    plateau->joueurs[k].positionColonne == j) {
                    p = k;
                    break;
                }
            }
            if (p >= 0)
                printf("%s[P%-2d]" RESET, COULEURS_JOUEURS[p], p + 1);
            else
                afficher_case(plateau->grille[i][j]);
            printf("│");
        }

        /* Joueur Est à droite sur la ligne du milieu, sinon padding */
        if (i == 2 && est >= 0)
            printf("  %s[P%d]" RESET, COULEURS_JOUEURS[est], est + 1);
        else
            printf("      ");

        printf("%s\n", legende[i]);

        afficher_marge();
        if (i < 4)
            printf("      ├─────┼─────┼─────┼─────┼─────┤\n");
        else
            printf("      └─────┴─────┴─────┴─────┴─────┘\n");
    }

    /* Joueur Sud sous la grille */
    if (sud >= 0) {
        afficher_marge();
        printf("%19s%s[P%d]" RESET "\n", "", COULEURS_JOUEURS[sud], sud + 1);
    }
}

/*
 * Affiche les objectifs personnels du joueur : coffre et arme antique.
 * Cases cochées en vert ([V]) si déjà trouvées, en rouge ([X]) sinon.
 * Largeur interne = 49 caractères visibles.
 */
void afficher_objectifs(Joueur *joueur) {
    const char *arme = NomArmeAntique(joueur->armeRecherchee);
    char buf[64];

    printf("\n");
    afficher_marge();
    printf("  ┌─ Vos objectifs ─────────────────────────────────┐\n");

    afficher_marge();
    if (joueur->trouveCoffre)
        printf(VERT  "  │  [V] Coffre au tresor                     TROUVE│\n" RESET);
    else
        printf(ROUGE "  │  [X] Coffre au tresor                  a trouver│\n" RESET);

    afficher_marge();
    if (joueur->trouveArmeAntique) {
        snprintf(buf, sizeof(buf), "  [V] %-32s TROUVE", arme);
        printf(VERT  "  │%-49s│\n" RESET, buf);
    } else {
        snprintf(buf, sizeof(buf), "  [X] %-32s cherche", arme);
        printf(ROUGE "  │%-49s│\n" RESET, buf);
    }

    afficher_marge();
    printf("  └─────────────────────────────────────────────────┘\n");
}

/*
 * Affiche un encadré annonçant le tour du joueur avec le chrono.
 * index_joueur est l'index 0-based dans le tableau des joueurs.
 */
void afficher_banniere_tour(Joueur *joueur, int index_joueur, time_t debut) {
    time_t maintenant = time(NULL);
    int duree = (int)difftime(maintenant, debut);
    int min   = duree / 60;
    int sec   = duree % 60;

    const char *couleur = COULEURS_JOUEURS[index_joueur];

    char titre[128];
    snprintf(titre, sizeof(titre),
             "  TOUR DE %s (%s)  [Chrono: %02d:%02d]  ",
             joueur->nom, NomAventurier(joueur->type), min, sec);
    int len = (int)strlen(titre);

    printf("\n");
    afficher_marge();
    printf(GRAS "%s╔", couleur);
    for (int i = 0; i < len; i++) printf("═");
    printf("╗\n");
    afficher_marge();
    printf("║%s║\n", titre);
    afficher_marge();
    printf("╚");
    for (int i = 0; i < len; i++) printf("═");
    printf("╝\n" RESET);
}
