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
        printf("  %s[%d] %-12s (%s) - Cote %-6s - Arme: %s\n" RESET,
            couleur,
            i + 1,
            j->nom,
            NomAventurier(j->type),
            NomCote(j->ligneDepart, j->colonneDepart),
            NomArme(j->armeChoisi));
    }
}

//Affiche le plateau complet
void afficher_plateau(Plateau *plateau) {
    printf("\n  +-----+-----+-----+-----+-----+\n");
    for (int i = 0; i < 5; i++){
        printf("  |");
        for (int j = 0; j < 5; j++){
            afficher_case(plateau->grille[i][j]);
            printf("|");
        }
        printf("\n  +-----+-----+-----+-----+-----+\n");
    }
}


