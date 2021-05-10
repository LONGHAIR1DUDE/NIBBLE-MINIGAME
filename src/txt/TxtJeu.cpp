#include <iostream>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif // WIN32

#include "TxtJeu.h"
#include "TxtFenetre.h"
using namespace std;

void affichageTxt(TxtFenetre &fenetre, Jeu &jeu) // création d'une fenêtre txt pour l'affichage du niveau 
{
    const Terrain &ter = jeu.getTerrain(); // on appel le terrain
    const Serpent &serp = jeu.getSerpent(); // on appel le serpent

    fenetre.effacer(); // on efface la fenêtre du terminal

    for (int x = 0; x < ter.getDimX(); x++) // boucle for qui parcour la fenêtre et affiche le contenue du tableau ter
        for (int y = 0; y < ter.getDimY(); y++)
        {
            fenetre.ecrire(x, y, ter.getXY(x, y));
        }

    // écriture des portails dans le niveau 
    fenetre.ecrire(jeu.getPortail(0).getPortail1().x,
                   jeu.getPortail(0).getPortail1().y, 'P');
    fenetre.ecrire(jeu.getPortail(0).getPortail2().x,
                   jeu.getPortail(0).getPortail2().y, 'P');

    for (int j = 0; j < jeu.getNbBonus(); j++) // boucle for qui place les bonus dans le niveau
    {
        fenetre.ecrire(jeu.getBonus(j).getX(), jeu.getBonus(j).getY(),
                       ter.getXY(jeu.getBonus(j).getX(), jeu.getBonus(j).getY()));
    }

    for (int i = 0; i < serp.getTailleSerpent(); i++) // boucle for qui positionne le serpent dans le niveau 
    {
        fenetre.ecrire(serp.getCorps(i).x, serp.getCorps(i).y, 'o');
    }

    fenetre.dessiner((getDimTerminale().x / 2) - (ter.getDimX() / 2), // dessine le niveau dans le terminal
                     (getDimTerminale().y / 2) - (ter.getDimY() / 2));
}

void affichageScore(TxtFenetre &fenetre, Jeu &jeu) // création d'une fenêtre pour l'affichage des scores
{
    cout << "NIBBLE" << endl;
    cout << "SCORE: " << jeu.getScore() << endl;
    cout << "MEILLEUR SCORE: " << jeu.stockerMeilleurScore() << endl;
}

void txtJeu(Jeu &j) // boucle de jeu
{
    TxtFenetre fenetre(j.getTerrain().getDimX(), j.getTerrain().getDimY()); // initialisation de la position de la fenetre d'affichage du niveau 
    TxtFenetre score(10, 10); // initialisation de la positino de la fenêtre des scores

    bool etat = true;
    bool ok = true;
    char car;

    do
    {
        // affichage des deux fenêtres précédement initialisées
        affichageTxt(fenetre, j); 
        affichageScore(score, j);

#ifdef _WIN32
        Sleep(100);
#else
        usleep(100000); // pause dans la boucle
#endif // WIN32

        j.setScore(1); // incrémente le score de 1 à chaque passage de boucle
        ok = j.SerpentBouge(); // vérifie que le serpent bouge (si serpentBouge retourne false le jeu s'arrete) 
        j.actionSurSerpent(); // gère les différentes actions sur le serpent
        j.actionPortail(); // gère le fonctionnement des portails
        j.placementAleatoireBonus(); // place aléatoirement les bonus dans le niveau 
        j.actionInterrupteur(etat); // gère le fonctionnement des interrupteurs
        car = fenetre.getCh(); // récupère la touche appuyé par l'utilisateur et fait l'action liée 
        switch (car)
        {
        case 'z':
            j.actionClavier('z');
            break;
        case 'q':
            j.actionClavier('q');
            break;
        case 's':
            j.actionClavier('s');
            break;

        case 'd':
            j.actionClavier('d');
            break;

        case 'l':
            ok = false;
            break;
        }
    } while (ok); // faire ... tant que ok est à true 
}
