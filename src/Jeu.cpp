#include <iostream>
#include <cstdlib>
#include <cassert>
#include "Jeu.h"
#include <ctime>
#include <chrono>
#include <thread>
using namespace std;

Jeu::Jeu () : Terrain(), Serpent(12, 10, Terrain, true) {
    terrain.mangeBonus(Serpent.getTete().x, Serpent.getTete().y);
}

Jeu::~Jeu () {}

Terrain& Jeu::getTerrain () { return Terrain; }

Serpent& Jeu::getSerpent () {return Serpent;}

Mur& Jeu::getMur(int i) {
    
    return Murs[i];
}

int& Jeu::getNbMurs() {
    return Murs.size();
}  

Portail& Jeu::getPortail(int i) {
    return Portail[i];
}  

int& Jeu::getNbPortails() {
    return Portail.size();
} 

Bonus& Jeu::getBonus(int i) {
    return Bonus[i];
}

int& Jeu::getNbBonus() {
    return Bonus.size();
} 

bool Jeu::actionClavier(const char touche) {
    switch(touche) {
        case 'q': 
            Serpent.gauche(Terrain);
            break;
        
        case 'd': 
            Serpent.droite(Terrain);
            break;
        
        case 'z': 
            Serpent.haut(Terrain);
            break;
        
        case 's': 
            Serpent.bas(Terrain);
            break;
    }
    	if (Terrain.getXY(Serpent.getTete)=='.') {
	    Terrain.mangeBonus(Serpent.getTete());
        return true;
	}
	return false;
}

void Jeu::placementAleatoire() {   
    int dimx=Terrain.getDimX();
    do{
        do{
            srand(time(NULL));
            int x = rand() % Terrain.getDimX();
            
            int y = rand() % Terrain.getDimY();
            
            int i = rand() % Bonus.size();
        } while(!Terrain.posValide(x,y))

        //a modifier faut ajouter un void Terrain::setXYBonus(int x,int y,Bonus b);
        Terrain.ter[y*dimx+x] = Bonus[i];
        this_thread::sleep_for(2s);
        
        if(Terrain.getXY(x,y) == Bonus[i])
            Terrain.ter[y*dimx+x] = '.'; 

    }while(Terrain.getXY(x,y) == ' ');
}

void Jeu::SerpentBouge() {
    Serpent.getTete().x += Serpent.getDirection().x;
    Serpent.getTete().y += Serpent.getDirection().y
}