#include <stdio.h>
#include "display.h"
#include "menu.h"
#include "saisie.h"

int menu_principal(void){
    int choix = 0;

    printf(CLEAR_SCREEN);
    fflush(stdout);
    printf(GRAS CYAN "\n");
    printf("==================================================== \n");
    printf("|||                                              ||| \n");
    printf("|||                    MEMO RPG                  ||| \n");
    printf("|||                                              ||| \n");
    printf("|||                                              ||| \n");
    printf("|||                                              ||| \n");
    printf("|||                                              ||| \n");
    printf("|||               1. NOUVELLE PARTIE             ||| \n");
    printf("|||                                              ||| \n");
    printf("|||                                              ||| \n");
    printf("|||                                              ||| \n");
    printf("|||                                              ||| \n");
    printf("|||  2.QUITTER                                   ||| \n");
    printf("==================================================== \n");
    printf(RESET "\n");
    printf("Votre choix : \n");
    choix = lire_entier(1, 2); //scanf sécurisé 


    return choix;
}




void choisir_joueur(Plateau *plateau){
    int nb = 0;

    printf(GRAS "     ======= CHOIX DES JOUEURS =======   " RESET);

    
    printf("Nombre de joueurs de 2 à 4 joueurs : ");
    nb = lire_entier(2, 4); //scanf sécurisé
    

    plateau->nb_joueurs = nb;

    for (int i = 0; i < nb; i++){
        printf("\n===== Joueur %d =====\n", i + 1);
        creerJoueur(&plateau->joueurs[i]);
    }
}


int menu_final(Plateau *plateau){
    int choix = 0;

    printf(CLEAR_SCREEN);
    fflush(stdout);
    printf(GRAS " === FIN DE PARTIE ===  " RESET);

    
    printf(" 1. Rejouer avec les mêmes joueurs\n");
    printf(" 2. Retour au menu principal\n");
    printf(" Votre choix : \n");
    choix = lire_entier(1, 2);
    

    if(choix == 1){
        for(int i = 0; i < plateau->nb_joueurs; i++){
            plateau->joueurs[i].trouveCoffre = 0;
            plateau->joueurs[i].trouveArmeAntique = 0;
        }
    }

    return choix;
}
