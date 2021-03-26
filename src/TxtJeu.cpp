#include <iostream>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif // WIN32

#include "TxtJeu.h"
#include "TxtFenetre.h"
using namespace std;

void AffichageTxt(TxtFenetre& fenetre, const Jeu& jeu) {
    const Terrain& ter = jeu.getTerrain();
    const Serpent& serp = jeu.getSerpent();
    // const Mur& mur = jeu.getMur();
    // const Bonus& bonus = jeu.getBonus();

    fenetre.effacer();

    for (int x = 0; x < ter.getDimX(); x++) 
        for (int y = 0; y < ter.getDimY(); y++)
            fenetre.ecrire(x, y, ter.getXY(x, y));

    fenetre.ecrire(serp.getTete().x, serp.getTete().y, 'O');
    
    fenetre.dessiner();
}

void txtJeu (Jeu& j) {
    TxtFenetre fenetre(j.getTerrain().getDimX(), j.getTerrain().getDimY());

    bool ok = true;
    int c;

    do {
        txtAff(fenetre, j);

        #ifdef _WIN32
        Sleep(100);
		#else
		usleep(100000);
        #endif // WIN32

        j.SerpentBouge();
        j.placementAleatoire();
        
        
        car = fenetre.getCh();
        switch (car) {
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

            case 'q':
            ok = false;
                break;
        }
        

    } while (ok);
}


