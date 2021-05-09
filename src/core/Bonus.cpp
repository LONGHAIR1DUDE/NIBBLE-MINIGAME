#include "Bonus.h"
#include <iostream>
#include <cassert>
using namespace std;

Bonus::Bonus() // constructeur par défaut
{
    action = 0;
    position.x = 7;
    position.y = 7;
}

Bonus::Bonus(int i, int x, int y) // constructeur par copie 
{
    action = i;
    position.x = x;
    position.y = y;
}

void Bonus::changeTailleSerpent(Serpent &serp, Terrain &ter) // fonction qui change la taille du serpent 
{
    if (action == 0) // si l'entier qui correspond à une action vaut 0
    { 
        for (int i = 0; i < 5; i++) 
        {
            serp.setMouv(false);
            serp.allongeCorps(ter);
        }
    }
    else // sinon
    {
        for (int i = 0; i < serp.getTailleSerpent(); i++)
        {
            serp.retrecirCorps();
        }
    }
}

void Bonus::inverseMouvement(Serpent &serp)
{
    serp.setMouv(true);
}

void Bonus::actionBonus(Serpent &serp, Terrain &ter)
{
    if (action == 0)
    {
        cout << "Malus!     " << endl;
        changeTailleSerpent(serp, ter);
    }
    else if (action == 1)
    {
        cout << "Bonus! +500" << endl;
        changeTailleSerpent(serp, ter);
        inverseMouvement(serp);
    }
    else 
    {
        cout << "Bonus! x2" << endl;
        inverseMouvement(serp);
    }
}

Point Bonus::getPos()
{
    return position;
}

int Bonus::getX()
{
    return position.x;
}

int Bonus::getY()
{
    return position.y;
}

int Bonus::getAction()
{
    return action;
}

void Bonus::setBonus(int i, int x, int y)
{
    action = i;
    position.x = x;
    position.y = y;
}

void Bonus::testRegression() {
    int indice = 5; 
    int _x = 4; 
    int _y = 3;
    setBonus(indice, _x, _y);
    assert(action == 5 && position.x == 4 && position.y == 3);
    cout << "SetBonus ok!" << endl;

    int ac = getAction();
    assert(ac == 0);
    cout << "getAction ok!" << endl;

    _x = getX();
    _y = getY();
    assert(_x == 7 && _y == 7);
    cout << "getX et getY ok!" << endl;

    Point pos = getPos();
    assert(pos.x == 7 && pos.y == 7);
    cout << "getPos ok!" << endl;

    Terrain ter;
    Serpent serp(3, 5, 7, ter, true);

    inverseMouvement(serp);
    assert(serp.getMouv() == false);
    cout << "inverseMouvement ok!" << endl;

    cout << "Class Bonus: assert ended successfully !" << endl;    

}