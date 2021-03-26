#include"Bonus.h"
#include<iostream>
#include<cassert>
using namespace std;

Bonus::Bonus(int i, int x, int y) {
    action = i;
    position.x = x;
    position.y = y;
}

void Bonus::changeTailleSerpent(Serpent & serp) {
    if(action>0){
        for(int i=0;i<action;i++){
            serp.allongeCorps();
        }
    }
    else{
        for(int i = 0; i <-(action); i++){
            serp.retrecirCorps();
        }
    }
}

void Bonus::inverseMouvement(Serpent & serp) {
    serp.setMouv(true); 
}

void Bonus::actionBonus() {
    if(action != 0){
        changeTailleSerpent();
    }
    else{
        inverseMouvement();
    }
}

Point Bonus::getPos(){
    return position;
}

int Bonus::getAction(){
    return action;
}

