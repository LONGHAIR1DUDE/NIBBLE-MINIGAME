#ifndef SERPENT_H
#define SERPENT_H
#include <iostream>
#include <vector>
#include "Terrain.h"
#include "Point.h"
using namespace std;

/**
 * \class Serpent
 * \brief Classe qui permet la création du serpent
 */
class Serpent
{
private:
    vector<Point> corps; //!< corps de type vector (tableau dynamique), contient les parties du serpent 
    bool mouvementInverse; //!< mouvementInverse de type booléen, définit le sens du mouvement du serpent (par rapport aux touches)
    Point directionSerpent; //!< directionSerpent de type Point, permet de définir la direction du serpent
    Point boutSerpent; //!< boutSerpent de type Point, correspond au dernière élément du serpent 

public:
    /**
     * @brief constructeur de la classe Serpent 
     * @param tailleSerp de type entier: désigne la taille qu'aura le serpent au début de la partie
     * @param posX de type entier: position de départ du serpent en x 
     * @param posY de type entier: position de départ du serpent en y 
     * @param t de type Terrain passée en donnée-résultat: correspond au niveau dans lequel sera implémenté le serpent
     * @param mouvement de type booléen: permet de dire si le serpent bouge ou non
     * @code 
     *  Serpent::Serpent(int tailleSerp, int posX, int posY, Terrain &t, bool mouvement = false)
        {
            if (t.posValide(posX, posY))
            {
                Point p;
                p.x = posX;
                p.y = posY;
                corps.push_back(p);
                mouvementInverse = mouvement;
                directionSerpent.x = 0;
                directionSerpent.y = -1;

                for (int i = 1; i < tailleSerp; i++)
                {
                    p.x = getCorps(i - 1).x;
                    p.y = getCorps(i - 1).y + 1;
                    corps.push_back(p);
                }
            }
        }
     * @endcode
    */
    Serpent(int tailleSerp, int posX, int posY, Terrain &t, bool mouvement);

    /**
     *@brief procédure qui permet au serpent d'aller à gauche
     *@param t de type Terrain passé en donnée-résultat: niveau ou le serpent est implémenté   
     *@code 
        void Serpent::gauche(const Terrain &t)
        {
            Point temp1, temp2;
            int tailleSerp = corps.size();
            temp1.x = corps[0].x;
            temp1.y = corps[0].y;
            if (directionSerpent.x != 1)
            {
                if (t.posValide(temp1.x - 1, temp1.y))
                {
                    corps[0].x--;
                    directionSerpent.x = -1;
                    directionSerpent.y = 0;
                    for (int i = 1; i < tailleSerp; i++)
                    {
                        temp2.x = corps[i].x;
                        temp2.y = corps[i].y;
                        corps[i].x = temp1.x;
                        corps[i].y = temp1.y;
                        temp1.x = temp2.x;
                        temp1.y = temp2.y;
                        if (i == tailleSerp - 1)
                        {
                            boutSerpent.x = temp1.x;
                            boutSerpent.y = temp2.y;
                        }
                    }
                }
            }
        }
     *@endcode
    */
    void gauche(const Terrain &t);

    /**
     *@brief procédure qui permet au serpent d'aller à droite 
     *@param t de type Terrain passé en donnée-résultat: niveau ou le serpent est implémenté   
     *@code 
        void Serpent::droite(const Terrain &t)
        {
            Point temp1, temp2;
            int tailleSerp = corps.size();
            temp1.x = corps[0].x;
            temp1.y = corps[0].y;
            if (directionSerpent.x != -1)
            {
                if (t.posValide(temp1.x + 1, temp1.y))
                {
                    corps[0].x++;
                    directionSerpent.x = 1;
                    directionSerpent.y = 0;
                    for (int i = 1; i < tailleSerp; i++)
                    {
                        temp2.x = corps[i].x;
                        temp2.y = corps[i].y;
                        corps[i].x = temp1.x;
                        corps[i].y = temp1.y;
                        temp1.x = temp2.x;
                        temp1.y = temp2.y;
                        if (i == tailleSerp - 1)
                        {
                            boutSerpent.x = temp1.x;
                            boutSerpent.y = temp2.y;
                        }
                    }
                }
            }
        }
     *@endcode
    */
    void droite(const Terrain &t);

    /**
     *@brief procédure qui permet au serpent d'aller en haut
     *@param t de type Terrain passé en donnée-résultat: niveau ou le serpent est implémenté   
     *@code 
        void Serpent::haut(const Terrain &t)
        {
            Point temp1, temp2;
            int tailleSerp = corps.size();
            temp1.x = corps[0].x;
            temp1.y = corps[0].y;
            if (directionSerpent.y != 1)
            {
                if (t.posValide(temp1.x, temp1.y - 1))
                {
                    corps[0].y--;
                    directionSerpent.x = 0;
                    directionSerpent.y = -1;
                    for (int i = 1; i < tailleSerp; i++)
                    {
                        temp2.x = corps[i].x;
                        temp2.y = corps[i].y;
                        corps[i].x = temp1.x;
                        corps[i].y = temp1.y;
                        temp1.x = temp2.x;
                        temp1.y = temp2.y;
                        if (i == tailleSerp - 1)
                        {
                            boutSerpent.x = temp1.x;
                            boutSerpent.y = temp2.y;
                        }
                    }
                }
            }
        }
     *@endcode
    */
    void haut(const Terrain &t);

    /**
     *@brief procédure qui permet au serpent d'aller en bas
     *@param t de type Terrain passé en donnée-résultat: niveau ou le serpent est implémenté   
     *@code 
        void Serpent::bas(const Terrain &t)
        {
            Point temp1, temp2;
            int tailleSerp = corps.size();
            temp1.x = corps[0].x;
            temp1.y = corps[0].y;
            if (directionSerpent.y != -1)
            {
                if (t.posValide(temp1.x, temp1.y + 1))
                {
                    corps[0].y++;
                    directionSerpent.x = 0;
                    directionSerpent.y = 1;
                    for (int i = 1; i < tailleSerp; i++)
                    {
                        temp2.x = corps[i].x;
                        temp2.y = corps[i].y;
                        corps[i].x = temp1.x;
                        corps[i].y = temp1.y;
                        temp1.x = temp2.x;
                        temp1.y = temp2.y;
                        if (i == tailleSerp - 1)
                        {
                            boutSerpent.x = temp1.x;
                            boutSerpent.y = temp2.y;
                        }
                    }
                }
            }
        }
     *@endcode
    */
    void bas(const Terrain &t);

    /**
     * @brief procédure qui allonge le serpent 
     * @param t de type Terrain passé en donnée-résultat: niveau dans lequel le serpent est implémenté 
     * @code 
*      void Serpent::allongeCorps(const Terrain &t)
        {
            corps.push_back(boutSerpent);
        }
     * @endcode 
    */
    void allongeCorps(const Terrain &t);

    /**
     * @brief procédure qui diminue la taille du serpent 
     * @code 
     * void Serpent::retrecirCorps()
        {
            if (getTailleSerpent() < 3)
            {
            }
            else
                corps.pop_back();
        }
     * @endcode
    */
    void retrecirCorps();

    /**
     * @brief accesseur sur un des éléments du tableau dynamique corps  
     * @param i de type entier: indice du tableau corps
     * @return const Point 
     * @code 
     * Point Serpent::getCorps(const int i) const
        {
            return corps[i];
        }
     * @endcode
    */
    Point getCorps(const int i) const;

    /**
     * @brief accesseur sur le première élément du tableau dynamique corps
     * @return const Point 
     * @code 
     * Point Serpent::getTete() const
        {
            return corps[0];
        }
     * @endcode  
    */
    Point getTete() const;

    /**
     * @brief accesseur sur le booléen mouvement 
     * @return bool
     * @code 
     * bool Serpent::getMouv()
        {
            return mouvementInverse;
        }
     * @endcode
    */
    bool getMouv() const;

    /**
     * @brief accesseur sur la direction du serpent 
     * @return const Point 
     * @code 
     * Point Serpent::getDirection() const
        {
            return directionSerpent;
        }
     * @endcode
    */
    Point getDirection() const;

    /**
     * @brief accesseur sur la taille du tableau dynamique corps
     * @return const int 
     * @code 
        int Serpent::getTailleSerpent() const
        {
            return corps.size();
        }
     * @endcode
    */
    int getTailleSerpent() const;

    /**
     * @brief mutateur sur le tableau dynamique corps
     * @param i de type const entier: indice que l'on souhaite modifier dans le tableau dynamique corps 
     * @param x de type const entier: valeur en x de la position de l'élément du serpent 
     * @param y de type const entier: valeur en y de la position de l'élément du serpent 
     * @code 
     * void Serpent::setCorps(const int i, const int x, const int y)
        {
            corps[i].x = x;
            corps[i].y = y;
        }
     * @endcode 
    */
    void setCorps(const int i, const int x, const int y);

    /**
     * @brief mutateur sur le première élément du tableau dynamique corps 
     * @param x de type const entier: valeur en x de la tête du serpent 
     * @param y de type const entier: valeur en y de la tête du serpent
     * @code 
     * void Serpent::setTete(const int x, const int y)
        {
            corps[0].x = x;
            corps[0].y = y;
        }
     * @endcode 
    */
    void setTete(const int x, const int y);

    /**
     * @brief mutateur sur la valeur du mouvement du serpent 
     * @param mouv de type booléen: true si le serpent bouge false sinon
     * @code 
     * void Serpent::setMouv(bool mouv)
        {
            mouvementInverse = mouv;
        }
     * @endcode 
    */
    void setMouv(bool mouv);

    /**
     * @brief mutateur sur la direction du serpent 
     * @param x de type entier: valeur en x de la tête du serpent 
     * @param y de type entier: valeur en y de la tête du serpent
     * @param t de typr Terrain passé en donnée-résultat: niveau dans lequel est implémenté le serpent 
     * @code
     *  void Serpent::setDirection(int x, int y, const Terrain &t)
        {
            if (getDirection().x == -x || getDirection().y == -y)
            {
            }
            else
            {
                directionSerpent.x = x;
                directionSerpent.y = y;
            }
        }
     * @endcode  
   */
    void setDirection(int x, int y, const Terrain &t);

    /**
     * @brief procédure de test de regression
     * @code 
     * void Serpent::testRegression()
        {
            const Terrain t;
            Point p1(10, 4);
            corps.push_back(p1);
            int x = corps[0].x;
            int y = corps[0].y;

            gauche(t);
            assert(corps[0].x == x - 1);
            assert(corps[0].y == y);
            assert(corps[1].x == x);
            assert(corps[1].y == y);

            haut(t);
            assert(corps[0].x == x - 1);
            assert(corps[0].y == y + 1);
            assert(corps[1].x == x - 1);
            assert(corps[1].y == y);

            Point p2(8, 4);
            corps.pop_back();
            corps.push_back(p2);

            droite(t);
            assert(corps[0].x == x);
            assert(corps[0].y == y + 1);
            assert(corps[1].x == x - 1);
            assert(corps[1].y == y + 1);

            bas(t);
            assert(corps[0].x == x);
            assert(corps[0].y == y);
            assert(corps[1].x == x);
            assert(corps[1].y == y + 1);

            Point val = getCorps(0);
            assert(val.x == corps[0].x);
            assert(val.y == corps[0].y);

            val = getTete();
            assert(val.x == corps[0].x);
            assert(val.y == corps[0].y);

            setCorps(1, 21, 20);
            assert(getCorps(1).x == 21);
            assert(getCorps(1).y == 20);

            setTete(19, 23);
            assert(getTete().x == 19);
            assert(getTete().y == 23);
            cout << "Class Serpent: assert ended successfully." << endl;
        }
     * @endcode
    */
    void testRegression();
};

#endif
