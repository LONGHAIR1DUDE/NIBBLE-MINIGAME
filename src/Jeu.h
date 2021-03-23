#include "Terrain.h"
#include "Serpent.h"
#include "Portail.h"
#include "Mur.h"
#include "Bonus.h"
#include <vector>
using namespace std;

#ifndef _JEU_H
#define _JEU_H

class Jeu {
private:
    Terrain terrain;
    Serpent serpent;
    vector<Mur> murs;
    vecotr<Portail> Portail;
    vector<Bonus> bonus;

public:
    Terrain& getTerrain() const;
    Serpent& getSerpent() const;
    Mur getMur(int i) const; 
    int getNbMurs() const;
    Portail getPortail(int i) const;
    int getNbPortails() const;
    Bonus getBonus(int i) const;
    int getNbBonus() const;
    bool actionClavier();
    void placementAleatoire();

};

#endif
