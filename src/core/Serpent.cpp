#include "Serpent.h"
#include <cassert>
using namespace std;

Serpent::Serpent (int tailleSerp, int posX, int posY, Terrain& t, bool mouvement = false) {
    if (t.posValide(posX, posY)) {
        Point p;
        p.x = posX;
        p.y = posY;
        corps.push_back(p);
        mouvementInverse = mouvement;
        directionSerpent.x = 0;
        directionSerpent.y = -1;

        for (int i = 1; i < tailleSerp; i++) {
            p.x = getCorps(i-1).x;
            p.y = getCorps(i-1).y+1;
            corps.push_back(p);
        }
    }
}

void Serpent::gauche (const Terrain& t) {
    Point temp1,temp2;
    int tailleSerp = corps.size();
    temp1.x=corps[0].x;
    temp1.y=corps[0].y;
    if (directionSerpent.x != 1) {
        if(t.posValide(temp1.x-1, temp1.y)){
            corps[0].x--;
            directionSerpent.x = -1;
            directionSerpent.y = 0;
            for (int i = 1; i < tailleSerp; i++) {
                temp2.x=corps[i].x;
                temp2.y=corps[i].y;
                corps[i].x=temp1.x;
                corps[i].y=temp1.y;
                temp1.x=temp2.x;
                temp1.y=temp2.y;
                if (i == tailleSerp-1) {
                    boutSerpent.x = temp1.x;
                    boutSerpent.y = temp2.y;
                }
            }
        }
    }
    
}
void Serpent::droite (const Terrain& t) {
    Point temp1,temp2;
    int tailleSerp = corps.size();
    temp1.x=corps[0].x;
    temp1.y=corps[0].y;
    if (directionSerpent.x != -1) {
        if(t.posValide(temp1.x+1, temp1.y)){
            corps[0].x++;
            directionSerpent.x = 1;
            directionSerpent.y = 0;
            for (int i = 1; i < tailleSerp; i++) {
                temp2.x=corps[i].x;
                temp2.y=corps[i].y;
                corps[i].x=temp1.x;
                corps[i].y=temp1.y;
                temp1.x=temp2.x;
                temp1.y=temp2.y;
                if (i == tailleSerp-1) {
                    boutSerpent.x = temp1.x;
                    boutSerpent.y = temp2.y;
                }
            }
        }
    }
}

void Serpent::haut (const Terrain& t) {
    Point temp1,temp2;
    int tailleSerp = corps.size();
    temp1.x=corps[0].x;
    temp1.y=corps[0].y;
    if (directionSerpent.y != 1) {
         if(t.posValide(temp1.x, temp1.y-1)){
            corps[0].y--;
            directionSerpent.x = 0;
            directionSerpent.y = -1;
            for (int i = 1; i < tailleSerp; i++) {
                temp2.x=corps[i].x;
                temp2.y=corps[i].y;
                corps[i].x=temp1.x;
                corps[i].y=temp1.y;
                temp1.x=temp2.x;
                temp1.y=temp2.y;
                if (i == tailleSerp-1) {
                    boutSerpent.x = temp1.x;
                    boutSerpent.y = temp2.y;
                }
            }
        }
    }
}
void Serpent::bas (const Terrain& t) {
    Point temp1,temp2;
    int tailleSerp = corps.size();
    temp1.x=corps[0].x;
    temp1.y=corps[0].y;
    if (directionSerpent.y != -1) {
        if(t.posValide(temp1.x, temp1.y+1)){
            corps[0].y++;
            directionSerpent.x = 0;
            directionSerpent.y = 1;
            for (int i = 1; i < tailleSerp; i++) {
                temp2.x=corps[i].x;
                temp2.y=corps[i].y;
                corps[i].x=temp1.x;
                corps[i].y=temp1.y;
                temp1.x=temp2.x;
                temp1.y=temp2.y;
                if (i == tailleSerp-1) {
                    boutSerpent.x = temp1.x;
                    boutSerpent.y = temp2.y;
                }
            }
        }
    }
}

//Fonction à terminer, ajouter détection de position libre
void Serpent::allongeCorps (const Terrain& t){
    corps.push_back(boutSerpent);
}

void Serpent::retrecirCorps(){
    if (getTailleSerpent() < 3) {} 
    else corps.pop_back();
}

Point Serpent::getCorps (const int i) const {
    return corps[i];
}

Point Serpent::getTete () const {
    return corps[0];
}

bool Serpent::getMouv(){
    return mouvementInverse;
}

Point Serpent::getDirection() const {
    return directionSerpent;
}

int Serpent::getTailleSerpent () const {
    return corps.size();
}

void Serpent::setCorps (const int i, const int x, const int y) {
    corps[i].x=x;
    corps[i].y=y;
}

void Serpent::setTete (const int x, const int y) {
    corps[0].x = x;
    corps[0].y = y;
}

void Serpent::setMouv(bool mouv){
    mouvementInverse=mouv;
}

/* PAS ENCORE FONCTIONNEL */
void Serpent::setDirection (int x, int y, const Terrain& t) {
    if (getDirection().x == -x || getDirection().y == -y) {}
    else {
        directionSerpent.x = x;
        directionSerpent.y = y;
    }
    // else if ((directionSerpent.x == 1) || (directionSerpent.x == -1)) {
    //     if (y == 1) {
    //         if (t.posValide(corps[0].x, corps[0].y+1)) {
    //             directionSerpent.x = x;
    //             directionSerpent.y = y;
    //         } else {}
    //     } else if (y == -1) {
    //         if (t.posValide(corps[0].x, corps[0].y-1)) {
    //             directionSerpent.x = x;
    //             directionSerpent.y = y;
    //         } else {}
    //     }
    // } else if ((directionSerpent.x == 1) || (directionSerpent.x == -1)) {
    //     if (x == 1) {
    //         if (t.posValide(corps[0].x+1, corps[0].y)) {
    //             directionSerpent.x = x;
    //             directionSerpent.y = y;
    //         } else {}
    //     } else if (x == -1) {
    //         if (t.posValide(corps[0].x-1, corps[0].y)) {
    //             directionSerpent.x = x;
    //             directionSerpent.y = y;
    //         } else {}
    //     }
    // }    
}

bool Serpent::caseContientSerpent (int x, int y) {
    return ((x == corps.at(y*getTailleSerpent()+x).x) && (y == corps.at(y*getTailleSerpent()+x).y));
}

void Serpent::testRegression () {
    const Terrain t;
    Point p1(10, 4);
    corps.push_back(p1);
    int x = corps[0].x;
    int y = corps[0].y;

    gauche(t);
    assert(corps[0].x == x-1);
    assert(corps[0].y == y);
    assert(corps[1].x == x);
    assert(corps[1].y == y);

    haut(t);
    assert(corps[0].x == x-1);
    assert(corps[0].y == y+1);
    assert(corps[1].x == x-1);
    assert(corps[1].y == y);

    Point p2(8, 4);
    corps.pop_back();
    corps.push_back(p2);

    droite(t);
    assert(corps[0].x == x);
    assert(corps[0].y == y+1);
    assert(corps[1].x == x-1);
    assert(corps[1].y == y+1);

    bas(t);
    assert(corps[0].x == x);
    assert(corps[0].y == y);
    assert(corps[1].x == x);
    assert(corps[1].y == y+1);

    Point val = getCorps(0);
    assert(val.x == corps[0].x);
    assert(val.y == corps[0].y);

    val = getTete();
    assert(val.x == corps[0].x);
    assert(val.y == corps[0].y);

    setCorps(1, 21, 20);
    assert(getCorps(1).x == 21);
    assert(getCorps(1).y == 20);

    setTete(19, 23);
    assert(getTete().x == 19);
    assert(getTete().y == 23);
    cout<<"Class Serpent: assert ended successfully."<<endl;
}


