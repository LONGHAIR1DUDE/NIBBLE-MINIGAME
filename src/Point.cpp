#include "Point.h"
using namespace std;

<<<<<<< HEAD
Point::Point () {}

Point::Point (int valX, int valY) {
    x = valX;
    y = valY; 
}

Point& Point::operator =(const Point& operandeDroite){
    x = operandeDroite.x;
    y = operandeDroite.y;
=======
Point& Point::operator =(const Point& operandeDroite){
    x=operandeDroite.x;
    y=operandeDroite.y;
>>>>>>> 16e022549a4c450dad652710fcb8ba2e2ab1435b
    return *this;
}
