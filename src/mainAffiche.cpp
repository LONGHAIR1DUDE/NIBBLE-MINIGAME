#include <iostream>
#include "Terrain.h"
using namespace std;

int main () {
    Terrain terrain("./data/niveauTest.txt");
    // terrain.posAleaCle();
    int tailleX = terrain.getDimX();
    int tailleY = terrain.getDimY();
    int tailleTerrain = terrain.getTailleTerrain();
    cout << "size(): " << tailleTerrain << " " << "dimx: " << tailleX << " " << "dimy: " << tailleY << endl;
    for (int y = 0; y < tailleY; y++) {
        for (int x = 0; x < tailleX; x++) {
            cout << terrain.getXY(x,y);
        }
    }
    return 0;
}
