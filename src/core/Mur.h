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

class Mur {
private:
  Rect mur;
  Point posMur[2]; // tableau contenant les 2 positions du mur (celle par défaut et la deuxième)
  bool etatMur; // true si le mur est en position initiale et false si il est dans sa deuxième position 

public:
  Mur(const int x, const int y, const int w, const int h);
  Mur();
  
  Rect getMur() const; // retourne les paramètres du mur
  bool getEtatMur() const; // retourne l'etat du mur
  void setEtatMur(const bool e); // modifie l'etat du mur en fonction des paramètres 
  Point getPos(const int indice) const; // retourne le tableau contenant les positions du mur
  void setPos(const int x, const int y); // permet de modifier la position du mur 
  void setDim(const int w, const int h);
};
#endif