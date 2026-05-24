/*
 * combat.c — Résolution des combats et conditions de victoire
 *
 * Chaque arme est efficace contre un seul type de monstre :
 *   Bouclier → Basilic
 *   Torche   → Zombie
 *   Hache    → Troll
 *   Arc      → Harpie
 * Si l'arme est incompatible, le joueur meurt et retourne à sa case de départ.
 */

#include <stdio.h>
#include "combat.h"

/* Retourne le nom lisible du monstre. */
const char* NomMonstre(TypeMonstre monstre){
    if (monstre == BASILIC) { return "Basilic"; }
    if (monstre == ZOMBIE)  { return "Zombie"; }
    if (monstre == TROLL)   { return "Troll"; }
    return "Harpie";
}

/* Retourne 1 si l'arme est efficace contre le monstre, 0 sinon.
   La table de correspondance est fixe (définie par le CDC). */
int armeBatMonstre(armeActive arme, TypeMonstre monstre){
    if (arme == BOUCLIER && monstre == BASILIC) { return 1; }
    if (arme == TORCHE   && monstre == ZOMBIE)  { return 1; }
    if (arme == HACHE    && monstre == TROLL)   { return 1; }
    if (arme == ARC      && monstre == HARPIE)  { return 1; }
    return 0;
}

/* Replace le joueur à sa position de départ (bord du plateau).
   Appelé après une mort, un blocage ou un totem. */
void retourDepart(Joueur *joueur){
    joueur->positionLigne   = joueur->ligneDepart;
    joueur->positionColonne = joueur->colonneDepart;
}

/*
 * Gère un combat entre le joueur et un monstre.
 * Affiche le résultat et retourne 1 (victoire) ou 0 (mort).
 * En cas de mort, retourDepart est appelé ici.
 */
int combat(Joueur *joueur, TypeMonstre monstre){
    printf("Monstre rencontre : %s\n", NomMonstre(monstre));
    printf("Arme utilisee : %s\n", NomArme(joueur->armeChoisi));

    if (armeBatMonstre(joueur->armeChoisi, monstre)) {
        printf("L'arme fonctionne contre ce monstre.\n");
        printf("%s gagne le combat.\n", joueur->nom);
        return 1; /* Victoire : le joueur continue son tour */
    } else {
        printf("Arme incompatible avec ce monstre.\n");
        printf("Retour a la case depart.\n");
        retourDepart(joueur);
        return 0; /* Mort : fin du tour */
    }
}

/*
 * Retourne 1 si le joueur a rempli les deux conditions de victoire :
 * avoir trouvé un coffre ET son arme antique personnelle.
 */
int joueurGagne(const Joueur *joueur){
    return (joueur->trouveCoffre == 1 && joueur->trouveArmeAntique == 1);
}
