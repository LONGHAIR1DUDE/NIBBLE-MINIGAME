#include "Terrain.h"
#include <cassert>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <string>
#include <time.h>
using namespace std;

// Constructeur de la classe Terrain
Terrain::Terrain() : dimx(100), dimy(100)
{
    recupNiveau("./data/niveau2.txt");
    posAleaCle();
    srand(time(NULL));
}

Terrain::Terrain(const string &nomFichier)
{
    recupNiveau(nomFichier);
    posAleaCle();
    srand(time(NULL));
}

Terrain::~Terrain() {}

// Fonction qui retourne le tableau de caractère ter
char Terrain::getXY(int x, int y) const
{
    assert(x >= 0);
    assert(x < dimx);
    assert(y >= 0);
    assert(y < dimy);
    return ter[y * dimx + x];
}

// Retourne la valeur de dimx
int Terrain::getDimX() const
{
    return dimx;
}

// Retourne la valeur de dimy
int Terrain::getDimY() const
{
    return dimy;
}

// Retourne la taille du tableau dynamique ter
int Terrain::getTailleTerrain() const
{
    return tailleTerrain;
}

Point Terrain::getCle(int indice) const
{
    return tabCle.at(indice);
}

Mur Terrain::getTabMurs(int i) const
{
    return tabMurs[i];
}

int Terrain::getTailleTabMurs() const
{
    return tabMurs.size();
}

int Terrain::getNbCle() const
{
    return tabCle.size();
}

int Terrain::getNbMurs() const
{
    return tabMurs.size();
}

void Terrain::setXY(const int x, const int y, const char c)
{
    assert(x >= 0);
    assert(x < dimx);
    assert(y >= 0);
    assert(y < dimy);
    // assert(posValide(x, y));
    // assert(emplacementLibre(x, y));
    ter[y * dimx + x] = c;
}

// Fonction qui renvoie true si les coordonnées (x,y) passées en
// paramètres ce trouve dans le niveau false sinon
bool Terrain::posValide(int x, int y) const
{
    return ((x >= 0) && (x < dimx) && (y >= 0) && (y < dimy) && ter[y * dimx + x] != '#');
}

// Lis le fichier passé en paramètre et stocke les caractères dans
// le tableau dynamique ter
void Terrain::recupNiveau(const string &nomFichier)
{
    ifstream monFichier(nomFichier);
    if (monFichier)
    {
        ter.clear();
        string nbCarLigne;
        getline(monFichier, nbCarLigne);
        dimx = nbCarLigne.size();

        monFichier.seekg(0, std::ios::beg);
        char a;
        int cpt = 1;
        while (monFichier.get(a))
        {
            if (cpt % (dimx + 1) != 0)
            {
                ter.push_back(a);
            }
            cpt++;
        }

        tailleTerrain = ter.size();
        dimy = (tailleTerrain / dimx);
    }
    else
    {
        cout << "ERREUR: Impossible d'ouvrir le fichier en lecture !" << endl;
    }
}

// Procédure qui place aléatoirement 3 clés dans un niveau
void Terrain::posAleaCle()
{
    Point cle{0, 0};
    for (int i = 0; i < 3; i++)
        tabCle.push_back(cle);

    for (int c = 0; c < 3; c++)
    {
        if (c == 0)
        {
            do
            {
                tabCle.at(c).x = rand() % dimx;
                tabCle.at(c).y = rand() % dimy;
            } while (!posValide(tabCle.at(c).x, tabCle.at(c).y));
        }

        else
            do
            {
                tabCle.at(c).x = rand() % dimx;
                tabCle.at(c).y = rand() % dimy;
            } while (!posValide(tabCle.at(c).x, tabCle.at(c).y) ||
                     ((tabCle.at(c).x == tabCle.at(c - 1).x) && (tabCle.at(c).y == tabCle.at(c - 1).y)) ||
                     ((tabCle.at(2).x == tabCle.at(0).x) && (tabCle.at(2).y == tabCle.at(0).y)));
    }
}

// Procédure qui mais le caractère ' ' aux coordonnées (x,y)
// passées en paramètre
void Terrain::mangeElement(int x, int y)
{
    assert(x >= 0);
    assert(x < dimx);
    assert(y >= 0);
    assert(y < dimy);
    ter[y * dimx + x] = ' ';
}

int Terrain::compteurPiece()
{
    char c;
    int cmpt = 0;
    for (int x = 0; x < dimx; x++)
    {
        for (int y = 0; y < dimy; y++)
        {
            c = getXY(x, y);
            if (c == '.')
                cmpt++;
        }
    }

    return cmpt;
}

bool Terrain::emplacementLibre(int x, int y)
{
    return (((x >= 0) && (x < dimx) && (y >= 0) && (y < dimy) && ter[y * dimx + x] == ' ') ||
            ((x >= 0) && (x < dimx) && (y >= 0) && (y < dimy) && ter[y * dimx + x] == '.'));
}

void Terrain::supprimeCle(int indice)
{
    if (indice == 0)
        tabCle.erase(tabCle.begin());
    else if (indice == 2)
        tabCle.erase(tabCle.begin() + 2);
    else
        tabCle.erase(tabCle.begin() + 1);
}

void Terrain::testRegression()
{

    int pos;
    int compteur = 0;

    for (int i = 0; i < dimx; i++)
    {
        assert(ter[i] == '#');
    }
    for (int i = 1; i < 17; i++)
    {
        for (int j = 1; j < dimx - 1; j++)
        {
            assert(ter[i * dimx + j] == '.');
        }
    }
    for (int i = (dimy - 1) * dimx; i < (dimy - 1) * dimx + dimx; i++)
    {
        assert(ter[i] == '#');
    }

    for (int i = 0; i < dimx; i++)
    {
        pos = posValide(i, 0);
        assert(pos == false);
    }
    for (int i = 1; i < dimy - 1; i++)
    {
        for (int j = 1; j < dimx - 1; j++)
        {
            pos = posValide(j, i);
            assert(pos == true);
        }
    }

    posAleaCle();
    for (int i = 0; i < 3; i++)
    {
        if (ter[tabCle[i].y * dimx + tabCle[i].x] == 'c')
            compteur++;
    }
    assert(compteur == 3);

    for (int i = 1; i < dimy - 1; i++)
    {
        for (int j = 1; j < dimx - 1; j++)
        {
            mangeElement(j, i);
            assert(ter[i * dimx + j] == ' ');
        }
    }
    cout << "Class Terrain: assert ended successfully." << endl;
}
