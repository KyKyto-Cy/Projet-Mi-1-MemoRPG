#ifndef COMBAT_H
#define COMBAT_H

#include "joueur.h"
#include "cartes.h"

/* Retourne le nom du monstre */
const char* NomMonstre(TypeMonstre monstre);

/* Vérifie si une arme peut battre un monstre */
int armeBatMonstre(armeActive arme, TypeMonstre monstre);

/* Replace le joueur sur sa case de départ */
void retourDepart(Joueur *joueur);

/* Lance un combat — retourne 1 si victoire, 0 si mort (retour à la case départ) */
int combat(Joueur *joueur, TypeMonstre monstre);

/* Vérifie si le joueur a gagné */
int joueurGagne(const Joueur *joueur);

#endif
