#include "Terrain.h"
#include "Serpent.h"
#include "Portail.h"
#include "Point.h"
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
    vector<Mur> tabMurs;
    vector<Portail> tabPortail;
    vector<Bonus> tabBonus;

public:
    Jeu();
    ~Jeu();

    Terrain getTerrain() const;
    Serpent getSerpent() const;
    Mur getMur(int i) const; 
    int getNbMurs() const;
    Portail getPortail(int i) const;
    int getNbPortails() const;
    Bonus getBonus(int i) const;
    int getNbBonus() const;
    bool actionClavier(const char touche);
    void placementAleatoire();
    void SerpentBouge(bool stop);
    void actionSurSerpent();
    void actionPortail();

};

#endif
