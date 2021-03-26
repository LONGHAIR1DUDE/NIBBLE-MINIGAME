#include <iostream>
#include "Mur.h"

Mur::Mur (const int x, const int y, const int w, const int h, const Point& direction) {
    mur.x = x;
    mur.y = y;
    mur.w = w;
    mur.h = h;
    posMur[0].x = mur.x;
    posMur[0].y = mur.y;

    if (direction.x == -1) {
        posMur[1].x = posMur[0].x - mur.w;
        posMur[1].y = posMur[0].y;
    }
        
    if (direction.x == 1) {
        posMur[1].x = posMur[0].x + mur.w;
        posMur[1].y = posMur[0].y;
    }

    if (direction.y == -1) {
        posMur[1].x = posMur[0].x;
        posMur[1].y = posMur[0].y - mur.h;
    }

    if (direction.y == 1) {
        posMur[1].x = posMur[0].x;
        posMur[1].y = posMur[0].y + mur.h;
    }

    etatMur = true;
}

Mur::~Mur () {}

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

void Mur::setPos (const int x, const int y) {
    posMur[0].x = x;
    posMur[0].y = y;
}