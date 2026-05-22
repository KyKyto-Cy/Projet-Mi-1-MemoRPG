#ifndef DISPLAY_H
#define DISPLAY_H

// TODO: prototypes des fonctions du module display

#include "board.h" //on inclue le fichier du plateau 
#include "player.h"//on inclue le fichier du joueur 

/* Efface l'écran et replace le curseur en haut à gauche */
#define CLEAR_SCREEN    "\033[2J\033[H"
/* Cache / affiche le curseur (utiliser en début et fin de programme) */
#define HIDE_CURSOR     "\033[?25l"
#define SHOW_CURSOR     "\033[?25h"

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
void afficher_case(Case c);

#endif