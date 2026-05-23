#ifndef JOUEUR_H
#define JOUEUR_H
#include"cartes.h"

/* Chaque joueur choisit un type d'aventurier */
typedef enum{
    GUERRIER,
    RANGER,
    MAGICIEN,
    VOLEUR
} TypeAventurier;

/* Arme utilisée pendant les combats */
typedef enum {
    BOUCLIER,
    TORCHE,
    ARC,
    HACHE
} armeActive;

/* Contient toutes les informations liées à un joueur */
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
    int portail_actif;

} Joueur;

/* Retourne le nom du type d'aventurier */
const char* NomAventurier(TypeAventurier type);
/* Retourne le nom d'une arme active */
const char* NomArme(armeActive arme);
/* Retourne le nom d'une arme antique */
const char* NomArmeAntique(TypeArmeAntique arme);

/* Associe automatiquement une arme antique selon le type d'aventurier */
TypeArmeAntique associerArmeAntique(TypeAventurier type);

/* Crée un joueur */
void creerJoueur(Joueur *joueur);

/* Demande le nombre de joueurs */
int choisirNombreJoueur(void);

/* Crée tous les joueurs */
void creationJoueur(Joueur joueur[], int nbJoueur);

/* Permet au joueur de changer son arme */
void choisirNouvelleArme(Joueur *joueur);

#endif
