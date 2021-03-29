#include <iostream>
#include <cstdlib>
#include <cassert>
#include "Jeu.h"
#include <ctime>
#include <chrono>
#include <thread>
#include <fstream>
using namespace std;

Jeu::Jeu (const string& namefile) : serpent(3, terrain.getDimX()/4, terrain.getDimY()/4, terrain, true), score(0) {
    terrain.recupNiveau(namefile);
    terrain.mangeElement(serpent.getTete().x, serpent.getTete().y);
    srand(time(NULL));
    Point a {1, 1};
    Point b {(terrain.getDimX()-2), (terrain.getDimY()-2)};
    Portail p(a, b);
    tabPortail.push_back(p);
}

Jeu::~Jeu () {}

Terrain Jeu::getTerrain () const { return terrain; }

Serpent Jeu::getSerpent () const {return serpent;}

Mur Jeu::getMur(int i) const { 
    return tabMurs[i];
}

int Jeu::getNbMurs() const {
    return tabMurs.size();
}  

Portail Jeu::getPortail (int i) const {
    return tabPortail[i];
}  

int Jeu::getNbPortails() const {
    return tabPortail.size();
} 

Bonus Jeu::getBonus(int i) const {
    return tabBonus[i];
}

int Jeu::getNbBonus() const {
    return tabBonus.size();
} 

int Jeu::getScore () {
    return score;
}

void Jeu::setScore (float num) {
    score += num;
}

int Jeu::stockerBestScore () {
    ifstream monBestScoreL("./data/bestScore.txt");
    float number;
    if (monBestScoreL) {
        monBestScoreL >> number;
        monBestScoreL.close();   
        if (number < score) {
            ofstream monBestScoreE("./data/bestScore.txt");
            if (monBestScoreE) {  
                monBestScoreE << score;
                monBestScoreE.close();
                return score;
            } else {
                cout << "ERREUR: Impossible d'ouvrir le fichier en ecriture !" << endl;
            }
        } else {
            return number;
        }
    } else 
        cout << "ERREUR: Impossible d'ouvrir le fichier en lecture !" << endl;
    return 0;
}

bool Jeu::actionClavier(const char touche) {
    switch(touche) {
        case 'q': if(!serpent.getMouv()) {serpent.droite(terrain);}
           else  {serpent.gauche(terrain);}
            break;
        
        case 'd': if(!serpent.getMouv()) {serpent.gauche(terrain);}
            else  {serpent.droite(terrain);}
            break;
        
        case 'z': if(!serpent.getMouv()) {serpent.bas(terrain);}
            else {serpent.haut(terrain);}
            break;
        
        case 's': if(!serpent.getMouv()) {serpent.haut(terrain);}
            else {serpent.bas(terrain);}
            break;
    }
    if (terrain.getXY(serpent.getTete().x, serpent.getTete().y)=='.') {
	    terrain.mangeElement(serpent.getTete().x, serpent.getTete().y);
            return true;
	}
	return false;
}

void Jeu::placementAleatoire() {   
    
    
    
       
   
        int x,y;
        int a;
        while(tabBonus.empty())
        {
        do{
            
            srand(time(NULL));
            x = rand() % terrain.getDimX();
            
            y = rand() % terrain.getDimY();
            
            a = rand()%2;
            
        } while(!terrain.posValide(x, y) || !terrain.emplacementLibre(x, y));
       
        Bonus b (a,x,y);
        tabBonus.push_back(b);
        
       
        
        terrain.setXY(tabBonus[0].getX() ,tabBonus[0].getY(), 'b');
         
       
        }
       
}

bool Jeu::SerpentBouge() {
    
    Point dir = serpent.getDirection();
    int x = serpent.getTete().x;
    int y = serpent.getTete().y;

    for (int i = 1; i < serpent.getTailleSerpent(); i++) {
        if ((serpent.getCorps(i).x == x) && (serpent.getCorps(i).y == y)) 
            return false;
    }

    if (dir.x == -1) {
        serpent.gauche(terrain);
    }

    if (dir.x == 1) {
        serpent.droite(terrain);
    }

    if (dir.y == -1) {
        serpent.haut(terrain);
    }

    if (dir.y == 1) {
        serpent.bas(terrain);
    }
        
    return true;
}

void Jeu::actionSurSerpent () {
    int x = serpent.getTete().x;
    int y = serpent.getTete().y;
    int cpt = terrain.compteurPiece();
    int dimx = terrain.getDimX();
    int dimy = terrain.getDimY();

    if (terrain.getXY(x, y) == '.') {
        serpent.allongeCorps(terrain);
        terrain.mangeElement(x, y);
        setScore(10);
        cpt--;
    }
    
        if(terrain.getXY(x,y) == 'b')
       {    
           terrain.setXY(tabBonus[0].getX() ,tabBonus[0].getY(), ' ');       
           tabBonus[0].actionBonus(serpent,terrain);
        tabBonus.pop_back();
        
        }

    if (cpt < 30) {
        do {
            x = rand()% dimx;
            y = rand()% dimy;
        } while (!terrain.posValide(x, y) || !terrain.emplacementLibre(x, y));
        terrain.setXY(x, y, '.');
    }
}

void Jeu::actionPortail () {
    int px1 = tabPortail[0].getPortail1().x;
    int py1 = tabPortail[0].getPortail1().y;

    int px2 = tabPortail[0].getPortail2().x;
    int py2 = tabPortail[0].getPortail2().y;
    if ((serpent.getTete().x == px1) && (serpent.getTete().y == py1)) {
        serpent.setTete(px2, py2);
    }

    else if ((serpent.getTete().x == px2) && (serpent.getTete().y == py2)) {
        serpent.setTete(px1, py1);
    }
}