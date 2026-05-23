#ifndef COMBAT_H
#define COMBAT_H

#include "player.h"
#include "cards.h"

/* Retourne le nom du monstre */
const char* NomMonstre(TypeMonstre monstre);

/* Vérifie si une arme peut battre un monstre */
int armeBatMonstre(armeActive arme, TypeMonstre monstre);

/* Replace le joueur sur sa case de départ */
void retourDepart(Joueur *joueur);

/* Lance un combat entre un joueur et un monstre */
void combat(Joueur *joueur, TypeMonstre monstre);

/* Vérifie si le joueur a gagné */
int joueurGagne(const Joueur *joueur);

#endif
