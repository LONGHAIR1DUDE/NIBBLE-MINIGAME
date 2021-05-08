#ifndef _POINT_H
#define _POINT_H
#include <iostream>
using namespace std;

/**
 * \class Point
 * \brief Classe qui permet la création du objet de type Point
 */
class Point
{
public:
    int x;
    int y;

    /**
     * @brief constructeur par copie de la classe Point
     * @param valX de type entier: position en x du point 
     * @param valY de type entier: position en y du point
     * @code 
     * Point::Point(int valX, int valY)
        {
            x = valX;
            y = valY;
        }

     * @endcode 
    */
    Point(int valX, int valY);

    Point();

    Point &operator=(const Point &operandeDroite);
};

#endif
