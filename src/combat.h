#ifndef COMBAT_H
#define COMBAT_H

#include "player.h"
#include "cards.h"

const char* NomMonstre(TypeMonstre monstre);

int armeBatMonstre(armeActive arme, TypeMonstre monstre);

void retourDepart(Joueur *joueur);

void combat(Joueur *joueur, TypeMonstre monstre);

int joueurGagne(const Joueur *joueur);

#endif
