#ifndef AFFICHAGE_H
#define AFFICHAGE_H

// TODO: prototypes des fonctions du module display

#include "plateau.h" //on inclue le fichier du plateau 
#include "joueur.h"//on inclue le fichier du joueur 

/* Efface l'écran et replace le curseur en haut à gauche */
#define EFFACER_ECRAN    "\033[2J\033[H"
/* Cache / affiche le curseur (utiliser en début et fin de programme) */
#define MASQUER_CURSEUR     "\033[?25l"
#define AFFICHER_CURSEUR     "\033[?25h"

// couleur ANSI
#define RESET       "\033[0m"
#define ROUGE       "\033[31m"
#define VERT        "\033[32m"
#define JAUNE       "\033[33m"
#define BLEU        "\033[34m"
#define MAGENTA     "\033[35m"
#define CYAN        "\033[36m"
#define BLANC       "\033[37m"
#define GRAS        "\033[1m"

void effacer_ecran(void);               /* Efface l'écran et ajoute une ligne vide */
void afficher_plateau(Plateau *plateau);
void afficher_joueurs(Plateau *plateau); /* Affiche la liste des joueurs avec couleur, côté et arme */
void afficher_case(Case c);

#endif