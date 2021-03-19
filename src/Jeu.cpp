#include <iostream>
#include <cstdlib>
#include <cassert>
#include "Jeu.h"
using namespace std;

Jeu::Jeu () : terrain() {
    terrain.mangeBonus()
}

Jeu::~Jeu () {}

Terrain& Jeu::getTerrain () { return terrain; }
    
