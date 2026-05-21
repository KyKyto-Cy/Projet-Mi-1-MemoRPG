#include<stdio.h>
#include<string.h>

#include "save.h"
#include "display.h"

#define FICHIER_SAVE "save.txt"


void sauvegarder_stats(StatJoueur stats[], int nb_joueurs){
    FILE *fichier = fopen(FICHIER_SAVE, "w");
    if (fichier == NULL){
        printf("Erreur\n");
        return;
    }
    
    fprintf(fichier, "%d\n", nb_joueurs);

    for (int i = 0; i < nb_joueurs; i++ ){
        fprintf(fichier, "%s %d %d\n", stats[i].nom, stats[i].parties_jouees, stats[i].victoires);
    }
    fclose(fichier);
    printf("Sauvegarde effectuee !\n");
}


void charger_stats(StatJoueur stats[], int *nb_joueurs){  // pointeur car on va le modifier
    FILE *fichier = fopen(FICHIER_SAVE, "r");
    if (fichier == NULL){
        *nb_joueurs = 0;
        return;
    }
    fscanf(fichier, "%d\n", nb_joueurs);
    for (int i = 0; i < *nb_joueurs; i++){
        fscanf(fichier, "%s %d %d\n", stats[i].nom, &stats[i].parties_jouees, &stats[i].victoires);
    }
    fclose(fichier);

}


void afficher_stats(StatJoueur stats[], int nb_joueurs){
    printf(GRAS "=== STATISTIQUES ===\n" RESET);
    if(nb_joueurs == 0){
        printf("Aucun joueur enregistré\n");
        return;
    }
    for (int i = 0; i < nb_joueurs; i++ ){
        printf("nom : %s  parties jouées : %d victoires : %d\n", stats[i].nom, stats[i].parties_jouees, stats[i].victoires);
    }


}