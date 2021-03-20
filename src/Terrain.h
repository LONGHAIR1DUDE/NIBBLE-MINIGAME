#ifndef _TERRAIN_H
#define _TERRAIN_H
#include <iostream>
#include <vector>
#include "Point.h"
#include <string>
using namespace std;

class Terrain {
private:
    vector<char> ter;
    int dimx;
    int dimy;
    int tailleTerrain;
    Point tabCle[3];

public:
    Terrain();
    ~Terrain();

    void recupNiveau(const string& nomFichier);
    void posAleaCle();
    bool posValide(int x, int y);
    char getXY(const int x, const int y) const;
    void mangeBonus(const int x, const int y);
    bool mangePiece(const int x, const int y);
    int getDimX() const;
    int getDimY() const;
    int getTailleTerrain() const;
    // void testRegression();
};


#endif