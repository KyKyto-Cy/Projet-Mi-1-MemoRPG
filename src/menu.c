#include <stdio.h>
#include "display.h"
#include "menu.h"


int menu_principal(void){
    int choix = 0;

    do{

        printf(GRAS CYAN "\n");
        printf("==================================================== \n");
        printf("|||                                              ||| \n");
        printf("|||                    MEMO RPG                  ||| \n");
        printf("|||                                              ||| \n");
        printf("|||                                              ||| \n");
        printf("|||                                              ||| \n");
        printf("|||                                              ||| \n");
        printf("|||               1. NOUVELLE PARTIE               ||| \n");
        printf("|||                                              ||| \n");
        printf("|||                                              ||| \n");
        printf("|||                                              ||| \n");
        printf("|||                                              ||| \n");
        printf("|||  2.QUITTER                                     ||| \n");
        printf("==================================================== \n");
        printf(RESET "\n");
        printf("Votre choix : \n");
        scanf("%d", &choix);

    }while(choix < 1 || choix > 2);

    return choix;
}




void choisir_joueur(Plateau *plateau){
    int nb = 0;

    printf(GRAS "     ======= CHOIX DES JOUEURS =======   " RESET);

    do {
        printf("Nombre de joueurs de 2 à 4 joueurs : ");
        scanf("%d", &nb);
    }while(nb < 2 || nb > 4);

    plateau->nb_joueurs = nb;

    for (int i = 0; i < nb; i++){
        printf("\n===== Joueur %d =====\n", i + 1);
        creerJoueur(&plateau->joueurs[i]);
    }
}


int menu_final(Plateau *plateau){
    int choix = 0;

    printf(GRAS " === FIN DE PARTIE ===  " RESET);

    do {
        printf(" 1. Rejouer avec les mêmes joueurs\n");
        printf(" 2. Retour au menu principal\n");
        printf(" Votre choix : \n");
        scanf("%d", &choix);
    } while (choix < 1 || choix > 2);

    if(choix == 1){
        for(int i = 0; i < plateau->nb_joueurs; i++){
            plateau->joueurs[i].trouveCoffre = 0;
            plateau->joueurs[i].trouveArmeAntique = 0;
        }
    }

    return choix;
}
