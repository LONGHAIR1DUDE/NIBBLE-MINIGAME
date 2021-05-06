#ifndef _PORTAIL_H
#define _PORTAIL_H
#include "Point.h"

class Portail
{
private:
    Point c1;
    Point c2;

public:
    Portail(Point pt1, Point pt2);

    Point getPortail1() const;
    Point getPortail2() const;
};

#endif