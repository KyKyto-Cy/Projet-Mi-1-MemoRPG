/*
 * menu.h — Interface des menus de navigation
 */

#ifndef MENU_H
#define MENU_H

#include "plateau.h"
#include "joueur.h"

/* Affiche le menu principal. Retourne 1 (nouvelle partie), 2 (stats), 3 (quitter). */
int menu_principal(void);

/* Demande le nombre de joueurs et crée chaque joueur interactivement. */
void choisir_joueur(Plateau *plateau);

/* Affiche le menu de fin. Retourne 1 (rejouer) ou 2 (menu principal). */
int menu_final(Plateau *plateau);

#endif
