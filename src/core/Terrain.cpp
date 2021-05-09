#include "Terrain.h"
#include <cassert>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <string>
#include <time.h>
using namespace std;

Terrain::Terrain() : dimx(100), dimy(100) // Constructeur par défaut de la classe, dimx et dimy prennent la valeur 100
{
    recupNiveau("./data/niveau3.txt"); // on récupère un fichier pour initialiser le niveau  
    posAleaCle(); // on pose les clés aléatoirement dans le niveau
    srand(time(NULL)); // initialisation de la fonction rand
}

Terrain::Terrain(const string &nomFichier) // constructeur par copie de la classe qui prend une chaine de caractère en paramètre 
{
    recupNiveau(nomFichier); // on récupère un fichier pour initialiser le niveau  
    posAleaCle(); // on pose les clés aléatoirement dans le niveau
    srand(time(NULL)); // initialisation de la fonction rand
}

Terrain::~Terrain() {} // destructeur de la classe 

char Terrain::getXY(int x, int y) const // accesseur qui retourne le tableau de caractère ter
{
    assert(x >= 0); // vérification que x est supérieur ou égale à zéro 
    assert(x < dimx); // vérification que x est inférieur à la dimension en x du niveau  
    assert(y >= 0); // vérification que y est supérieur ou égale à zéro 
    assert(y < dimy); // vérification que y est inférieur à la dimension en y du niveau  
    return ter[y * dimx + x]; // retourne le tableau dynamique ter
}

int Terrain::getDimX() const // accesseur qui retourne la valeur de dimx
{
    return dimx;
}

int Terrain::getDimY() const // accesseur qui retourne la valeur de dimy
{
    return dimy;
}

int Terrain::getTailleTerrain() const // accesseur qui retourne la taille du tableau dynamique ter
{
    return tailleTerrain;
}

Point Terrain::getCle(int indice) const // accesseur qui retourne la clé d'indice passé en paramètre 
{
    return tabCle.at(indice);
}

Mur Terrain::getTabMurs(int i) const // accesseur qui retourne le mur d'indice passé en paramètre
{
    return tabMurs[i];
}

int Terrain::getNbCle() const // accesseur qui retourne la taille du tableau tabCle
{
    return tabCle.size();
}

int Terrain::getNbMurs() const // accesseur qui retourn la taille du tableau tabMurs
{
    return tabMurs.size();
}

void Terrain::setXY(const int x, const int y, const char c) // mutateur qui modifie le caractère du tableau aux coordonnées passés en paramètre 
{
    assert(x >= 0); // vérifie que x est supérieur ou égale à 0
    assert(x < dimx); // vérifie que x est inférieur à la dimension en x du niveau   
    assert(y >= 0); // vérifie que y est supérieur ou égale à 0
    assert(y < dimy); // vérifie que y est inférieur à la dimension en y du niveau   
    ter[y * dimx + x] = c; // change la valeur dans le tableau ter 
}
 
bool Terrain::posValide(int x, int y) const // Fonction qui renvoie true si les coordonnées (x,y) passées en paramètres ne correspond pas à un mur false sinon
{
    return ((x >= 0) && (x < dimx) && (y >= 0) && (y < dimy) && ter[y * dimx + x] != '#');
}

void Terrain::recupNiveau(const string &nomFichier) // Lis le fichier passé en paramètre et stocke les caractères dans le tableau dynamique ter
{
    ifstream monFichier(nomFichier); // ouvre le fichier en lecture
    if (monFichier) // si le fichier s'ouvre
    {
        ter.clear(); // on vide le tableau ter 
        string nbCarLigne; 
        getline(monFichier, nbCarLigne); // on stocke la première ligne dans la variable nbCarLigne
        dimx = nbCarLigne.size(); // on récupère la taille de la première ligne

        monFichier.seekg(0, std::ios::beg); // on retourne au début du fichier 
        char a;
        int cpt = 1;
        while (monFichier.get(a)) // tant qu'un caractère du fichier est lu 
        {
            if (cpt % (dimx + 1) != 0) // si se n'est pas le caractère de fin de chaine
            {
                ter.push_back(a); // on stocke le caractère à la fin du tableau 
            }
            cpt++;
        }

        tailleTerrain = ter.size(); // on récupère la taille du tableau ter
        dimy = (tailleTerrain / dimx); // on récupère la dimension en y du niveau 
    }
    else // sinon (le fichier ne s'ouvre pas)
    {
        cout << "ERREUR: Impossible d'ouvrir le fichier en lecture !" << endl;
    }
}

void Terrain::posAleaCle() // Procédure qui place aléatoirement 3 clés dans un niveau
{
    Point cle{0, 0}; // déclaraction d'une variable de type Point 
    for (int i = 0; i < 3; i++) // initialisation du tableau tabCle 
        tabCle.push_back(cle);

    for (int c = 0; c < 3; c++) // boucle for qui affecte des coordonnées à chaque clé du tableau 
    {
        if (c == 0) // si c'est le première élément du tableau tabCle
        {
            do
            {
                tabCle.at(c).x = rand() % dimx; // valeur aléatoire entre 0 et la dimension en x - 1 
                tabCle.at(c).y = rand() % dimy; // valeur aléatoire entre 0 et la dimension en y - 1 
            } while (!posValide(tabCle.at(c).x, tabCle.at(c).y)); // faire ... tant que la position n'est pas valide 
        }

        else // sinon (pas le première élément du tableau tabCle)
            do
            {
                tabCle.at(c).x = rand() % dimx; // valeur aléatoire entre 0 et la dimension en x - 1 
                tabCle.at(c).y = rand() % dimy; // valeur aléatoire entre 0 et la dimension en y - 1 
            } while (!posValide(tabCle.at(c).x, tabCle.at(c).y) || // faire ... tant que la position n'est pas valide ou si une clé est déjà aux coordonnées affectées
                     ((tabCle.at(c).x == tabCle.at(c - 1).x) && (tabCle.at(c).y == tabCle.at(c - 1).y)) ||
                     ((tabCle.at(2).x == tabCle.at(0).x) && (tabCle.at(2).y == tabCle.at(0).y))); 
    }
}

void Terrain::mangeElement(int x, int y) // Procédure qui mais le caractère ' ' aux coordonnées (x,y) passées en paramètre
{
    assert(x >= 0); // vérifie que x est supérieur ou égale à 0
    assert(x < dimx); // vérifie que x est inférieur à la dimension en x du niveau 
    assert(y >= 0); // vérifie que x est supérieur ou égale à 0
    assert(y < dimy); // vérifie que x est inférieur à la dimension en x du niveau 
    ter[y * dimx + x] = ' '; // remplace le caractère du tableau par ' '
}

int Terrain::compteurPiece() // compte le nombre de pièce présente dans le niveau 
{
    char c;
    int cmpt = 0;
    for (int x = 0; x < dimx; x++) // boucle for qui parcoure le terrain en x
    {
        for (int y = 0; y < dimy; y++) // boucle for qui parcoure le terrain en y
        {
            c = getXY(x, y);
            if (c == '.') // si le caractère du tableau ter est '.' on incrémente le compteur 
                cmpt++;
        }
    }

    return cmpt;
}

bool Terrain::emplacementLibre(int x, int y) // vérifie si la case du tableau est libre (libre si la case contient une pièce ou est vide)
{
    return (((x >= 0) && (x < dimx) && (y >= 0) && (y < dimy) && ter[y * dimx + x] == ' ') ||
            ((x >= 0) && (x < dimx) && (y >= 0) && (y < dimy) && ter[y * dimx + x] == '.'));
}

void Terrain::supprimeCle(int indice) // supprime la clé d'indice passé en paramètre 
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

    for (int i = 1; i < dimy - 1; i++)
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
