#ifndef MENU_H
#define MENU_H

#include "board.h"
#include "player.h"

int menu_principal(void);
void choisir_joueur(Plateau *plateau);
int menu_final(Plateau *plateau);

#endif
