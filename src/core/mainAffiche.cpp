#include <iostream>
#include "Terrain.h"
#include "Jeu.h"
using namespace std;

int main()
{
    Terrain terrain("./data/niveau5.txt");
    int tailleX = terrain.getDimX();
    int tailleY = terrain.getDimY();
    int tailleTerrain = terrain.getTailleTerrain();
    cout << "size(): " << tailleTerrain << " "
         << "dimx: " << tailleX << " "
         << "dimy: " << tailleY << endl;
    for (int y = 0; y < tailleY; y++)
    {
        for (int x = 0; x < tailleX; x++)
        {
            cout << terrain.getXY(x, y);
        }
        cout << endl;
    }

    for (int i = 0; i < terrain.getNbCle(); i++)
    {
        cout << terrain.getCle(i).x << " " << terrain.getCle(i).y << endl;
    }

    terrain.supprimeCle(0);

    cout << endl;
    for (int i = 0; i < terrain.getNbCle(); i++)
    {
        cout << terrain.getCle(i).x << " " << terrain.getCle(i).y << endl;
    }
    // for (int i = 0; i < tailleTab; i++) {
    //     // cout << endl;
    //     // cout << i << ": " << terrain.getTabMurs(i).getMur().x << " " << terrain.getTabMurs(i).getMur().y << " "
    //     //     << terrain.getTabMurs(i).getMur().w << " " << terrain.getTabMurs(i).getMur().h << endl;
    //     // cout << "pos1(x y): " << terrain.getTabMurs(i).getPos(0).x << " " << terrain.getTabMurs(i).getPos(0).y << " pos2: "
    //     //     << terrain.getTabMurs(i).getPos(1).x << " " << terrain.getTabMurs(i).getPos(1).y << endl;
    //     // cout << "Etat: " << terrain.getTabMurs(i).getEtatMur() << endl;
    // }

    for (int i = 0; i < terrain.getNbMurs(); i++)
    {
        cout << terrain.getTabMurs(i).getMur().x << " " << terrain.getTabMurs(i).getMur().y << endl;
    }

    return 0;
}
