#include <stdio.h>
#include <string.h>
#include "player.h"

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
    fgets(joueur->nom, 50, stdin);
    joueur->nom[strcspn(joueur->nom, "\n")] = '\0'; // lit toute la ligne même si il y a des espaces

    printf("\nChoisissez votre aventurier :\n");
    printf("0 = Guerrier\n");
    printf("1 = Ranger\n");
    printf("2 = Magicien\n");
    printf("3 = Voleur\n");

    choixType = lire_entier(0, 3);

    

    joueur->type = choixType;

    joueur->armeRecherchee = associerArmeAntique(joueur->type);

    printf("\nChoisissez votre arme active :\n");
    printf("0 = Bouclier\n");
    printf("1 = Torche\n");
    printf("2 = Arc\n");
    printf("3 = Hache\n");

    choixArme = lire_entier(0, 3);


    joueur->armeChoisi = choixArme;

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

    printf("0 = Bouclier\n");
    printf("1 = Torche\n");
    printf("2 = Arc\n");
    printf("3 = Hache\n");

    choixArme = lire_entier(0, 3);


    joueur->armeChoisi = choixArme;
}
