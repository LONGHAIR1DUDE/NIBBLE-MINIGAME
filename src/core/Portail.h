#ifndef _PORTAIL_H
#define _PORTAIL_H
#include "Point.h"

/**
 * \class Portail
 * \brief Classe qui permet la création du objet de type Portail
 */
class Portail
{
private:
    Point c1; //!< c1 de type Point, coordonnées du premier portail
    Point c2; //!< cé de type Point, coordonnées du second portail

public:

    /**
     * @brief constructeur par copie de la classe Portail 
     * @param pt1 de type Point: correspond au premier portail
     * @param pt2 de type Point: correspond au second  portail
     * @code 
     * Portail::Portail(Point pt1, Point pt2)
        {
            c1.x = pt1.x;
            c1.y = pt1.y;

            c2.x = pt2.x;
            c2.y = pt2.y;
        }
     * @endcode 
    */
    Portail(Point pt1, Point pt2);

    /**
     * @brief accesseur qui retourne un point correspondant au premier portail 
     * @code 
     * Point Portail::getPortail1() const
        {
            return c1;
        }
     * @endcode
    */
    Point getPortail1() const;

    /**
     * @brief accesseur qui retourne un point correspondant au second portail 
     * @code 
     * Point Portail::getPortail2() const
        {
            return c2;
        }
     * @endcode
    */
    Point getPortail2() const;

    void testRegression();
};

#endif