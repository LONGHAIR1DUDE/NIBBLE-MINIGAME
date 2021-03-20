#ifndef SERPENT_H
#define SERPENT_H
#include<iostream>
#include <vector>
#include "Terrain.h"
#include "Point.h"
using namespace std;

class Serpent {
private:
    vector<Point> corps;
public:
    Serpent(const int posX, const int posY, const Terrain& t);

    void gauche(const Terrain& t);
    void droite(const Terrain& t);
    void haut(const Terrain& t);
    void bas(const Terrain& t);
    Point getCorps(const int i) const;
    Point getTete() const;
    void setCorps(const int i, const int x, const int y);
    void setTete(const int x, const int y);
    void testRegression();
 };


#endif
