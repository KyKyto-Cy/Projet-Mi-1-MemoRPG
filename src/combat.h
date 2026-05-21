#ifndef COMBAT_H
#define COMBAT_H

#include "player.h"

typedef enum {
    BASILIC,
    ZOMBIE,
    TROLL,
    HARPIE
} TypeMonstre; // en doublons, faire un choix 

const char* NomMonstre(TypeMonstre monstre);

int armeBatMonstre(armeActive arme, TypeMonstre monstre);

void retourDepart(Joueur *joueur);

void combat(Joueur *joueur, TypeMonstre monstre);

int joueurGagne(Joueur joueur);

#endif
