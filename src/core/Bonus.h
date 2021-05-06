#ifndef BONUS_H
#define BONUS_H
#include "Point.h"
#include "Serpent.h"
#include "Terrain.h"
using namespace std;

class Bonus
{
private:
    int action;
    Point position;
    void changeTailleSerpent(Serpent &serp, Terrain &ter);
    void inverseMouvement(Serpent &serp);

public:
    Bonus(int type, int x, int y);
    Bonus();
    void actionBonus(Serpent &serp, Terrain &ter);
    int bonusVitesse();

    Point getPos();
    int getX();
    int getY();
    int getAction();
    void setBonus(int i, int x, int y);
};

#endif