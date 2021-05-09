#include <iostream>
#include "Mur.h"

Mur::Mur(const int x, const int y, const int w, const int h) // constructeur par copie de la classe
{
    Point p{0, 0};
    for (int i = 0; i < 2; i++)
    {
        posMur[i].x = p.x;
        posMur[i].y = p.y;
    }
    setPosDim(x, y, w, h); // set la position du mur ainsi que ses dimensions
    setEtatMur(true); // set l'etat du mur 
}

Rect Mur::getMur() const // accesseur sur l'attribue mur 
{
    return mur;
}

bool Mur::getEtatMur() const // accesseur sur l'état du mur
{
    return etatMur;
}

Point Mur::getPos(const int indice) const // accesseur sur la position du mur pour un indice passé en paramètre 
{
    return posMur[indice];
}

void Mur::setEtatMur(const bool e) // mutateur sur l'etat du mur 
{
    etatMur = e;
    if (etatMur) // si le mur est à son état initial
    {
        mur.x = posMur[0].x;
        mur.y = posMur[0].y;
    }
    else // sinon
    {
        mur.x = posMur[1].x;
        mur.y = posMur[1].y;
    }
}

void Mur::setPosDim(const int x, const int y, const int w, const int h) // mutateur sur la position et les dimensions du mur 
{
    mur.w = w;
    mur.h = h;
    posMur[0].x = x;
    posMur[0].y = y;
    mur.x = x;
    mur.y = y;

    posMur[1].x = x;
    posMur[1].y = y;

    if (w > h) // si la largeur du mur est supérieur à sa hauteur 
    {
        posMur[1].x += w; // on set la position du mur en x+w
        posMur[1].y = y;
    }
    else // sinon
    {
        posMur[1].x = x;
        posMur[1].y += h; // on set la position du mur en y+h
    }
}
