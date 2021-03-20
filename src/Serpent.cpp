#include "Serpent.h"
#include <cassert>
using namespace std;

Serpent::Serpent (const int posX, const int posY, const Terrain& t) {
    if (t.posValide(posX, posY)) {
        corps[0].x=posX;
        corps[0].y=posY;
    }
}

void Serpent::gauche (const Terrain& t) {
    Point temp1,temp2;
    int tailleSerp = corps.size();
    temp1.x=corps[0].x;
    temp1.y=corps[0].y;
    if(t.posValide(temp1.x-1, temp1.y)){
        corps[0].x--;
        for (int i = 1; i < tailleSerp; i++) {
            temp2.x=corps[i].x;
            temp2.y=corps[i].y;
            corps[i].x=temp1.x;
            corps[i].y=temp1.y;
            temp1.x=temp2.x;
            temp1.y=temp2.y;
        }
    }
}
void Serpent::droite (const Terrain& t) {
    Point temp1,temp2;
    int tailleSerp = corps.size();
    temp1.x=corps[0].x;
    temp1.y=corps[0].y;
    if(t.posValide(temp1.x+1, temp1.y)){
        corps[0].x++;
        for (int i = 1; i < tailleSerp; i++) {
            temp2.x=corps[i].x;
            temp2.y=corps[i].y;
            corps[i].x=temp1.x;
            corps[i].y=temp1.y;
            temp1.x=temp2.x;
            temp1.y=temp2.y;
        }
    }
}

void Serpent::haut (const Terrain& t) {
    Point temp1,temp2;
    int tailleSerp = corps.size();
    temp1.x=corps[0].x;
    temp1.y=corps[0].y;
    if(t.posValide(temp1.x, temp1.y+1)){
        corps[0].y++;
        for (int i = 1; i < tailleSerp; i++) {
            temp2.x=corps[i].x;
            temp2.y=corps[i].y;
            corps[i].x=temp1.x;
            corps[i].y=temp1.y;
            temp1.x=temp2.x;
            temp1.y=temp2.y;
        }
    }
}
void Serpent::bas (const Terrain& t) {
    Point temp1,temp2;
    int tailleSerp = corps.size();
    temp1.x=corps[0].x;
    temp1.y=corps[0].y;
    if(t.posValide(temp1.x, temp1.y-1)){
        corps[0].y--;
        for (int i = 1; i < tailleSerp; i++) {
            temp2.x=corps[i].x;
            temp2.y=corps[i].y;
            corps[i].x=temp1.x;
            corps[i].y=temp1.y;
            temp1.x=temp2.x;
            temp1.y=temp2.y;
        }
    }
}

Point Serpent::getCorps (const int i) const {
    return corps[i];
}

Point Serpent::getTete () const {
    return corps[0];
}

void Serpent::setCorps (const int i, const int x, const int y) {
    corps[i].x=x;
    corps[i].y=y;
}

void Serpent::setTete (const int x, const int y) {
    corps[0].x=x;
    corps[0].y=y;
}

void Serpent::testRegression () {
    const Terrain t;
    Serpent serp(20, 20, t);
    serp.corps[1].x = serp.corps[0].x+1;
    serp.corps[1].y = serp.corps[0].y;
    int x = serp.corps[0].x;
    int y = serp.corps[0].y;
    
    gauche(t);
    assert(serp.corps[0].x == x-1);
    assert(serp.corps[0].y == y);
    assert(serp.corps[1].x == x);
    assert(serp.corps[1].y == y);

    haut(t);
    assert(serp.corps[0].x == x-1);
    assert(serp.corps[0].y == y+1);
    assert(serp.corps[1].x == x-1);
    assert(serp.corps[1].y == y);

    serp.corps[1].x = serp.corps[0].x-1;
    serp.corps[1].y = serp.corps[0].y;
    
    droite(t);
    assert(serp.corps[0].x == x);
    assert(serp.corps[0].y == y+1);
    assert(serp.corps[1].x == x-1);
    assert(serp.corps[1].y == y+1);

    bas(t);
    assert(serp.corps[0].x == x);
    assert(serp.corps[0].y == y);
    assert(serp.corps[1].x == x);
    assert(serp.corps[1].y == y+1);

    Point val = getCorps(0);
    assert(val.x == serp.corps[0].x);
    assert(val.y == serp.corps[0].y);

    val = getTete();
    assert(val.x == serp.corps[0].x);
    assert(val.y == serp.corps[0].y);

    setCorps(1, 21, 20);
    assert(getCorps(1).x == 21);
    assert(getCorps(1).y == 20);

    setTete(19, 23);
    assert(getTete().x == 19);
    assert(getTete().y == 23);
    cout<<"assert ended successfully ."<<endl;
}

