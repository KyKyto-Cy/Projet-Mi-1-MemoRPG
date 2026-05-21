#include <stdio.h>
#include"display.h"
#include"player.h"


void menu_principal(){
    int choix;

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

    }while(choix < 1 || choix >2);

    return choix;
        
    
}




void choisir_joueur(Plateau *plateau){
    int nb;

    printf(GRAS "     ======= CHOIX DES JOUEURS =======   " RESET);


    do {
            printf("Nombre de joueurs de 2 à 4 joueurs : "); //Demande le nombre de joueurs 
            scanf("%d", &nb);


    }while(nb < 2 || nb > 4); // si le choix n'appartient pas à [2,4] le programme redemande le nombres de joueurs;
    plateau->nb_joueurs = nb; 





    for (int i= 0; i < nb; i++){
        creerJoueur(&plateau->joueurs[i]);
    }

}


void menu_final(Plateau *plateau){
    int choix;

    printf(GRAS " === FIN DE PARTIE ===  "RESET);

    do {
        printf(" 1. Rejouer avec les mêmes joueurs\n");
        printf(" 2. Retour au menu principal\n");
        printf(" Votre choix : \n");
        scanf("%d", &choix);
    } while (choix < 1 || choix > 2);

    if(choix == 1){
        for(int i = 0; i < plateau->nb_joueurs; i++){
            plateau->joueurs[i].a_coffre = 0;
            plateau->joueurs[i].a_arme = 0;
        }
    }else{
        menu_principal();
    }
}
