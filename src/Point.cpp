#include "Point.h"
using namespace std;

Point& Point::operator =(const Point& operandeDroite){
    x=operandeDroite.x;
    y=operandeDroite.y;
    return *this;
}
