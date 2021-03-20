#include <iostream>
#include "mur.h"
#include "Terrain.h"
Mur::Mur(Point a,Point b,Point c,Point d)
{
        v=a;
        w=b;
        x=c;
        y=d;
}
Point Mur::GetV() const{ return v;}
Point Mur::GetW() const{ return w;}
Point Mur::GetX() const{ return x;}
Point Mur::GetY() const{ return y;}
void Mur::m_Gauche(Terrain t)
{
    if(t.posValide(v.x-1,v.y)) 
    {
        v.x--;
        w.x--;
        x.x--;
        y.x--;
    }

}
void Mur::m_Droite(Terrain t)
{
    if(t.posValide(w.x+1,w.y)) 
    {
        v.x++;
        w.x++;
        x.x++;
        y.x++;
    }
    
}
void Mur::m_Haute(Terrain t)
{
    if(t.posValide(w.x,w.y+1) && t.posValide(v.x,v.y+1)) 
    {
        v.y++;
        w.y++;
        x.y++;
        y.y++;
    }
    
}
void Mur::m_Bas(Terrain t)
{
    if(t.posValide(w.x,w.y-1) && t.posValide(v.x,v.y-1)) 
    {
        v.y--;
        w.y--;
        x.y--;
        y.y--;
    }
    
}
