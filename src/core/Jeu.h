#include "Terrain.h"
#include "Serpent.h"
#include "Portail.h"
#include "Point.h"
#include "Mur.h"
#include "Bonus.h"
#include "../txt/TxtFenetre.h"
#include <vector>
using namespace std;

#ifndef _JEU_H
#define _JEU_H

class Jeu {
private:
    Terrain terrain;
    Serpent serpent;
    vector<Portail> tabPortail;
    vector<Bonus> tabBonus;
    int score;
    int *p_score;
    int meilleurScore;

public:
    Jeu(const string& namefile);
    
    ~Jeu();

    const Terrain& getTerrain() const;
    const Serpent& getSerpent() const;
    Mur getMur(int i); 
    int getNbMurs() const;
    Portail& getPortail(int i);
    int getNbPortails() const;
    Bonus& getBonus(int i);
    int getNbBonus() const;
    int getScore();
    int getMeilleurScore();
    void setScore(int val);
    int stockerMeilleurScore();
    bool actionClavier(const char touche);
    void placementAleatoireBonus();
    bool SerpentBouge();
    void actionSurSerpent();
    void actionPortail();
    void actionInterrupteur(bool& etat);
};

#endif
