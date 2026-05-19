#include <stdio.h>
#include<display.h>


void menu_principal(){
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
        
    



}




void choisir_joueur(Plateau *plateau){
    int nb;

    printf(GRAS "     ======= CHOIX DES JOUEURS =======   ");


    do {
            printf("Nombre de joueurs de 2 à 4 joueurs : "); //Demande le nombre de joueurs 
            scanf("%d", &nb);


    }while(nb < 2 || nb > 4); // si le choix n'appartient pas à [2,4] le programme redemande le nombres de joueurs;
    plateau->nb_joueurs = nb; 





    for (int i= 0; i < nb, i++){
        int choix_aventurier;
        do{
            printf("Nom du joueur %d :", i+1);
            scanf("%s", plateau->joueurs[i].nom); //Saisie des noms
            printf("Choisir votre aventurier : \n");
            printf(" 1.Guerrier\n");
            printf(" 2.Ranger\n");
            printf(" 3.Magicien\n");
            printf(" 4.Voleur\n");
            printf("Votre choix :");
            scanf("%d", &choix_aventurier);
        }while (choix_aventurier < 1 || choix_aventurier > 4)

        switch (choix_aventurier) {
            case 1: 
               plateau->joueurs[i].type = GUERRIER;
               break;
            case 2:
                plateau->joueurs[i].type = RANGER;
                break;
            case 3:
                plateau->joueurs[i].type = MAGICIEN;
                break;
            case 4:
                plateau->joueurs[i].type = VOLEUR;
                break; 

        }
        plateau->joueurs[i].a_coffre = 0;
        plateau->joueurs[i].a_arme = 0;
    }

}


void menu_fin_partie(Plateau *plateau){
    int choix;

    printf(GRAS " === FIN DE PARTIE ===  ");

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
