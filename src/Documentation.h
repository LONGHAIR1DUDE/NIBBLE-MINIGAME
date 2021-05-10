/** \mainpage Nibble

\section Introduction 
Projet réalisé dans le cadre de l'UE LIFAP4 en 2e année de licence Informatique à l'Université Claude Bernard Lyon 1.

\section Pour compiler 
tester sous Linux(Ubuntu) et Windows.

Dépendances:
    \n SDL : https://www.libsdl.org/

\n $ make ou ouvrir le projet avec CodeBlocks puis F9

\section Pour éxecuter 

Ce placer à la racine du projet:
\n $ cd .../nibble_p1803192_p1907354_p1801934

Executer le Makefile:
\n $ make

Executable pour afficher un niveau dans le terminal:
\n $ ./bin/afficher 

Executable pour afficher le résultat des tests de régression:
\n $ ./bin/test

Lancer le jeu en mode texte:
\n $ ./bin/nibble_txt

Lancer le jeu en mode graphique (1280x720):
\n $ ./bin/nibble_sdl2 0

Lancer le jeu en mode graphique (960x540):
\n $ ./bin/nibble_sdl2 1

\section Pour générer la documentation de code

\n Dépendance : Doxygen http://www.stack.nl/~dimitri/doxygen/ 

Créer la documentation avec doxygen:
\n $ doxygen Doxyfile

Ouvrir la documentation doxygen:
\n $ firefox doc/html/index.html

*/
