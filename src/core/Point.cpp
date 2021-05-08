#include "Point.h"
using namespace std;

Point::Point(int valX, int valY)
{
    x = valX;
    y = valY;
}

Point::Point() {}

Point &Point::operator=(const Point &operandeDroite)
{
    x = operandeDroite.x;
    y = operandeDroite.y;
    return *this;
}
