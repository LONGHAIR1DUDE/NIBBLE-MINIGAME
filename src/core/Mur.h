/*@brief Module gérant un mur dans l'application NIBBLE
Un mur dans l'application NIBBLE est définie par les 4 points v w x y
@file MUR.h
@date 2021/03-->05
*/

#ifndef _MUR_H
#define _MUR_H
/**
@brief La classe MUR contient ses dimensions et un entier indiquant la nature du mouvement
*/

#include "Point.h"
#include "Rect.h"
#include <vector>

/**
 * \class Mur
 * \brief Classe qui permet la création du objet de type Mur
 */
class Mur
{
private:
  Rect mur;
  Point posMur[2]; // tableau contenant les 2 positions du mur (celle par défaut et la deuxième)
  bool etatMur;    // true si le mur est en position initiale et false si il est dans sa deuxième position

public:

  /**
   * @brief Constructeur par copie de la classe Mur 
   * @param x de type entier: position en x du mur
   * @param y de type entier: position en y du mur 
   * @param w de type entier: largeur du mur
   * @param h de type entier: hauteur du mur
   * @code
   * Mur::Mur(const int x, const int y, const int w, const int h)
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
   * @endcode 
  */
  Mur(const int x, const int y, const int w, const int h);

  /**
   * @brief accesseur sur l'objet mur
   * @code 
   * Rect Mur::getMur() const
      {
          return mur;
      }
   * @endcode 
   * @return mur de type Rect 
  */
  Rect getMur() const; // retourne les paramètres du mur

  /**
   * @brief accesseur sur etatMur
   * @code 
   * bool Mur::getEtatMur() const
      {
          return etatMur;
      }
   * @endcode
   * @return etatMur de type booléen 
  */
  bool getEtatMur() const; // retourne l'etat du mur

  /**
   * @brief accesseur sur le tableau posMur 
   * @param indice de type entier: position en x et en y pour une des deux postions du mur
   * @code 
   * Point Mur::getPos(const int indice) const
      {
          return posMur[indice];
      }
   * @endcode 
   * @return posMur de type Point
  */
  Point getPos(const int indice) const; // retourne le tableau contenant les positions du mur

  /**
   * @brief mutateur sur etatMur
   * @param e de type booléen: etat du mur 
   * @code 
   * void Mur::setEtatMur(const bool e)
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
   * @endcode 
  */
  void setEtatMur(const bool e); // modifie l'etat du mur en fonction des paramètres

  /**
   * @brief mutateur sur le tableau posMur 
   * @param x de type entier: position en x du mur
   * @param y de type entier: position en y du mur
   * @param w de type entier: largeur du mur
   * @param h de type entier: hauteur du mur
   * @code 
   * void Mur::setPosDim(const int x, const int y, const int w, const int h)
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
   * @endcode 
  */
  void setPosDim(const int x, const int y, const int w, const int h); // permet de modifier la position du mur
};
#endif