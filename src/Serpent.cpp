#include "Serpent.h"
#include <cassert>
using namespace std;

Serpent::Serpent(posX, posY){
    corps[0].x=posX;
    corps[0].y=posY;
}

void Serpent::gauche(Terrain t){
    int i=1;
    Point temp1,temp2;
    temp1.x=corps[0].x;
    temp1.y=corps[0].y;
    if(t.posValide(x-1, y)){
        corps[0].x--;
        while(corps[i]!=corps.end())
        {
            temp2.x=corps[i].x;
            temp2.y=corps[i].y;
            corps[i].x=temp1.x;
            corps[i].y=temp1.y;
            temp1.x=temp2.x;
            temp1.y=temp2.y;
            i++;
        }
    }
}
void Serpent::droite(Terrain t){
    int i=1;
    Point temp1,temp2;
    temp1.x=corps[0].x;
    temp1.y=corps[0].y;
    if(t.posValide(x+1, y)){
        corps[0].x++;
        while(corps[i]!=corps.end())
        {
            temp2.x=corps[i].x;
            temp2.y=corps[i].y;
            corps[i].x=temp1.x;
            corps[i].y=temp1.y;
            temp1.x=temp2.x;
            temp1.y=temp2.y;
            i++;
        }
    }
}
void Serpent::haut(Terrain t){
    int i=1;
    Point temp1,temp2;
    temp1.x=corps[0].x;
    temp1.y=corps[0].y;
    if(t.posValide(x, y+1)){
        corps[0].y++;
        while(corps[i]!=corps.end())
        {
            temp2.x=corps[i].x;
            temp2.y=corps[i].y;
            corps[i].x=temp1.x;
            corps[i].y=temp1.y;
            temp1.x=temp2.x;
            temp1.y=temp2.y;
            i++;
        }
    }
}
void Serpent::bas(Terrain t){
    int i=1;
    Point temp1,temp2;
    temp1.x=corps[0].x;
    temp1.y=corps[0].y;
    if(t.posValide(x, y-1)){
        corps[0].y--;
        while(corps[i]!=corps.end())
        {
            temp2.x=corps[i].x;
            temp2.y=corps[i].y;
            corps[i].x=temp1.x;
            corps[i].y=temp1.y;
            temp1.x=temp2.x;
            temp1.y=temp2.y;
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

