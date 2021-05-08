#include <iostream>
#include <cstdlib>
#include <cassert>
#include "Jeu.h"
#include <ctime>
#include <chrono>
#include <thread>
#include <fstream>
using namespace std;

Jeu::Jeu(const string &nomFichier) : serpent(3, terrain.getDimX() / 2, 
                    terrain.getDimY() / 2, terrain, true), score(0)
{
    terrain.recupNiveau(nomFichier);
    terrain.mangeElement(serpent.getTete().x, serpent.getTete().y);
    tabMursTerrain();
    placementMurs(true);
    srand(time(NULL));
    Point a{1, 1};
    Point b{(terrain.getDimX() - 2), (terrain.getDimY() - 2)};
    Portail p(a, b);
    tabPortail.push_back(p);
    multiplicateur = 1;
}

Jeu::~Jeu() {}

const Terrain &Jeu::getTerrain() const { return terrain; }

const Serpent &Jeu::getSerpent() const { return serpent; }

int Jeu::getNbMurs() const
{
    return tabMurs.size();
}

Mur Jeu::getMur(int i) const
{
    return tabMurs[i];
}

Portail Jeu::getPortail(int i) const
{
    return tabPortail[i];
}

int Jeu::getNbPortails() const
{
    return tabPortail.size();
}

Bonus Jeu::getBonus(int i) const
{
    return tabBonus[i];
}

int Jeu::getNbBonus() const
{
    return tabBonus.size();
}

int Jeu::getScore()
{
    return score;
}

int Jeu::getMeilleurScore()
{
    return meilleurScore;
}

void Jeu::setScore(int val)
{
    score += val*multiplicateur;
}

int Jeu::stockerMeilleurScore()
{
    ifstream monMeilleurScoreL("./data/bestScore.txt");
    if (monMeilleurScoreL)
    {
        monMeilleurScoreL >> meilleurScore;
        monMeilleurScoreL.close();
        if (meilleurScore < score)
        {
            ofstream monMeilleurScoreE("./data/bestScore.txt");
            if (monMeilleurScoreE)
            {
                monMeilleurScoreE << score;
                monMeilleurScoreE.close();
                meilleurScore = score;
                return score;
            }
            else
            {
                cout << "ERREUR: Impossible d'ouvrir le fichier en ecriture !" << endl;
            }
        }
        else
        {
            return meilleurScore;
        }
    }
    else
        cout << "ERREUR: Impossible d'ouvrir le fichier en lecture !" << endl;
    return 0;
}

bool Jeu::actionClavier(const char touche)
{
    switch (touche)
    {
    case 'q':
        if (!serpent.getMouv())
        {
            serpent.setDirection(1, 0, terrain);
        }
        else
        {
            serpent.setDirection(-1, 0, terrain);
        }
        break;

    case 'd':
        if (!serpent.getMouv())
        {
            serpent.setDirection(-1, 0, terrain);
        }
        else
        {
            serpent.setDirection(1, 0, terrain);
        }
        break;

    case 'z':
        if (!serpent.getMouv())
        {
            serpent.setDirection(0, 1, terrain);
        }
        else
        {
            serpent.setDirection(0, -1, terrain);
        }
        break;

    case 's':
        if (!serpent.getMouv())
        {
            serpent.setDirection(0, -1, terrain);
        }
        else
        {
            serpent.setDirection(0, 1, terrain);
        }
        break;
    }
    if (terrain.getXY(serpent.getTete().x, serpent.getTete().y) == '.')
    {
        terrain.mangeElement(serpent.getTete().x, serpent.getTete().y);
        return true;
    }
    return false;
}

void Jeu::placementAleatoireBonus()
{
    int x, y, a;
    int dimx = terrain.getDimX();
    int dimy = terrain.getDimY();

    // boucle for qui créé et stocke 3 bonus dans le tableau tabBonus
    for (int i = 0; i < 3; i++)
    {
        a = rand() % 3;
        if (i == 0)
        {
            do
            {
                x = rand() % dimx;
                y = rand() % dimy;
            } while (!terrain.posValide(x, y));
        }
        else
        {
            do
            {
                x = rand() % dimx;
                y = rand() % dimy;
            } while (!terrain.posValide(x, y) || ((tabBonus[i - 1].getX() == x) && (tabBonus[i - 1].getY() == y)));
        }
        Bonus b(a, x, y);
        tabBonus.push_back(b);
        terrain.setXY(tabBonus[i].getX(), tabBonus[i].getY(), 'b');
    }
}

bool Jeu::SerpentBouge()
{

    Point dir = serpent.getDirection();
    int x = serpent.getTete().x;
    int y = serpent.getTete().y;

    for (int i = 1; i < serpent.getTailleSerpent(); i++)
    {
        if ((serpent.getCorps(i).x == x) && (serpent.getCorps(i).y == y))
            return false;
    }

    if (dir.x == -1)
    {
        serpent.gauche(terrain);
    }

    if (dir.x == 1)
    {
        serpent.droite(terrain);
    }

    if (dir.y == -1)
    {
        serpent.haut(terrain);
    }

    if (dir.y == 1)
    {
        serpent.bas(terrain);
    }

    return true;
}

void Jeu::actionSurSerpent()
{
    int x = serpent.getTete().x;
    int y = serpent.getTete().y;
    int cpt = terrain.compteurPiece();
    int dimx = terrain.getDimX();
    int dimy = terrain.getDimY();
    char element = terrain.getXY(x, y);
    int nbCle = terrain.getNbCle();
    int tailleTabBonus = tabBonus.size();

    for (int i = 0; i < nbCle; i++)
    {
        terrain.setXY(terrain.getCle(i).x, terrain.getCle(i).y, 'c');
    }

    if (element == '.')
    {
        serpent.allongeCorps(terrain);
        terrain.mangeElement(x, y);
        setScore(100);

        cpt--;
    }

    if (element == 'b')
    {
        terrain.mangeElement(x, y);
        int indice, action, coordx, coordy;
        for (int i = 0; i < tailleTabBonus; i++)
        {
            if (x == tabBonus[i].getX() && y == tabBonus[i].getY())
            {
                indice = i;
                break;
            }
        }

        tabBonus[indice].actionBonus(serpent, terrain);
        if (tabBonus[indice].getAction() == 1) {
            setScore(500);
            multiplicateur = 1;
        }
        else if (tabBonus[indice].getAction() == 2)
            multiplicateur = 2;
        else multiplicateur = 0.5;
        do
        {
            action = rand() % 3;
            coordx = rand() % dimx;
            coordy = rand() % dimy;
        } while (!terrain.posValide(coordx, coordy) || !terrain.emplacementLibre(coordx, coordy));
        tabBonus[indice].setBonus(action, coordx, coordy);
    }

    if (cpt < 30)
    {
        do
        {
            x = rand() % dimx;
            y = rand() % dimy;
        } while (!terrain.posValide(x, y) || !terrain.emplacementLibre(x, y));
        terrain.setXY(x, y, '.');
    }

    if (element == 'c')
    {
        terrain.mangeElement(x, y);
        for (int i = 0; i < 3; i++)
            if ((terrain.getCle(i).x == x) && (terrain.getCle(i).y == y))
            {
                terrain.supprimeCle(i);
                break;
            }
    }
}

void Jeu::actionPortail()
{
    int px1 = tabPortail[0].getPortail1().x;
    int py1 = tabPortail[0].getPortail1().y;

    int px2 = tabPortail[0].getPortail2().x;
    int py2 = tabPortail[0].getPortail2().y;
    if ((serpent.getTete().x == px1) && (serpent.getTete().y == py1))
    {
        serpent.setTete(px2, py2);
    }

    else if ((serpent.getTete().x == px2) && (serpent.getTete().y == py2))
    {
        serpent.setTete(px1, py1);
    }
}

bool Jeu::caseContientSerpent(int x, int y)
{
    for (int i = 0; i < serpent.getTailleSerpent(); i++)
        if ((x == serpent.getCorps(i).x) && (y == serpent.getCorps(i).y))
            return true;
    return false;
}

void Jeu::tabMursTerrain()
{
    vector<Rect> posMurTerrain;
    vector<Rect> murs;
    Rect tampon;
    int dimx = terrain.getDimX();
    int dimy = terrain.getDimY();

    // boucle for qui stocke dans le tableau posMurTerrain toute les
    // positions des caractères '#' excepté ceux des bordures du niveau
    for (int y = 1; y < dimy - 1; y++)
    {
        for (int x = 1; x < dimx - 1; x++)
        {
            if (terrain.getXY(x, y) == '#')
            {
                tampon.x = x;
                tampon.y = y;
                tampon.w = 1;
                tampon.h = 1;
                posMurTerrain.push_back(tampon);
            }
        }
    }

    int taillePosMur = posMurTerrain.size();
    int tailleMurs;
    if (taillePosMur != 0)
    {
        // insert le première élément du tableau posMursTerrain
        // dans le tableau murs
        murs.push_back(posMurTerrain[0]);
        tailleMurs = 1;
        bool valSortie;

        // boucle for qui stocke les coordonnées du premières élément
        // de chaque mur ainsi que leur dimension
        for (int i = 1; i < taillePosMur; i++)
        {
            tailleMurs = murs.size();
            for (int j = 0; j < tailleMurs; j++)
            {
                valSortie = true;

                if ((posMurTerrain.at(i).x == murs.at(j).x + murs.at(j).w) &&
                    (posMurTerrain.at(i).y == murs.at(j).y))
                {
                    murs.at(j).w++;
                    break;
                }

                else if ((posMurTerrain.at(i).y == murs.at(j).y + murs.at(j).h) &&
                         (posMurTerrain.at(i).x == murs.at(j).x))
                {
                    murs.at(j).h++;
                    break;
                }

                else
                    valSortie = false;
            }
            if (valSortie == false)
                murs.push_back(posMurTerrain.at(i));
        }

        // boucle for qui stocke les éléments de murs dans le tableau
        // de type Mur, tabMurs
        for (int i = 0; i < tailleMurs; i++)
        {
            if (murs.at(i).w > murs.at(i).h)
            {
                if (terrain.posValide(murs.at(i).x + murs.at(i).w, murs.at(i).y))
                {
                    Mur mur(murs.at(i).x, murs.at(i).y, murs.at(i).w, murs.at(i).h);
                    tabMurs.push_back(mur);
                }
                else
                {
                    Mur mur(murs.at(i).x - murs.at(i).w, murs.at(i).y, murs.at(i).w, murs.at(i).h);
                    tabMurs.push_back(mur);
                }
            }
            else
            {
                if (terrain.posValide(murs.at(i).x, murs.at(i).y + murs.at(i).h))
                {
                    Mur mur(murs.at(i).x, murs.at(i).y, murs.at(i).w, murs.at(i).h);
                    tabMurs.push_back(mur);
                }
                else
                {
                    Mur mur(murs.at(i).x, murs.at(i).y - murs.at(i).h, murs.at(i).w, murs.at(i).h);
                    tabMurs.push_back(mur);
                }
            }
        }

        posMurTerrain.clear();
        murs.clear();
    }
}

void Jeu::placementMurs(bool etat)
{
    int nbMurs = getNbMurs();
    int dimx = terrain.getDimX();
    int dimy = terrain.getDimY();

    // Boucle for qui efface tout les murs qui sont à l'interieur du niveau
    for (int y = 1; y < dimy - 1; y++)
    {
        for (int x = 1; x < dimx - 1; x++)
        {
            if (terrain.getXY(x, y) == '#')
                terrain.setXY(x, y, ' ');
        }
    }

    int largeur, hauteur;
    bool obstacle;

    // Boucle qui dessine les murs stocker dans tabMurs
    for (int y = 1; y < dimy - 1; y++)
    {
        for (int x = 1; x < dimx - 1; x++)
        {
            for (int i = 0; i < nbMurs; i++)
            {
                tabMurs[i].setEtatMur(etat);

                // vérifie si il y a un mur à la case de coordonnées (x, y)
                if ((x == tabMurs[i].getMur().x) && (y == tabMurs[i].getMur().y))
                {
                    obstacle = false;
                    largeur = tabMurs[i].getMur().w;
                    hauteur = tabMurs[i].getMur().h;

                    for (int j = 0; j < largeur; j++)
                    {
                        for (int k = 0; k < hauteur; k++)
                        {
                            if (!terrain.emplacementLibre(x + j, y + k) ||
                                caseContientSerpent(x + j, y + k))
                                obstacle = true;
                        }
                    }

                    if (obstacle)
                        tabMurs[i].setEtatMur(!etat);
                    int _x = tabMurs[i].getMur().x;
                    int _y = tabMurs[i].getMur().y;

                    // Boucle dessine le mur par rapport à sa hauteur et sa largeur
                    for (int j = 0; j < largeur; j++)
                    {
                        for (int k = 0; k < hauteur; k++)
                        {
                            terrain.setXY(_x + j, _y + k, '#');
                        }
                    }
                }
            }
        }
    }
}

void Jeu::actionInterrupteur(bool &etat)
{
    int x = serpent.getTete().x;
    int y = serpent.getTete().y;
    if (terrain.getXY(x, y) == 'i')
    {
        if (etat)
            etat = false;
        else
            etat = true;
        placementMurs(etat);
    }
}
