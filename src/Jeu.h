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
    

public:
    Terrain& getTerrain();
    Mur getMur(int i);
    int getNbMurs();
    
};

#endif