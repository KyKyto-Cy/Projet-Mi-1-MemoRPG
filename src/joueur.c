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
#include "affichage.h"
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
 * Chaque aventurier recherche une arme précise — correspondance fixe.
 */
TypeArmeAntique associerArmeAntique(TypeAventurier type) {
    if (type == GUERRIER) return EPEE_DE_FEU;
    if (type == RANGER)   return BATON_DES_FAMILIERS;
    if (type == MAGICIEN) return GRIMOIRE_INTERDIT;
    return DAGUE_DE_SOMMEIL;
}

/*
 * Affiche une boîte Unicode décrivant un type d'aventurier.
 * color    : code ANSI de couleur
 * num      : numéro de choix (1-4)
 * name     : nom de la classe
 * arme     : arme antique associée
 * desc     : description de la classe
 */
static void afficher_boite_aventurier(const char *color, int num,
                                      const char *name, const char *arme,
                                      const char *desc) {
    printf("%s  ┌─ %d. %-8s ───────────────────────────┐\n", color, num, name);
    printf("  │  Arme antique : %-24s│\n", arme);
    printf("  │                                         │\n", desc);
    printf("  └─────────────────────────────────────────┘\n" RESET "\n");
}

/*
 * Remplit la structure Joueur par saisie interactive.
 * Affiche des boîtes descriptives pour chaque classe d'aventurier.
 */
void creerJoueur(Joueur *joueur){
    printf("Entrez votre nom :\n");
    lire_chaine(joueur->nom, 50);

    printf("\nChoisissez votre aventurier :\n\n");

    afficher_boite_aventurier(ROUGE,   1, "GUERRIER", "Epee de feu");
    afficher_boite_aventurier(VERT,    2, "RANGER",   "Baton des familiers");
    afficher_boite_aventurier(CYAN,    3, "MAGICIEN", "Grimoire interdit");
    afficher_boite_aventurier(JAUNE,   4, "VOLEUR",   "Dague de sommeil");

    int choixType = lire_entier(1, 4);
    joueur->type = choixType - 1; /* L'enum commence à 0, le menu à 1 */

    joueur->armeRecherchee = associerArmeAntique(joueur->type);
    joueur->armeChoisi     = BOUCLIER;

    joueur->positionLigne   = -1;
    joueur->positionColonne = -1;
    joueur->ligneDepart     = -1;
    joueur->colonneDepart   = -1;

    joueur->trouveCoffre      = 0;
    joueur->trouveArmeAntique = 0;
    joueur->portail_actif     = 0;
    joueur->vivant            = 1;
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
    printf("\n%s" GRAS " Choisissez votre arme :\n" RESET, joueur->nom);
    printf("  1. Bouclier  " ROUGE "(Basilic)" RESET "\n");
    printf("  2. Torche    " ROUGE "(Zombie)" RESET "\n");
    printf("  3. Arc       " ROUGE "(Harpie)" RESET "\n");
    printf("  4. Hache     " ROUGE "(Troll)" RESET "\n");

    int choixArme = lire_entier(1, 4);
    joueur->armeChoisi = choixArme - 1;
}
