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

    void gauche(const Terrain& t);
    void droite(const Terrain& t);
    void haut(const Terrain& t);
    void bas(const Terrain& t);
    Point getCorps(int i)const;
    Point getTete()const;
    void setCorps(int i,int x, int y);
    void setTete(int x, int y);
 };


#endif
