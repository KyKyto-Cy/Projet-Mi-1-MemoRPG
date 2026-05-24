# Projet Mémo RPG

## Description

Mémo-RPG est un jeu dans lequel des aventuriers avancent dans un labyrinthe à la recherche de leur arme antique et d'un coffre au trésor. Au cours de leur périple ils rencontreront différents monstres ennemis qu'ils devront terrasser s'ils veulent réussir à s'échapper en vie.

Le jeu se joue de 2 à 4 joueurs sur un plateau 5x5 contenant :
- 4 armes antiques
- 2 coffres au trésor
- 16 monstres
- 1 portail magique
- 2 totems de transmutation

Chaque joueur choisit son prénom, son type d'aventurier et son arme active. Le but est de trouver son arme antique **et** un coffre au trésor pour gagner.

### Types d'aventuriers et armes antiques

| Aventurier | Arme antique recherchée        |
|------------|-------------------------------|
| Guerrier   | Épée de feu                   |
| Ranger     | Bâton de contrôle des familiers |
| Magicien   | Grimoire interdit              |
| Voleur     | Dague de sommeil               |

### Monstres et armes efficaces

| Monstre | Arme requise |
|---------|-------------|
| Basilic | Bouclier    |
| Zombie  | Torche      |
| Troll   | Hache       |
| Harpie  | Arc         |

---

## Compilation

Prérequis : `gcc` et `make` installés.

```bash
make          # compile le projet → produit ./memo_rpg
make clean    # supprime les fichiers objets (obj/)
make fclean   # supprime les objets et le binaire
make re       # recompile tout from scratch (fclean + all)
```

## Utilisation

```bash
./memo_rpg
```

ou directement :

```bash
make run
```

### Contrôles en jeu

| Action            | Touche(s)              |
|-------------------|------------------------|
| Se déplacer       | `Z` Nord · `D` Est · `S` Sud · `Q` Ouest |
| Choisir une option | Chiffre correspondant + Entrée |
| Quitter           | Option `3` du menu principal |

Les statistiques (victoires, parties jouées) sont sauvegardées automatiquement dans `save.txt`.

---

## Structure du projet

```
Projet-Mi-1-/
├── src/
│   ├── main.c          Point d'entrée, boucle principale
│   ├── plateau.c/h     Grille 5x5, positionnement des joueurs
│   ├── cartes.c/h      Création et mélange des cartes
│   ├── affichage.c/h   Rendu terminal (couleurs ANSI, bordures Unicode)
│   ├── jeu.c/h         Déroulement des tours, déplacements
│   ├── joueur.c/h      Structure Joueur, création, choix d'arme
│   ├── combat.c/h      Résolution des combats, conditions de victoire
│   ├── menu.c/h        Menus principal, joueurs, fin de partie
│   ├── saisie.c/h      Lectures sécurisées (entier, chaîne, direction)
│   ├── sauvegarde.c/h  Persistance des statistiques dans save.txt
│   ├── chrono.c/h      Mesure et affichage de la durée d'une partie
│   └── direction.h     Enum Direction (Nord/Est/Sud/Ouest)
├── obj/                Fichiers objets générés (ignorés par git)
├── Makefile
└── README.md
```
