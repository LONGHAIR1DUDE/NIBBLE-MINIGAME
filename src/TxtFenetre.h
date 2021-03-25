#ifndef _TXTFENETRE_H
#define _TXTFENETRE_H

class TxtFenetre {
private:
    int dimx, dimy;
    char* fenetre;
public:
    TxtFenetre(int dx, int dy);

    void effacer();
    void ecrire(int x, int y, char c);
    void ecrire(int x, int y, char* c);
    void dessiner(int x, int y);
    void pause();
    char getCh();
};

#endif