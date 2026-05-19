#ifndef BOARD_H
#define BOARD_H
#define TAILLE_PLATEAU 5
#define NB_JOUEUR_MAX 4
#define NB_CARTES (TAILLE_PLATEAU * TAILLE_PLATEAU)
// TODO: prototypes des fonctions du module board

#include "player.h"

typedef enum {
    VIDE,
    MONSTRE,
    COFFRE,
    ARME_ANTIQUE,
    PORTAIL,
    TOTEM

}TypeCase; //COMMENTAIRE A FAIRE//

typedef enum {
    BASILIC,
    ZOMBIE,
    TROLL,
    HARPIE

}TypeMonstre;

typedef enum {
    EPEE_DE_FEU,
    BATON_DES_FAMILIERS,
    GRIMOIRE_INTERDIT,
    DAGUE_DE_SOMMEIL,
}TypeArmeAntique;

typedef struct{
    TypeCase type;
    TypeMonstre monstre;
    TypeArmeAntique arme;
    int revelee;
}Case;

typedef struct {
    Case grille[TAILLE_PLATEAU][TAILLE_PLATEAU];
    Joueur joueurs[NB_JOUEUR_MAX];
    int nb_joueurs;
} Plateau;



#endif