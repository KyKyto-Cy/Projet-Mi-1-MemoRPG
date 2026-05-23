# Projet Mémo RPG

## Description

Mémo RPG est un jeu dans lequel des aventuriers avance dans un labyrinthe à la recherche de leur arme antique et un coffre au trésor. Au cours de leur périple ils rencontreront différents monstre ennemis qu'ils devront terasser s'ils veulent réussir à s'échapper en vie.

Le jeux se joue de 2 à 4 joueurs sur un plateau 5x5 contenant:
- 4 armes antiques
- 2 coffres au trésor
- 16 monstres
- 1 portail magique
- 2 totems de transmutation

Chaque joueur entre son prénom au début, choisi son type et une arme active. Le but du jeux est de trouver son arme antique ainsi qu'un coffre au trésor pour que le joueur gagne

Voici les différents type d'aventurier: 

- Guerrier
- Ranger
- Magicien
- Voleur

Les différentes armes antiques reliées aux aventuriers:

- L'épée de feu -> Guerrier
- Baton de contrôle des familiers -> Ranger
- Grimoire interdit -> Magicien
- Dague de sommeil -> Voleur

Les différents monstres rencontrés sur le plateau

- Basilic
- Zombie
- Troll
- Harpie

## Les fonctions utilisées :

### `Board.c`

- Mélange et place les cartes sur la grille
- Positionne chaque joueur sur un côté du plateau avec une symétrie radiale

### `card.C`

- Création des cartes
- Mélange les cartes

### `combat.c`

- Gestion des combats
- Vérification des armes efficaces sur chaque monstre
- Retour à la case départ en cas d'échec

### `display.c`

- Gère l’affichage du plateau

### `game.c`

- Vérifie qu’une case soit accessible
- Gère les tours et les déplacements des joueurs
- Affiche le plateau mise à jour (case révélée ou cachées)

### `player.c` 

- Création de plusieurs joueurs
- Choix du nom, du type d'aventurier et de l'arme antique

### `menu.c`

- Affiche le menu
- Choix du nombre de joueur
- Donne le choix de rejouer avec les mêmes joueurs

### `Saisie.c`

- S’occupe des saisies, vérifie que le nom n’est pas vide

### `Save.c`

- Sauvegarde les stats des joueurs ( parties jouées, nom, nombre de victoire)

