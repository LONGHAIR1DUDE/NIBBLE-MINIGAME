#include "Terrain.h"
#include <cassert>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <string>
using namespace std;

const char niveau1[22][22] = {
    "#####################",
    "#...................#",
    "#.............b.....#",
    "#...................#",
    "#....b..............#",
    "#...................#",
    "#...c.......b.......#",
    "#...................#",
    "#...................#",
    "#...................#",
    "#.......c...........#",
    "#...................#",
    "#.............b.....#",
    "#...................#",
    "#....b..............#",
    "#................c..#",
    "#...........b.......#",
    "#...................#",
    "#...b...............#",
    "#...................#",
    "#####################"
};

// Constructeur de la classe Terrain
Terrain::Terrain() : dimx(100), dimy(100) {
        recupNiveau("./data/niveau1.txt");
}

Terrain::~Terrain () {}

// Lis le fichier passé en paramètre et stocke les caractères dans 
// le tableau dynamique ter
void Terrain::recupNiveau (const string& nomFichier) {
    ifstream monFlux(nomFichier);
    if (monFlux) {
        string ligne;
        getline(monFlux, ligne);
        dimx = ligne.size();

        monFlux.seekg(0, std::ios::beg);
        char a;
        do {
            monFlux.get(a);
            ter.push_back(a);
        } while (monFlux.get(a)) ;

        dimy = ter.size()/dimx;
        tailleTab = ter.size();

    } else 
        cout << "ERREUR: Impossible d'ouvrir le fichier en lecture !" << endl;
}

// Fonction qui renvoi true si les coordonnées (x,y) passées en 
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
        tabCle[c].x = rand()% dimx;
        tabCle[c].y = rand()% dimy;
        if (posValide(tabCle[c].x, tabCle[c].y)) {
            ter[tabCle[c].y*dimx+tabCle[c].x] = 'c';
        }
    }
}

// Retourne la taille du tableau dynamique ter
int Terrain::getTailleTab() const { return tailleTab; }

// Retourne la valeur de dimx
int Terrain::getDimX () const { return dimx; }

// Retourne la valeur de dimy
int Terrain::getDimY () const { return dimy; }

// Retourne le contenu du tableau dynamique ter 
vector<char> Terrain::getTabTerrain () const { 
    vector<char> copieTerrain;
    for (int y = 0; y < dimy; y++) {
        for (int x = 0; x < dimx; x++) {
            copieTerrain[y*dimx+x] = ter[y*dimx+x];
        }
    }

    return copieTerrain;
}