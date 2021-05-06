#include <iostream>
#include "Portail.h"
using namespace std;

Portail::Portail(Point pt1, Point pt2)
{
    c1.x = pt1.x;
    c1.y = pt1.y;

    c2.x = pt2.x;
    c2.y = pt2.y;
}

Point Portail::getPortail1() const
{
    return c1;
}

Point Portail::getPortail2() const
{
    return c2;
}