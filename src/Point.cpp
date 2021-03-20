#include "Point.h"
using namespace std;

Point& Point::operator =(operandeDroite){
    x=operandeDroite.x;
    y=operandeDroite.y;
    return *this;
}
