#include <iostream>
#include <cstdlib>
#include <cassert>
#include "Jeu.h"
#include <ctime>
#include <chrono>
#include <thread>
#include <fstream>
using namespace std;

Jeu::Jeu (const string& namefile) : serpent(3, terrain.getDimX()/2, 
    terrain.getDimY()/2, terrain, true), score(0) {
    terrain.recupNiveau(namefile);
    terrain.mangeElement(serpent.getTete().x, serpent.getTete().y);
    terrain.tabMursTerrain();
    terrain.placementMurs(true);
    srand(time(NULL));
    Point a {1, 1};
    Point b {(terrain.getDimX()-2), (terrain.getDimY()-2)};
    Portail p(a, b);
    tabPortail.push_back(p);
    srand(time(NULL));
    p_score = &score;
}

Jeu::~Jeu () {}

const Terrain& Jeu::getTerrain () const { return terrain; }

const Serpent& Jeu::getSerpent () const {return serpent;}

Mur Jeu::getMur(int i) { 
    return terrain.getTabMurs(i);
}

int Jeu::getNbMurs() const {
    return terrain.getNbMurs();
}  

Portail& Jeu::getPortail (int i) {
    return tabPortail[i];
}  

int Jeu::getNbPortails() const {
    return tabPortail.size();
} 

Bonus& Jeu::getBonus(int i) {
    return tabBonus[i];
}

int Jeu::getNbBonus() const {
    return tabBonus.size();
} 

int Jeu::getScore () {
    return score;
}

int Jeu::getMeilleurScore () {
    return meilleurScore;
}

void Jeu::setScore (int val) {
    *p_score += val;
}

int Jeu::stockerMeilleurScore () {
    ifstream monMeilleurScoreL("./data/bestScore.txt");
    if (monMeilleurScoreL) {
        monMeilleurScoreL >> meilleurScore;
        monMeilleurScoreL.close();   
        if (meilleurScore < score) {
            ofstream monMeilleurScoreE("./data/bestScore.txt");
            if (monMeilleurScoreE) {  
                monMeilleurScoreE << score;
                monMeilleurScoreE.close();
                meilleurScore = score;
                return score;
            } else {
                cout << "ERREUR: Impossible d'ouvrir le fichier en ecriture !" << endl;
            }
        } else {
            return meilleurScore;
        }
    } else 
        cout << "ERREUR: Impossible d'ouvrir le fichier en lecture !" << endl;
    return 0;
}

bool Jeu::actionClavier(const char touche) {
    switch(touche) {
        case 'q': if(!serpent.getMouv()) {serpent.setDirection(1,0,terrain);}
           else  {serpent.setDirection(-1,0,terrain);}
            break;
        
        case 'd': if(!serpent.getMouv()) {serpent.setDirection(-1,0,terrain);}
            else  {serpent.setDirection(1,0,terrain);}
            break;
        
        case 'z': if(!serpent.getMouv()) {serpent.setDirection(0,1,terrain);}
            else {serpent.setDirection(0,-1,terrain);}
            break;
        
        case 's': if(!serpent.getMouv()) {serpent.setDirection(0,-1,terrain);}
            else {serpent.setDirection(0,1,terrain);}
            break;
    }
    if (terrain.getXY(serpent.getTete().x, serpent.getTete().y)=='.') {
	    terrain.mangeElement(serpent.getTete().x, serpent.getTete().y);
            return true;
	}
	return false;
}

void Jeu::placementAleatoireBonus() {      
    int x, y, a;
    int dimx = terrain.getDimX();
    int dimy = terrain.getDimY();

    // boucle for qui créé et stocke 3 bonus dans le tableau tabBonus
    for (int i = 0; i < 3; i++) {
        a = rand()% 3;
        if (i == 0) {
            do {
                x = rand()% dimx;
                y = rand()% dimy;
            } while(!terrain.posValide(x, y)); 
        } else {
            do {
                x = rand()% dimx;
                y = rand()% dimy;        
            } while(!terrain.posValide(x, y) || ((tabBonus[i-1].getX() == x) 
                    && (tabBonus[i-1].getY() == y))); 
        }
        Bonus b(a, x, y);
        tabBonus.push_back(b);
        terrain.setXY(tabBonus[i].getX(), tabBonus[i].getY(), 'b');
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
    char element = terrain.getXY(x, y);
    int nbCle = terrain.getNbCle();
    int tailleTabBonus = tabBonus.size();

    for (int i = 0; i < nbCle; i++) {
        terrain.setXY(terrain.getCle(i).x, terrain.getCle(i).y, 'c');
    }

    if (element == '.') {
        serpent.allongeCorps(terrain);
        terrain.mangeElement(x, y);
        setScore(100);
        cpt--;
    }
    
    if(element == 'b') { 
        terrain.mangeElement(x, y);  
        int indice, action, coordx, coordy; 
        for (int i = 0; i < tailleTabBonus; i++) {
            if (x == tabBonus[i].getX() && y == tabBonus[i].getY()) {
                indice = i;
                break;
            }
        }    

        tabBonus[indice].actionBonus(serpent, terrain);

        do {
            action = rand()% 3;
            coordx = rand()% dimx;
            coordy = rand()% dimy;
        } while(!terrain.posValide(coordx, coordy) || !terrain.emplacementLibre(coordx, coordy));
        tabBonus[indice].setBonus(action, coordx, coordy);
    }

    if (cpt < 30) {
        do {
            x = rand()% dimx;
            y = rand()% dimy;
        } while (!terrain.posValide(x, y) || !terrain.emplacementLibre(x, y));
        terrain.setXY(x, y, '.');
    }

    if (element == 'c') {
        terrain.mangeElement(x, y);
        for (int i = 0; i < 3; i++) 
            if ((terrain.getCle(i).x == x) && (terrain.getCle(i).y == y)) {
                terrain.supprimeCle(i);
                break;
            } 
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

void Jeu::actionInterrupteur (bool& etat) {
    int x = serpent.getTete().x;
    int y = serpent.getTete().y;
    if (terrain.getXY(x, y) == 'i') {
        if (etat)
            etat = false;
        else etat = true;
        terrain.placementMurs(etat);
    }
}