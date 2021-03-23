#include <iostream>
#include "Mur.h"
#include "Terrain.h"
//constructeur de la class mur
Mur::Mur(Point a,Point b,Point c,Point d)
{
        v=a;
        w=b;
        x=c;
        y=d;
}
//les mutateurs
Point Mur::GetV() const{ return v;}
Point Mur::GetW() const{ return w;}
Point Mur::GetX() const{ return x;}
Point Mur::GetY() const{ return y;}
float Mur::GetMouvementAuto() const {
    return mouvementAuto;
}
//les accesseurs
float Mur::SetMouvementAuto(float a){
    mouvementAuto = a;
}
//procedure du mouvement a gauche
void Mur::m_Gauche(Terrain t)
{       //si la position est valide on translate le mur a gauche d'une case
    if(t.posValide(v.x-1,v.y)) 
    {
        v.x--;
        w.x--;
        x.x--;
        y.x--;
    }

}
void Mur::m_Droite(Terrain t)
{               //si la position est valide on translate le mur a droite d'une case
    if(t.posValide(w.x+1,w.y)) 
    {
        v.x++;
        w.x++;
        x.x++;
        y.x++;
    }
    
}
void Mur::m_Haute(Terrain t)
{           //si la position est valide on translate le mur en haut d'une case
    if(t.posValide(w.x,w.y+1) && t.posValide(v.x,v.y+1)) //pour un rectangle VWXY il faut verifier si la position 
    {                                                    //est valide pour les deux points V et W               
        v.x++;
        w.x++;
        x.x++;
        y.x++;
    }
    
}
void Mur::m_Bas(Terrain t)
{       //si la position est valide on translate le mur en bas d'une case
    if(t.posValide(w.x,w.y-1) && t.posValide(v.x,v.y-1)) //pour un rectangle VWXY il faut verifier si la position 
    {                                                       //est valide pour les deux points V et W 
        v.x--;
        w.x--;
        x.x--;
        y.x--;
    }
    
}
void Mur::m_Mouvement(float Mouvment,Terrain t)
{
    m_Haute(t);
    m_Bas(t);
    m_Bas(t);
    m_Haute(t);
    m_Gauche(t);
    m_Droite(t);

}