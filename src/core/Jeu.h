#include "Terrain.h"
#include "Serpent.h"
#include "Point.h"
#include "Mur.h"
#include "Bonus.h"
#include "Rect.h"
#include "../txt/TxtFenetre.h"
#include <vector>
using namespace std;

#ifndef _JEU_H
#define _JEU_H

class Jeu
{
private:
    Terrain terrain;
    Serpent serpent;
    vector<Portail> tabPortail;
    vector<Bonus> tabBonus;
    vector<Mur> tabMurs;
    int score;
    int meilleurScore;
    int multiplicateur;

public:
    Jeu(const string &namefile);

    ~Jeu();

    const Terrain &getTerrain() const;
    const Serpent &getSerpent() const;
    int getNbMurs() const;
    Mur getMur(int i) const;
    Portail getPortail(int i) const;
    int getNbPortails() const;
    Bonus getBonus(int i) const;
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
    bool caseContientSerpent(int x, int y);
    void placementMurs(bool etat);
    void actionInterrupteur(bool &etat);
    void tabMursTerrain();
    void afficheTabMurs();
};

#endif
