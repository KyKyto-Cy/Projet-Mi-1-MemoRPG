/*
 * affichage.h — Macros ANSI et prototypes d'affichage
 *
 * Centralise les séquences d'échappement ANSI pour les couleurs et
 * le contrôle du terminal, ainsi que les prototypes des fonctions d'affichage.
 */

#ifndef AFFICHAGE_H
#define AFFICHAGE_H

#include <time.h>
#include "plateau.h"
#include "joueur.h"

/* --- Contrôle du terminal --- */
#define EFFACER_ECRAN    "\033[2J\033[H" /* Efface l'écran et remet le curseur en haut */
#define MASQUER_CURSEUR  "\033[?25l"     /* Cache le curseur */
#define AFFICHER_CURSEUR "\033[?25h"     /* Affiche le curseur */

/* --- Codes de couleur ANSI --- */
#define RESET       "\033[0m"  /* Réinitialise toutes les couleurs */
#define ROUGE       "\033[31m"
#define VERT        "\033[32m"
#define JAUNE       "\033[33m"
#define BLEU        "\033[34m"
#define MAGENTA     "\033[35m"
#define CYAN        "\033[36m"
#define BLANC       "\033[37m"
#define GRAS        "\033[1m"
#define GRIS_FONCE  "\033[90m"         /* Gris foncé — cases vides */
#define BLEU_FAIBLE "\033[2m\033[34m"  /* Bleu atténué — cases cachées */

void effacer_ecran(void);                              /* Vide le terminal */
void afficher_plateau(Plateau *plateau);               /* Grille 5x5 avec bordures Unicode et joueurs */
void afficher_joueurs(Plateau *plateau, int index_actif); /* Liste des joueurs ; index_actif >= 0 surligne le joueur en cours */
void afficher_case(Case c);                            /* Affiche une case individuelle colorée */
void afficher_banniere_tour(Joueur *joueur, int index_joueur, time_t debut); /* Encadré ╔═╗ avec nom, classe et chrono */
void afficher_objectifs(Joueur *joueur);    /* Boîte ┌─┐ coffre + arme antique avec statut coloré */

#endif
