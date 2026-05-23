/*
 * sauvegarde.h — Persistance des statistiques inter-parties
 *
 * Les statistiques sont sauvegardées dans save.txt après chaque partie.
 * Le tableau StatJoueur[] est chargé au lancement et mis à jour en mémoire,
 * puis réécrit sur disque à la fin de chaque partie.
 */

#ifndef SAUVEGARDE_H
#define SAUVEGARDE_H
#include "plateau.h"

/* Capacité maximale du tableau de statistiques en mémoire */
#define MAX_JOUEURS_SAUVEGARDES 100

/* Statistiques cumulées d'un joueur sur toutes ses parties. */
typedef struct {
    char nom[50];      /* Nom du joueur (clé de recherche) */
    int parties_jouees;
    int victoires;
} StatJoueur;

void sauvegarder_stats(StatJoueur stats[], int nb_joueurs);  /* Écrit save.txt */
void charger_stats(StatJoueur stats[], int *nb_joueurs);     /* Lit save.txt */
void afficher_stats(StatJoueur stats[], int nb_joueurs);     /* Affiche le classement trié */
void mettre_a_jour_stats(StatJoueur stats[], int *nb_stats,  /* Met à jour après une partie */
                         Plateau *plateau, int index_gagnant);

#endif
