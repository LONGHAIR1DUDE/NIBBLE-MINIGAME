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
#include "Terrain.h"
#include "Point.h"

class Mur
{ 
private :

    Point v,w,x,y;
    float mouvementAuto;
    void m_Gauche(Terrain t);
    void m_Droite(Terrain t);
    void m_Haute(Terrain t);
    void m_Bas(Terrain t);
public : 
    Mur (Point a,Point b,Point c,Point d);
    void m_Mouvement(float mouvementAuto,Terrain t);
    Point GetV() const;
    Point GetW() const;
    Point GetX() const;
    Point GetY() const;
    float GetMouvementAuto() const;
    float SetMouvementAuto(float a);
    
    
};
#endif