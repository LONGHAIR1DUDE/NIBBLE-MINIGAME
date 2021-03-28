#ifndef _TXTFENETRE_H
#define _TXTFENETRE_H
#include "../core/Point.h"

class TxtFenetre {
private:
    int dimx, dimy;
    char* fenetre;
public:
    TxtFenetre(int dx, int dy);

    void effacer(char c = ' ');
    void ecrire(int x, int y, char c);
    void ecrire(int x, int y, char* c);
    void dessiner(int x = 0, int y = 0);
    void pause();
    char getCh();
    char getCarFenetre(int x, int y);
};

Point getDimTerminale();
void termClear();

#endif