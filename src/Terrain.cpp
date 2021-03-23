#include "Terrain.h"
#include <cassert>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <string>
#include <time.h>
using namespace std;

// Constructeur de la classe Terrain
Terrain::Terrain() : dimx(100), dimy(100) {
         recupNiveau("./data/niveau1.txt");
}

Terrain::Terrain(const string& namefile) {
    recupNiveau(namefile);
}

Terrain::~Terrain () {}

// Lis le fichier passé en paramètre et stocke les caractères dans
// le tableau dynamique ter
void Terrain::recupNiveau (const string& nomFichier) {
    ifstream monFichier(nomFichier);
    if (monFichier) {
        ter.clear();
        string nbCarLigne;
        getline(monFichier, nbCarLigne);
        dimx = nbCarLigne.size();

        monFichier.seekg(0, std::ios::beg);
        char a;
        int cpt = 1;
        while (monFichier.get(a)) {
            if (cpt % (dimx+1) != 0) {
                ter.push_back(a);
            }
            cpt++;
        }

        tailleTerrain = ter.size();
        dimy = (tailleTerrain/dimx);

    } else {
        cout << "ERREUR: Impossible d'ouvrir le fichier en lecture !" << endl;
    }
}

// Fonction qui renvoie true si les coordonnées (x,y) passées en
// paramètres ce trouve dans le niveau false sinon
bool Terrain::posValide(int x, int y) const {
    return ((x>=0) && (x<dimx) && (y>=0) && (y<dimy) && ter[y*dimx+x] != '#');
}

// Fonction qui retourne le tableau de caractère ter
char Terrain::getXY(int x, int y) const {
    assert(x>=0);
    assert(x<dimx);
    assert(y>=0);
    assert(y<dimy);
    return ter[y*dimx+x];
}

// Procédure qui mais le caractère ' ' aux coordonnées (x,y)
// passées en paramètre
void Terrain::mangeBonus(int x, int y) {
    assert(x>=0);
    assert(x<dimx);
    assert(y>=0);
    assert(y<dimy);
    ter[y*dimx+x] = ' ';
}

// Procédure qui place aléatoirement 3 clés dans un niveau
void Terrain::posAleaCle () {
    srand(time(NULL));
    for (int c = 0; c < 3; c++) {
        do {
            tabCle[c].x = rand()% dimx;
            tabCle[c].y = rand()% dimy;
        } while (!posValide(tabCle[c].x, tabCle[c].y) || 
             ((tabCle[c].x == tabCle[c-1].x) && (tabCle[c].y == tabCle[c-1].y)) || 
             ((tabCle[2].x == tabCle[0].x) && (tabCle[2].y == tabCle[0].y)));
        ter[tabCle[c].y*dimx+tabCle[c].x] = 'c';
    }
}

// Retourne la taille du tableau dynamique ter
int Terrain::getTailleTerrain() const { return tailleTerrain; }

// Retourne la valeur de dimx
int Terrain::getDimX () const { return dimx; }

// Retourne la valeur de dimy
int Terrain::getDimY () const { return dimy; }

void testRegression(){
    int pos;
    int compteur=0;
    for(int i=0;i<21;i++){
        assert(ter[i]=='#');
    }
    for(int i=1;i<17;i++){
        for(int j=1;j<20;j++){
            assert(ter[i*dimx+j]=='.');
        }
    }
    for(int i=18*dimx;i<18*dimx+21;i++){
        assert(ter[i]=='#');
    }
    for(int i=0;i<21;i++){
        pos=posValide(i,0));
        assert(pos=false);
    }
    for(int i=1;i<17;i++){
        for(int j=1;j<20;j++){
            pos=posValide(j,i));
            assert(pos=true);
        }
    }
    posAleaCle();
    for(int i=0;i<3;i++){
    if(assert(ter[tabCle[i].y*dimx+tabCle[i].x]='c'))
        compteur++;
    }
    assert(compteur==3);
    for(int i=1;i<17;i++){
        for(int j=1;j<20;j++){
            if(ter(i*dimx+j)==c){
                mangeBonus(j,i);
                assert(ter[i*dimx+j]==' ');
            }
        }
    }
}

