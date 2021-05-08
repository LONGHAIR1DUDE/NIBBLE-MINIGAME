#include "Rect.h"
#include <iostream>
using namespace std;

Rect::Rect(int cx, int cy, int dw, int dh)
{
    x = cx;
    y = cy;
    w = dw;
    h = dh;
}

Rect::Rect() {}

Rect::~Rect() {}