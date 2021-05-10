# TP Projet LIFAP4: NIBBLE
Ce TP projet est réalisé dans le cadre de l'UE LIFAP4, en 2e année de license Informatique à l'université Claude Bernard de Lyon.
Le thème du projet est le jeu d'arcade Nibble avec des fonctionnalités ainsi que des mécaniques supplémentaires.

lien vers le cahier des charges du projet: https://tomuss.univ-lyon1.fr/=ST-1052892-7Rehr9YcUSGnmdcOozwg-cas.univ-lyon1.fr/2021/Printemps/UE-INF2015L/upload_get/7_15/0_33/UE-INF2015L_DepotCahierDesCharges_nibble_p1803192_p1907354_p1801934.pdf

# Exemple 
- Fruits bonus/malus 
- Portails qui téléporte le serpent d'un point A vers un point B
- Murs qui change de position au passage du serpent sur un interrupteur 
- etc...

## Organisation du code

- `src/`: Contient tous les fichiers `.cpp` et `.h`
    - `src/core/`: contient les fichiers `.cpp` et `.h` 'noyaux' de l'application (tout ce qui est hors affichage graphique).
    - `src/sdl2/`: contient les fichiers `.cpp` et `.h` pour l'affiche graphique avec sdl2.
    - `src/txt/`: contient les fichiers `.cpp` et `.h` pour l'affichage texte dans le terminal.
    

- `obj/`: Contient les fichiers `.obj` créés par le Makefile.

- `bin/`: Contient les différents exécutables créés par le Makefile.

- `data/`: Contient toutes les données (images/fichier.txt pour les niveaux, etc...).

- `Doxyfile`: Fichier qui créer un dossier `doc/` contenant la documentation Doxygen.

- `Makefile`: Fichier de compilation (commande `make`).

## Installation de la SDL 

### Sous Linux 

1. Mise à jour des paquets:

```bash
$ sudo apt-get update && sudo apt-get upgrade
```

2. Installation du paquet de développement SDL:

```bash
$ sudo apt-get install libsdl2-dev
```

## Compilation 

### Linux

1. Lancer la compilation du projet:

    - Compiler les fichiers .cpp
    ```bash
    $ make 
    ```

    - Générer la documentation avec doxygen 
    ```bash
    $ make docu 
    ```

    - Supprimer touts les éxécutables et les fichiers objets
    ```bash
    $ make clean
    ```

2. Les exécutables:

- Exécutable pour lancer les testes de régression:

```bash
$ ./bin/test 
```

- Exécutable qui affiche le Terrain dans le terminal:

```bash
$ ./bin/afficheTerrain
```
- Exécutable qui lance l'application en mode texte:

```bash
$ ./bin/nibble_txt
```

- Exécutable qui lance l'application en mode graphique:

    - résolution 1280x720:
    ```bash
    $ ./bin/nibble_sdl2 0
    ```

    - résolution 960x540:
    ```bash
    $ ./bin/nibble_sdl2 1
    ```
## Les touches

- `z`: Aller en haut.
- `q`: Aller à gauche.
- `s`: Aller en bas.
- `d`: Aller à droite. 

- `l`: Quitter le jeu (txt).
- `echap`: Quitter le jeu (sdl).
