#ifndef BONUS_H
#define BONUS_H
#include "Point.h"
#include "Serpent.h"
#include "Terrain.h"
using namespace std;

/**
 * \class Bonus
 * \brief Classe qui permet la création du objet de type Bonus
 */
class Bonus
{
private:
    int action;
    Point position;

    /**
     * @brief change la taille du serpent en fonction de l'action 
     * @param serp de type Serpent passé en donnée/résultat: serpent dont on va modifier la taille 
     * @param ter de type Terrain passé en donnée/résultat: terrain dans lequel le serpent est placé
     * @code 
     * void Bonus::changeTailleSerpent(Serpent &serp, Terrain &ter)
        {
            if (action == 0)
            {
                for (int i = 0; i < 5; i++)
                {
                    serp.setMouv(false);
                    serp.allongeCorps(ter);
                }
            }
            else
            {
                for (int i = 0; i < serp.getTailleSerpent(); i++)
                {
                    serp.retrecirCorps();
                }
            }
        }
     * @endcode 
    */
    void changeTailleSerpent(Serpent &serp, Terrain &ter);

    /**
     * @brief inverse le mouvement du serpent 
     * @param serp de type Serpent passé en donnée/résultat: serpent sur lequel agit la fonction 
     * @code 
     * void Bonus::inverseMouvement(Serpent &serp)
        {
            serp.setMouv(true);
        }
     * @endcode 
    */
    void inverseMouvement(Serpent &serp);

public:

    /**
     * @brief constructeur par défaut de la classe Bonus
     * @code 
     * Bonus::Bonus()
        {
            action = 0;
            position.x = 7;
            position.y = 7;
        }
     * @endcode 
    */
    Bonus();

    /**
     * @brief constructeur par copie de la classe Bonus 
     * @param i de type entier: indice qui correspond à une action
     * @param x de type entier: position en x du bonus
     * @param y de type entier: position en y du bonus 
     * @code 
     * Bonus::Bonus(int i, int x, int y)
        {
            action = i;
            position.x = x;
            position.y = y;
        }
     * @endcode 
    */
    Bonus(int i, int x, int y);

    /**
     * @brief définit les actions des différents bonus 
     * @param serp de type Serpent passé en donnée/résultat: serpent sur lequel vont être appliqués les effets
     * @param ter de type Terrain passé en donnée/résultat: terrain dans lequel évolue le serpent
     * @code 
     * void Bonus::actionBonus(Serpent &serp, Terrain &ter)
        {
            if (action == 0)
            {
                cout << "Malus!     " << endl;
                changeTailleSerpent(serp, ter);
            }
            else if (action == 1)
            {
                cout << "Bonus! +500" << endl;
                changeTailleSerpent(serp, ter);
                inverseMouvement(serp);
            }
            else 
            {
                cout << "Bonus! x2" << endl;
                inverseMouvement(serp);
            }
        }
     * @endcode 
    */
    void actionBonus(Serpent &serp, Terrain &ter);

    /**
     * @brief accesseur sur la position du bonus
     * @code 
     * Point Bonus::getPos()
        {
            return position;
        }
     * @endcode 
     * @return position de type Point 
    */
    Point getPos();

    /**
     * @brief accesseur sur la valeur en x du bonus 
     * @code 
     * int Bonus::getX()
        {
            return position.x;
        }
     * @endcode 
     * @return position.x de type entier 
    */
    int getX();

    /**
     * @brief accesseur sur la valeur en y du bonus 
     * @code 
     * int Bonus::getY()
        {
            return position.y;
        }
     * @endcode 
     * @return position.y de type entier 
    */
    int getY();

    /**
     * @brief accesseur sur l'action du bonus
     * @code 
     * int Bonus::getAction()
        {
            return action;
        }
     * @endcode 
     * @return action de type entier 
    */
    int getAction();

    /**
     * @brief mutateur sur le bonus 
     * @param i de type entier: indice de l'action du bonus 
     * @param x de type entier: position en x du bonus 
     * @param y de type entier: position en y  du bonus 
     * @code 
     * void Bonus::setBonus(int i, int x, int y)
        {
            action = i;
            position.x = x;
            position.y = y;
        }
        @endcode 
    */
    void setBonus(int i, int x, int y);
};

#endif