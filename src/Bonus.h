#ifndef BONUS_H
#define BONUS_H
#include"Point.h"
#include"Serpent.h"
using namespace std;

class Bonus{
private:
    int action;
    Point position;
    void changeTailleSerpent(Serpent & serp);
    void inverseMouvement(Serpent & serp);

public:
    Bonus(int type, int x, int y);
    void actionBonus();
    Point getPos();
    int getAction();
};

#endif
