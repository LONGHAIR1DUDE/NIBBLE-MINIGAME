#ifndef _TERRAIN_H
#define _TERRAIN_H
#include <iostream>
#include <vector>
#include "Point.h"
#include <string>
#include "Mur.h"
using namespace std;

class Terrain {
private:
    vector<char> ter;
    int dimx;
    int dimy;
    int tailleTerrain;
    Point tabCle[3];
    // vector<Point> posInterrupteur;
    vector<Mur> tabMurs;


public:
    Terrain();
    Terrain(const string& namefile);
    ~Terrain();

    void recupNiveau(const string& nomFichier);
    void posAleaCle();
    bool posValide(int x, int y) const;
    char getXY(const int x, const int y) const;
    void mangeElement(const int x, const int y);
    void appuyerInterrupteur(int x, int y);
    int getDimX() const;
    int getDimY() const;
    int getTailleTerrain() const;
    Point getCle(int i) const;
    Mur getTabMurs(int indice) const;
    int getTailleTabMurs() const;
    // Point getPosInterrupteur(int i) const;
    void testRegression();
    void tabMursTerrain();
    void setXY(const int x, const int y, const char c);
    int compteurPiece();
    bool emplacementLibre(int x, int y) const;
};

#endif
