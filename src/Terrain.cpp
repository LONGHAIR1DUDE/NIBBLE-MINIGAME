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
            ((tabCle[c].x == tabCle[c-1].x) && (tabCle[c].y == tabCle[c-1].y)));
        ter[tabCle[c].y*dimx+tabCle[c].x] = 'c';
    }
}

// Retourne la taille du tableau dynamique ter
int Terrain::getTailleTerrain() const { return tailleTerrain; }

// Retourne la valeur de dimx
int Terrain::getDimX () const { return dimx; }

// Retourne la valeur de dimy
int Terrain::getDimY () const { return dimy; }

// void Terrain::testRegression () {
//     int x = 20;
//     int y = 14;

//     recupNiveau("./data/niveauTestReg.txt");
//     assert(posValide(x,y));
//     char tampon1; 
//     char tampon2; 

//     for (int y = 0; y < dimy; y++) {
//         for (int x = 0; x < dimx; x++) {
//             tampon1 = ter[y*dimx+x];
//             tampon2 = getXY(x,y);
//             assert(tampon1 == tampon2);
//         }
//     }
    
//     mangeBonus(x,y);
//     assert(getXY(x,y) == ' ');

//     posAleaCle();
//     assert(sizeof(tabCle == 3));
//     assert(getTailleTerrain() == ter.size());

//     cout<<"assert ended successfully ."<<endl;
// }