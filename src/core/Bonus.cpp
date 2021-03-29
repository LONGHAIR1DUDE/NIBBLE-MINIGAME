#include"Bonus.h"
#include<iostream>
#include<cassert>
using namespace std;
Bonus::Bonus()
{
    action = 0;
    position.x = 7;
    position.y = 7;
}
Bonus::Bonus(int i, int x, int y) {
    action = i;
    position.x = x;
    position.y = y;
}

void Bonus::changeTailleSerpent(Serpent & serp,Terrain& ter) {
    
    if(action==0){
        for(int i=0;i<5;i++){
            serp.allongeCorps(ter);
        }
    }
    else{
        for(int i = 0; i < serp.getTailleSerpent() ; i++){
            serp.retrecirCorps();
        }
    }
}

void Bonus::inverseMouvement(Serpent & serp) {
    serp.setMouv(true); 
}

void Bonus::actionBonus(Serpent& serp,Terrain& ter) {
    cout<<"action :"<<action<<endl;
    if(action == 0){
        changeTailleSerpent(serp,ter);
    }
    else{
        changeTailleSerpent(serp,ter);
        inverseMouvement(serp);
    }
}

Point Bonus::getPos(){
    return position;
}
int Bonus::getX()
{
    return position.x;
}
int Bonus::getY()
{
    return position.y;
}
int Bonus::getAction(){
    return action;
}
void Bonus::setBonus(int i, int x, int y) {
    action = i;
    position.x = x;
    position.y = y;
}