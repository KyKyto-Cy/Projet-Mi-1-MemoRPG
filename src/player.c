#include <stdio.h>
#include <string.h>
#include "player.h"
#include "saisie.h"

const char* NomAventurier(TypeAventurier type){

    if(type == GUERRIER){
        return "Guerrier";
    }

    else if(type == RANGER){
        return "Ranger";
    }

    else if(type == MAGICIEN){
        return "Magicien";
    }

    else{
        return "Voleur";
    }
}

const char* NomArme(armeActive arme){

    if(arme == BOUCLIER){
        return "Bouclier";
    }

    else if(arme == TORCHE){
        return "Torche";
    }

    else if(arme == ARC){
        return "Arc";
    }

    else{
        return "Hache";
    }
}

const char* NomArmeAntique(TypeArmeAntique arme){

    if(arme == EPEE_DE_FEU){
        return "Epee de feu";
    }

    else if(arme == BATON_DES_FAMILIERS){
        return "Baton de controle des familiers";
    }

    else if(arme == GRIMOIRE_INTERDIT){
        return "Grimoire interdit";
    }

    else{
        return "Dague de sommeil";
    }
}

TypeArmeAntique associerArmeAntique(TypeAventurier type) {

    if (type == GUERRIER){
        return EPEE_DE_FEU;
    }

    else if (type == RANGER){
        return BATON_DES_FAMILIERS;
    }

    else if (type == MAGICIEN){
        return GRIMOIRE_INTERDIT;
    }

    else{
        return DAGUE_DE_SOMMEIL;
    }
}

void creerJoueur(Joueur *joueur){

    int choixType;
    int choixArme;

    printf("Entrez votre nom :\n");
    lire_chaine(joueur->nom, 50);

    printf("\nChoisissez votre aventurier :\n");
    printf("1 = Guerrier\n");
    printf("2 = Ranger\n");
    printf("3 = Magicien\n");
    printf("4 = Voleur\n");

    choixType = lire_entier(1, 4);

    joueur->type = choixType - 1;

    joueur->armeRecherchee = associerArmeAntique(joueur->type);

    printf("\nChoisissez votre arme active :\n");
    printf("1 = Bouclier\n");
    printf("2 = Torche\n");
    printf("3 = Arc\n");
    printf("4 = Hache\n");

    choixArme = lire_entier(1, 4);

    joueur->armeChoisi = choixArme - 1;

    joueur->positionLigne = -1;
    joueur->positionColonne = -1;

    joueur->ligneDepart = -1;
    joueur->colonneDepart = -1;

    joueur->trouveCoffre = 0;
    joueur->trouveArmeAntique = 0;

    joueur->vivant = 1;
}

int choisirNombreJoueur(){

    int nbJoueur;

    printf("Nombre de joueurs (entre 2 et 4) :\n");
    nbJoueur = lire_entier(2, 4);


    return nbJoueur;
}

void creationJoueur(Joueur joueur[], int nbJoueur){

    for (int i = 0; i < nbJoueur; i++){

        printf("\n===== Joueur %d =====\n", i + 1);

        creerJoueur(&joueur[i]);
    }
}

void choisirNouvelleArme(Joueur *joueur){

    int choixArme;

    printf("\n%s choisissez votre arme :\n", joueur->nom);

    printf("1 = Bouclier\n");
    printf("2 = Torche\n");
    printf("3 = Arc\n");
    printf("4 = Hache\n");

    choixArme = lire_entier(1, 4);

    joueur->armeChoisi = choixArme - 1;
}
