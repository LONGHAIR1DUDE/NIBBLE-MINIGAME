#include <iostream>
#include "Mur.h"

Mur::Mur(const int x, const int y, const int w, const int h)
{
    Point p{0, 0};
    for (int i = 0; i < 2; i++)
    {
        posMur[i].x = p.x;
        posMur[i].y = p.y;
    }
    setPosDim(x, y, w, h);
    setEtatMur(true);
}

Rect Mur::getMur() const
{
    return mur;
}

bool Mur::getEtatMur() const
{
    return etatMur;
}

Point Mur::getPos(const int indice) const
{
    return posMur[indice];
}

void Mur::setEtatMur(const bool e)
{
    etatMur = e;
    if (etatMur)
    {
        mur.x = posMur[0].x;
        mur.y = posMur[0].y;
    }
    else
    {
        mur.x = posMur[1].x;
        mur.y = posMur[1].y;
    }
}

void Mur::setPosDim(const int x, const int y, const int w, const int h)
{
    mur.w = w;
    mur.h = h;
    posMur[0].x = x;
    posMur[0].y = y;
    mur.x = x;
    mur.y = y;

    posMur[1].x = x;
    posMur[1].y = y;

    if (w > h)
    {
        posMur[1].x += w;
        posMur[1].y = y;
    }
    else
    {
        posMur[1].x = x;
        posMur[1].y += h;
    }
}
