#ifndef _RECT_H
#define _RECT_H

class Rect
{
public:
  int x, y, w, h; // x et y les coordonnées du première élément du mur et w(width), h(height) pour sa largeur et hauteur.
  Rect();
  Rect(int cx, int cy, int dw, int dh);
  ~Rect();
};

#endif