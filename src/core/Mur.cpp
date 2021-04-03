#include <iostream>
#include "Mur.h"

// precondition: direction doit être un point du type (0,1), (1,0), (-1,0) ou (0,-1)
Mur::Mur (const int x, const int y, const int w, const int h) {
    setPosDim(x, y, w, h);
    etatMur = true;
}

Mur::Mur () {}

Rect Mur::getMur () const {
    return mur;
}

bool Mur::getEtatMur () const {
    return  etatMur;
}

Point Mur::getPos (const int indice) const {
    return posMur[indice];
}

void Mur::setEtatMur (const bool e) {
    etatMur = e;
}

void Mur::setPosDim (const int x, const int y, const int w, const int h) {
    mur.w = w;
    mur.h = h;
    posMur[0].x = x;
    posMur[0].y = y;
    mur.x = x;
    mur.y = y;

    if (mur.w > mur.h) {
        posMur[1].x += mur.w;
        posMur[1].y = mur.y;
    } else {
        posMur[1].x = mur.x;
        posMur[1].y += mur.h;
    }
}

