#include <iostream>
#include "Terrain.h"
#include "Serpent.h"
#include "Bonus.h"
#include "Point.h"
#include "Rect.h"
#include "Mur.h"
#include "Portail.h"
#include "Jeu.h"

using namespace std;

int main()
{
    Terrain ter;
    // Bonus bonus;
    // Point p1(3, 5);
    // Point p2(6, 2);
    // Portail port(p1, p2);

    bool mouv = true;
    Serpent serp(2, 9, 4, ter, mouv);
    serp.testRegression();
    ter.testRegression();
    // bonus.testRegression();
    // port.testRegression();

    return 0;
}