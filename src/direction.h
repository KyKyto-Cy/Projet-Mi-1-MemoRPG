/*
 * direction.h — Énumération des quatre directions cardinales
 *
 * Les valeurs (0 à 3) correspondent aux indices des tableaux dx[]/dy[]
 * définis dans jeu.c pour calculer les décalages de position.
 */

#ifndef DIRECTION_H
#define DIRECTION_H

typedef enum {
    NORD  = 0, /* Décalage ligne -1, colonne  0 */
    EST   = 1, /* Décalage ligne  0, colonne +1 */
    SUD   = 2, /* Décalage ligne +1, colonne  0 */
    OUEST = 3  /* Décalage ligne  0, colonne -1 */
} Direction;

#endif
