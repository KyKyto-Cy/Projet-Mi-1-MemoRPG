/*
 * joueur.c — Création et gestion des joueurs
 *
 * Gère la saisie des informations de chaque joueur (nom, type d'aventurier),
 * l'association automatique de l'arme antique recherchée,
 * et le choix d'arme en début de chaque sous-tour.
 */

#include <stdio.h>
#include <string.h>
#include "joueur.h"
#include "saisie.h"

/* Retourne le nom lisible du type d'aventurier. */
const char* NomAventurier(TypeAventurier type){
    if (type == GUERRIER) return "Guerrier";
    if (type == RANGER)   return "Ranger";
    if (type == MAGICIEN) return "Magicien";
    return "Voleur";
}

/* Retourne le nom lisible de l'arme active. */
const char* NomArme(armeActive arme){
    if (arme == BOUCLIER) return "Bouclier";
    if (arme == TORCHE)   return "Torche";
    if (arme == ARC)      return "Arc";
    return "Hache";
}

/* Retourne le nom lisible de l'arme antique. */
const char* NomArmeAntique(TypeArmeAntique arme){
    if (arme == EPEE_DE_FEU)         return "Epee de feu";
    if (arme == BATON_DES_FAMILIERS) return "Baton de controle des familiers";
    if (arme == GRIMOIRE_INTERDIT)   return "Grimoire interdit";
    return "Dague de sommeil";
}

/*
 * Retourne l'arme antique associée au type d'aventurier.
 * Chaque aventurier recherche une arme précise — cette correspondance
 * est fixe et définie par le cahier des charges.
 */
TypeArmeAntique associerArmeAntique(TypeAventurier type) {
    if (type == GUERRIER) return EPEE_DE_FEU;
    if (type == RANGER)   return BATON_DES_FAMILIERS;
    if (type == MAGICIEN) return GRIMOIRE_INTERDIT;
    return DAGUE_DE_SOMMEIL;
}

/*
 * Remplit la structure Joueur par saisie interactive.
 * Initialise tous les champs à leur valeur de départ :
 * position à -1 (hors plateau, sera fixée par positionner_joueurs),
 * arme de départ = Bouclier, tous les flags à 0.
 */
void creerJoueur(Joueur *joueur){
    printf("Entrez votre nom :\n");
    lire_chaine(joueur->nom, 50);

    printf("\nChoisissez votre aventurier :\n");
    printf("1 = Guerrier\n");
    printf("2 = Ranger\n");
    printf("3 = Magicien\n");
    printf("4 = Voleur\n");

    int choixType = lire_entier(1, 4);
    joueur->type = choixType - 1; /* L'enum commence à 0, le menu à 1 */

    /* L'arme antique est déterminée automatiquement par le type d'aventurier */
    joueur->armeRecherchee = associerArmeAntique(joueur->type);
    joueur->armeChoisi     = BOUCLIER; /* Arme par défaut au début */

    /* Position hors plateau : sera affectée par positionner_joueurs() */
    joueur->positionLigne   = -1;
    joueur->positionColonne = -1;
    joueur->ligneDepart     = -1;
    joueur->colonneDepart   = -1;

    /* Flags de progression et d'état */
    joueur->trouveCoffre     = 0;
    joueur->trouveArmeAntique = 0;
    joueur->portail_actif    = 0;
    joueur->vivant           = 1;
}

/* Demande le nombre de joueurs (2 à 4). */
int choisirNombreJoueur(){
    int nbJoueur;
    printf("Nombre de joueurs (entre 2 et 4) :\n");
    nbJoueur = lire_entier(2, 4);
    return nbJoueur;
}

/* Crée tous les joueurs d'une partie en appelant creerJoueur pour chacun. */
void creationJoueur(Joueur joueur[], int nbJoueur){
    for (int i = 0; i < nbJoueur; i++){
        printf("\n===== Joueur %d =====\n", i + 1);
        creerJoueur(&joueur[i]);
    }
}

/* Permet au joueur de choisir son arme au début de chaque sous-tour. */
void choisirNouvelleArme(Joueur *joueur){
    printf("\n%s choisissez votre arme :\n", joueur->nom);
    printf("1 = Bouclier\n");
    printf("2 = Torche\n");
    printf("3 = Arc\n");
    printf("4 = Hache\n");

    int choixArme = lire_entier(1, 4);
    joueur->armeChoisi = choixArme - 1; /* L'enum commence à 0, le menu à 1 */
}
