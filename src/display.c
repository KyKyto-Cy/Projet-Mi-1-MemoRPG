#include <stdio.h>
#include "display.h"
#include "player.h"
#include "board.h"


void effacer_ecran(void){
    printf(CLEAR_SCREEN);
    fflush(stdout);
    printf("\n");
}

void afficher_case(Case c) {
    if (c.revelee == 0){
        printf(BLEU "[ ? ]" RESET); // affiche la case en bleu si la case n'est pas révélée
        return;
    }


switch (c.type){
    case VIDE:
    printf(BLANC "[   ]" RESET); //affiche la case en blanc si le type de la case est VIDE
    break;

    case MONSTRE:
    switch (c.monstre) {
        case BASILIC :
        printf(ROUGE "[ B ]" RESET); //affiche la lettre B sur la case en rouge si le monstre est un basilic
        break;

        case ZOMBIE:
        printf(ROUGE "[ Z ]" RESET);// affiche la lettre Z sur la case en rouge si le monstre est un zombie
        break;

        case TROLL:
        printf(ROUGE "[ T ]" RESET);// affiche la lettre T sur la case en rouge si le monstre est un troll
        break;

        case HARPIE:
        printf(ROUGE "[ H ]" RESET);// affiche la lettre H sur la case en rouge si le monstre est un harpie
        break;
    }
    break;

    case COFFRE:
    printf(JAUNE "[ C ]" RESET);
    break;

    case ARME_ANTIQUE:
    switch (c.arme) {
        case EPEE_DE_FEU :
            printf(MAGENTA "[ E ]" RESET); 
            break;
        case BATON_DES_FAMILIERS: 
            printf(MAGENTA "[ B ]" RESET); 
            break;
        case GRIMOIRE_INTERDIT:   
            printf(MAGENTA "[ G ]" RESET); 
            break;
        case DAGUE_DE_SOMMEIL:    
            printf(MAGENTA "[ D ]" RESET); 
            break;
    }
    break;

    case PORTAIL:
    printf(CYAN "[ P ]"RESET);
    break;

    case TOTEM :
    printf(VERT "[ TO]" RESET);
    break;

}

}


/* Tableau des couleurs par joueur (J1=Rouge, J2=Vert, J3=Jaune, J4=Cyan) */
static const char* COULEURS_JOUEURS[] = { ROUGE, VERT, JAUNE, CYAN };

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

//Affiche le plateau complet avec les joueurs autour
void afficher_plateau(Plateau *plateau) {
    int nord = -1, est = -1, sud = -1, ouest = -1;
    for (int i = 0; i < plateau->nb_joueurs; i++) {
        Joueur *j = &plateau->joueurs[i];
        if      (j->ligneDepart   == -1) nord  = i;
        else if (j->colonneDepart ==  5) est   = i;
        else if (j->ligneDepart   ==  5) sud   = i;
        else                             ouest = i;
    }

    /* Nord : centré sur la colonne 2 du plateau (position 21 = 6 padding + 1 + 12 + 2) */
    if (nord >= 0)
        printf("\n%19s%s[P%d]" RESET "\n", "", COULEURS_JOUEURS[nord], nord + 1);
    else
        printf("\n\n");

    /* Toutes les lignes séparatrices commencent à la position 6 */
    printf("      +-----+-----+-----+-----+-----+\n");
    for (int i = 0; i < 5; i++) {
        /* Gauche : 6 chars fixes — [Px]  ou 6 espaces */
        if (i == 2 && ouest >= 0)
            printf("%s[P%d]" RESET "  ", COULEURS_JOUEURS[ouest], ouest + 1);
        else
            printf("      ");

        printf("|");
        for (int j = 0; j < 5; j++) {
            afficher_case(plateau->grille[i][j]);
            printf("|");
        }

        /* Droite : 2 espaces + [Px] sur la ligne du milieu */
        if (i == 2 && est >= 0)
            printf("  %s[P%d]" RESET, COULEURS_JOUEURS[est], est + 1);

        printf("\n      +-----+-----+-----+-----+-----+\n");
    }

    /* Sud : même centrage que Nord */
    if (sud >= 0)
        printf("%19s%s[P%d]" RESET "\n", "", COULEURS_JOUEURS[sud], sud + 1);
}


