#include <iostream>
#include "Portail.h"
#include <cassert>
using namespace std;

Portail::Portail(Point pt1, Point pt2) // constructeur par copie de la classe
{
    c1.x = pt1.x;
    c1.y = pt1.y;

    c2.x = pt2.x;
    c2.y = pt2.y;
}

Point Portail::getPortail1() const // accesseur sur le premier portail
{
    return c1;
}

Point Portail::getPortail2() const // accesseur sur le deuxième portail
{
    return c2;
}

void Portail::testRegression() {
    Point p1(3, 5); 
    Point p2(7, 2);

    Point port1 = getPortail1();
    Point port2 = getPortail2();
    assert(port1.x == c1.x && port1.y == c1.y);
    assert(port2.x == c2.x && port2.y == c2.y);
    cout << "Class Portail: assert ended successfully !" << endl;
}