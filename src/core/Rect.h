#ifndef _RECT_H
#define _RECT_H

/**
 * \class Rect
 * \brief Classe qui permet la création du objet de type Rect
 */
class Rect
{
public:
  int x, y, w, h; // x et y les coordonnées du première élément du mur et w(width), h(height) pour sa largeur et hauteur.

  /**
   * @brief Constructeur de la classe Rect
   * @param cx de type entier: correspond à la position en x du rectangle 
   * @param cy de type entier: correspond à la position en y du rectangle
   * @param dw de type entier: correspond à la largeur du rectangle
   * @param dh de type entier: correspond à la hauteur du rectangle 
   * @code
   * Rect::Rect(int cx, int cy, int dw, int dh)
      {
          x = cx;
          y = cy;
          w = dw;
          h = dh;
      }
   * @endcode
  */  
  Rect(int cx, int cy, int dw, int dh);

  Rect();

  /**
   * @brief destructeur de la classe Rect
  */
  ~Rect();
};

#endif