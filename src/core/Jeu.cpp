#include <iostream>
#include <cstdlib>
#include <cassert>
#include "Jeu.h"
#include <ctime>
#include <chrono>
#include <thread>
using namespace std;

Jeu::Jeu () : terrain(), serpent(10, terrain.getDimX()/2, terrain.getDimY()/2, terrain, true) {
    terrain.recupNiveau("./data/niveau3.txt");
    terrain.mangeElement(serpent.getTete().x, serpent.getTete().y);
}

Jeu::~Jeu () {}

Terrain Jeu::getTerrain () const { return terrain; }

Serpent Jeu::getSerpent () const {return serpent;}

Mur Jeu::getMur(int i) const { 
    return murs[i];
}

int Jeu::getNbMurs() const {
    return murs.size();
}  

Portail Jeu::getPortail (int i) const {
    return portail[i];
}  

int Jeu::getNbPortails() const {
    return portail.size();
} 

Bonus Jeu::getBonus(int i) const {
    return bonus[i];
}

int Jeu::getNbBonus() const {
    return bonus.size();
} 

bool Jeu::actionClavier(const char touche) {
    switch(touche) {
        case 'q': 
            serpent.gauche(terrain);
            break;
        
        case 'd': 
            serpent.droite(terrain);
            break;
        
        case 'z': 
            serpent.haut(terrain);
            break;
        
        case 's': 
            serpent.bas(terrain);
            break;
    }
    	if (terrain.getXY(serpent.getTete().x, serpent.getTete().y)=='.') {
	    terrain.mangeElement(serpent.getTete().x, serpent.getTete().y);
        return true;
	}
	return false;
}

void Jeu::placementAleatoire() {   
    int x, y;
    do{
        do{
            srand(time(NULL));
            x = rand() % terrain.getDimX();
            
            y = rand() % terrain.getDimY();
            
            // i = rand() % bonus.size();
        } while(!terrain.posValide(x,y));

        //a modifier faut ajouter un void Terrain::setXYBonus(int x,int y,Bonus b);
        terrain.setXY(y, x, 'b');
        this_thread::sleep_for(2s);
        
        if(terrain.getXY(x,y) == 'b')
            terrain.setXY(y,x, '.'); 

    }while(terrain.getXY(x,y) == ' ');
}

void Jeu::SerpentBouge() {
    Point dir = serpent.getDirection();
    if (dir.x == -1) 
        serpent.gauche(terrain);

    if (dir.x == 1) 
        serpent.droite(terrain);

    if (dir.y == -1) 
        serpent.haut(terrain);

    if (dir.y == 1) 
        serpent.bas(terrain);
}