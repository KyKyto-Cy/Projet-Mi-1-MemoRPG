#ifndef PLAYER_H
#define PLAYER_H
#include"cards.h"
typedef enum{
    GUERRIER,
    RANGER,
    MAGICIEN,
    VOLEUR
} TypeAventurier;

typedef enum {
    BOUCLIER,
    TORCHE,
    ARC,
    HACHE
} armeActive;



typedef struct{
    char nom[50];

    TypeAventurier type;
    armeActive armeChoisi;
    TypeArmeAntique armeRecherchee;

    int ligneDepart;
    int colonneDepart;

    int positionLigne;
    int positionColonne;

    int trouveCoffre;
    int trouveArmeAntique;
    int vivant;

} Joueur;

const char* NomAventurier(TypeAventurier type);
const char* NomArme(armeActive arme);
const char* NomArmeAntique(TypeArmeAntique arme);

TypeArmeAntique associerArmeAntique(TypeAventurier type);

void creerJoueur(Joueur *joueur);

int choisirNombreJoueur(void);

void creationJoueur(Joueur joueur[], int nbJoueur);

void choisirNouvelleArme(Joueur *joueur);

#endif
