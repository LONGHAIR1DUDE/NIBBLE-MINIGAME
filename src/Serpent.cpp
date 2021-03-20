#include "Serpent.h"
#include <cassert>
using namespace std;

Serpent::Serpent(posX, posY){
    corps[0].x=posX;
    corps[0].y=posY;
}

void Serpent::gauche(Terrain t){
    int i=1;
    int t=corps.size();
    Point temp1,temp2;
    temp1=corps[0];
    if(t.posValide(x-1, y)){
        corps[0].x--;
        while(i!=t)
        {
            temp2=corps[i];
            corps[i]=temp1;
            temp1=temp2;
            i++;
        }
    }
}

void Serpent::droite(Terrain t){
    int i=1;
    int t=corps.size();
    Point temp1,temp2;
    temp1=corps[0];
    if(t.posValide(x+1, y)){
        corps[0].x++;
        while(i!=t)
        {
            temp2=corps[i];
            corps[i]=temp1;
            temp1=temp2;
            i++;
        }
    }
}

void Serpent::haut(Terrain t){
    int i=1;
    int t=corps.size();
    Point temp1,temp2;
    temp1=corps[0];
    if(t.posValide(x, y+1)){
        corps[0].y++;
        while(i!=t)
        {
            temp2=corps[i];
            corps[i]=temp1;
            temp1=temp2;
            i++;
        }
    }
}

void Serpent::bas(Terrain t){
    int i=1;
    int t=corps.size();
    Point temp1,temp2;
    temp1=corps[0];
    if(t.posValide(x, y-1)){
        corps[0].y--;
        while(i!=t)
        {
            temp2=corps[i];
            corps[i]=temp1;
            temp1=temp2;
            i++;
        }
    }
}

Point Serpent::getCorps(i){
    return corps[i];
}

Point Serpent::getTete(){
    return corps[0];
}

void Serpent::setCorps(i, x, y){
    corps[i].x=x;
    corps[i].y=y;
}

void Serpent::setCorps(x, y){
    corps[0].x=x;
    corps[0].y=y;
}

