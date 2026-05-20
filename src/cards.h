#ifndef CARDS_H
#define CARDS_H

/* Type de contenu d'une case du plateau */
typedef enum {
    VIDE,        /* Case sans contenu particulier */
    MONSTRE,     /* Case occupée par un monstre */
    COFFRE,      /* Case contenant un coffre au trésor */
    ARME_ANTIQUE,/* Case contenant une arme antique */
    PORTAIL,     /* Case portail de téléportation */
    TOTEM        /* Case contenant un totem */
} TypeCase;

/* Types de monstres pouvant apparaître sur le plateau */
typedef enum {
    BASILIC,  /* Monstre : basilic */
    ZOMBIE,   /* Monstre : zombie */
    TROLL,    /* Monstre : troll */
    HARPIE    /* Monstre : harpie */
} TypeMonstre;

/* Types d'armes antiques récupérables sur le plateau */
typedef enum {
    EPEE_DE_FEU,         /* Arme : épée enflammée */
    BATON_DES_FAMILIERS, /* Arme : bâton invoquant des familiers */
    GRIMOIRE_INTERDIT,   /* Arme : grimoire de magie interdite */
    DAGUE_DE_SOMMEIL,    /* Arme : dague infligeant le sommeil */
} TypeArmeAntique;

#endif