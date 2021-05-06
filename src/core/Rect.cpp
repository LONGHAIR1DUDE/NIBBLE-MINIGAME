#include "Rect.h"
#include <iostream>
using namespace std;

Rect::Rect() {}

Rect::Rect(int cx, int cy, int dw, int dh)
{
    x = cx;
    y = cy;
    w = dw;
    h = dh;
}

Rect::~Rect() {}