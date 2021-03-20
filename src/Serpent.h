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
    Serpent(int posX, int posY);

    void gauche(Terrain t);
    void droite(Terrain t);
    void haut(Terrain t);
    void bas(Terrain t);
    Point getCorps(int i);
    Point getTete();
    void setCorps(int i,int x, int y);
    void setTete(int x, int y);
 };


#endif
