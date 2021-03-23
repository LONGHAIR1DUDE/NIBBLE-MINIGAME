#include "Point.h"
using namespace std;

<<<<<<< HEAD
=======

>>>>>>> 35f6076da7139cad2818ca6600e02dc15452123d
Point::Point () {}

Point::Point (int valX, int valY) {
    x = valX;
    y = valY; 
}

Point& Point::operator =(const Point& operandeDroite){
    x = operandeDroite.x;
    y = operandeDroite.y;
<<<<<<< HEAD
=======

>>>>>>> 35f6076da7139cad2818ca6600e02dc15452123d
    return *this;
}
