#include "Serpent.h"
#include <cassert>
using namespace std;

Serpent::Serpent(int tailleSerp, int posX, int posY, Terrain &t, bool mouvement = false) // constructeur de la classe
{
    if (t.posValide(posX, posY)) // si la position est valide
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
    else // sinon
    {
        posX /= 2; // on divise par 2 la position en x
        posY /= 2; // on divise par 2 la position en y
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

bool Serpent::gauche(const Terrain &t) // gestion du déplacement du serpent vers la gauche 
{
    Point temp1, temp2;
    int tailleSerp = corps.size(); // on récupère la taille du serpent 
    temp1.x = corps[0].x; // on récupère la valeur en x de la tête du serpent
    temp1.y = corps[0].y; // on récupère la valeur en y de la tête du serpent
    if (directionSerpent.x != 1) // si le serpent ne va pas à droite
    {
        if (t.posValide(temp1.x - 1, temp1.y)) // si la position sur la case de gauche est valide
        {
            corps[0].x--; // on décrémente de 1 la valeur en x de la tête du serpent 
            directionSerpent.x = -1; // on change la valeur de direction en x
            directionSerpent.y = 0; // on change la valeur de direction en y
            for (int i = 1; i < tailleSerp; i++) // boucle for qui agit sur le reste du corps du serpent 
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
        else return false;
    }
    return true;
}

bool Serpent::droite(const Terrain &t) // gestion du déplacement du serpent vers la droite 
{
    Point temp1, temp2;
    int tailleSerp = corps.size(); // on récupère la taille du serpent 
    temp1.x = corps[0].x; // on récupère la valeur en x de la tête du serpent
    temp1.y = corps[0].y; // on récupère la valeur en y de la tête du serpent
    if (directionSerpent.x != -1) // si le serpent ne va pas à gauche 
    {
        if (t.posValide(temp1.x + 1, temp1.y)) // si la position sur la case de droite est valide
        {
            corps[0].x++; // on incrémente de 1 la valeur en x de la tête du serpent 
            directionSerpent.x = 1; // on change la valeur de direction en x
            directionSerpent.y = 0; // on change la valeur de direction en y
            for (int i = 1; i < tailleSerp; i++) // boucle for qui agit sur le reste du corps du serpent 
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
        else return false;
    }
    return true;
}

bool Serpent::haut(const Terrain &t) // gestion du déplacement du serpent en haut 
{
    Point temp1, temp2;
    int tailleSerp = corps.size(); // on récupère la taille du serpent 
    temp1.x = corps[0].x; // on récupère la valeur en x de la tête du serpent
    temp1.y = corps[0].y; // on récupère la valeur en y de la tête du serpent
    if (directionSerpent.y != 1) // si le serpent ne va pas en bas
    {
        if (t.posValide(temp1.x, temp1.y - 1)) // si la position sur la case du haut est valide
        {
            corps[0].y--; // on décrémente de 1 la valeur en y de la tête du serpent 
            directionSerpent.x = 0; // on change la valeur de direction en x
            directionSerpent.y = -1; // on change la valeur de direction en y 
            for (int i = 1; i < tailleSerp; i++) // boucle for qui agit sur le reste du corps du serpent 
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
        else return false;
    }
    return true;
}

bool Serpent::bas(const Terrain &t) // gestion du déplacement du serpent en bas
{
    Point temp1, temp2;
    int tailleSerp = corps.size(); // on récupère la taille du serpent 
    temp1.x = corps[0].x; // on récupère la valeur en x de la tête du serpent
    temp1.y = corps[0].y; // on récupère la valeur en y de la tête du serpent
    if (directionSerpent.y != -1) // si le serpent ne va pas en haut
    { 
        if (t.posValide(temp1.x, temp1.y + 1)) // si la position sur la case du bas est valide
        {
            corps[0].y++; // on incrémente de 1 la valeur en y de la tête du serpent 
            directionSerpent.x = 0; // on change la valeur de direction en x
            directionSerpent.y = 1; // on change la valeur de direction en y
            for (int i = 1; i < tailleSerp; i++) // boucle for qui agit sur le reste du corps du serpent 
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
        else return false;
    }
    return true;
}

void Serpent::allongeCorps(const Terrain &t) // allonge le corps du serpent 
{
    corps.push_back(boutSerpent); // ajoute un élément à la fin du tableau corps 
}

void Serpent::retrecirCorps() // retrecie le corps du serpent 
{
    if (getTailleSerpent() < 3){/* on ne fait rien */} // si le serpent à une taille inférieur à 3 
    else
        corps.pop_back(); // on enleve le dernière élément du tableau 
}

Point Serpent::getCorps(const int i) const // accesseur sur un élément du tableau corps 
{
    return corps[i];
}

Point Serpent::getTete() const // accesseur sur la tête du serpent 
{
    return corps[0];
}

bool Serpent::getMouv() const // accesseur sur le mouvement du serpent 
{
    return mouvementInverse;
}

Point Serpent::getDirection() const // accesseur sur la direction du serpent 
{
    return directionSerpent;
}

int Serpent::getTailleSerpent() const // accesseur sur la taille du tableau corps 
{
    return corps.size();
}

void Serpent::setCorps(const int i, const int x, const int y) // mutateur sur l'élément d'indice passé en paramètre du tableau corps
{
    corps[i].x = x;
    corps[i].y = y;
}

void Serpent::setTete(const int x, const int y) // mutateur sur le première élément du tableau corps 
{
    corps[0].x = x;
    corps[0].y = y;
}

void Serpent::setMouv(bool mouv) // mutateur sur le mouvement du serpent
{
    mouvementInverse = mouv;
}

void Serpent::setDirection(int x, int y, const Terrain &t) // mutateur sur la direction du serpent 
{
    if (getDirection().x == -x || getDirection().y == -y){/* on ne fait rien */} // si la direction passé en paramètre est inverse de celle du serpent 
    else
    {
        directionSerpent.x = x;
        directionSerpent.y = y;
    }
}

void Serpent::testRegression()
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
