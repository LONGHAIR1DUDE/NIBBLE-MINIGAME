#include "Rect.h"
#include <iostream>
using namespace std;

Rect::Rect(int cx, int cy, int dw, int dh) // constructeur par copie de la classe
{
    x = cx;
    y = cy;
    w = dw;
    h = dh;
}

Rect::Rect() {} // constructeur par défaut de la classe

Rect::~Rect() {} // destructeur de la classe