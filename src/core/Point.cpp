#include "Point.h"
using namespace std;

Point::Point(int valX, int valY) // constructeur par copie de la classe 
{
    x = valX;
    y = valY;
}

Point::Point() {} // constructeur par défaut de la classe 

Point &Point::operator=(const Point &operandeDroite) // gestion de l'opérateur = avec des objets de type Point 
{
    x = operandeDroite.x;
    y = operandeDroite.y;
    return *this;
}
