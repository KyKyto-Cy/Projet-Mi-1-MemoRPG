/*
 * joueur.h — Structure et fonctions relatives aux joueurs
 *
 * Définit les types d'aventuriers, les armes actives,
 * et la structure Joueur qui concentre tout l'état d'un joueur en jeu.
 */

#ifndef JOUEUR_H
#define JOUEUR_H
#include "cartes.h"

/* Les quatre classes d'aventuriers disponibles. */
typedef enum {
    GUERRIER,  /* Fort, maîtrise le bouclier */
    RANGER,    /* Agile, maîtrise le bâton */
    MAGICIEN,  /* Sage, maîtrise le grimoire */
    VOLEUR     /* Furtif, maîtrise la dague */
} TypeAventurier;

/* Armes que le joueur peut équiper avant chaque sous-tour. */
typedef enum {
    BOUCLIER, /* Efficace contre le Basilic */
    TORCHE,   /* Efficace contre le Zombie */
    ARC,      /* Efficace contre la Harpie */
    HACHE     /* Efficace contre le Troll */
} armeActive;

/* Contient tout l'état d'un joueur pendant la partie. */
typedef struct {
    char nom[50];               /* Nom saisi en début de partie */

    TypeAventurier  type;           /* Classe de l'aventurier */
    armeActive      armeChoisi;     /* Arme équipée pour le sous-tour courant */
    TypeArmeAntique armeRecherchee; /* Arme antique à trouver (dépend du type) */

    int ligneDepart;    /* Position de départ (bord du plateau, hors grille) */
    int colonneDepart;

    int positionLigne;  /* Position courante sur la grille */
    int positionColonne;

    int trouveCoffre;      /* 1 si le coffre a été trouvé, 0 sinon */
    int trouveArmeAntique; /* 1 si l'arme antique personnelle a été trouvée */
    int vivant;            /* 1 si le joueur est en vie (réservé pour extensions futures) */
    int portail_actif;     /* 1 si un portail a été activé au tour précédent */
} Joueur;

const char* NomAventurier(TypeAventurier type);       /* Retourne le nom lisible du type */
const char* NomArme(armeActive arme);                 /* Retourne le nom lisible de l'arme active */
const char* NomArmeAntique(TypeArmeAntique arme);     /* Retourne le nom lisible de l'arme antique */
TypeArmeAntique associerArmeAntique(TypeAventurier type); /* Associe l'arme antique au type */

void creerJoueur(Joueur *joueur);        /* Saisie interactive d'un joueur */
void choisirNouvelleArme(Joueur *joueur); /* Choix d'arme en début de sous-tour */

#endif
