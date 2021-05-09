#include <iostream>
#include <cstdlib>
#include <cassert>
#include "Jeu.h"
#include <ctime>
#include <chrono>
#include <thread>
#include <fstream>
using namespace std;

Jeu::Jeu(const string &nomFichier) : terrain(nomFichier) ,serpent(3, terrain.getDimX() / 2,  // constructeur de la classe  
                    terrain.getDimY() / 2, terrain, true), score(0)
{
    terrain.mangeElement(serpent.getTete().x, serpent.getTete().y); 
    tabMursTerrain(); // initialise le tableau de mur 
    placementMurs(true); // place les murs à leur position initial
    srand(time(NULL)); // initialise rand 
    Point a{1, 1};
    Point b{(terrain.getDimX() - 2), (terrain.getDimY() - 2)};
    Portail p(a, b);
    tabPortail.push_back(p); // remplie le tableau contenant les portails 
    multiplicateur = 1;
}

Jeu::~Jeu() {} // destructeur de la classe

const Terrain &Jeu::getTerrain() const { return terrain; } // accesseur sur le terrain

const Serpent &Jeu::getSerpent() const { return serpent; } // accesseur sur le serpent

int Jeu::getNbMurs() const // accesseur sur le nombre de mur
{
    return tabMurs.size();
}

Mur Jeu::getMur(int i) const // accesseur sur le mur d'indice passé en paramètre du tableau tabMur
{
    return tabMurs[i];
}

Portail Jeu::getPortail(int i) const // accesseur sur l'élément d'indice passé en paramètre du tableau tabPortail
{
    return tabPortail[i];
}

int Jeu::getNbPortails() const // accesseur sur le nombre de portail 
{
    return tabPortail.size();
}

Bonus Jeu::getBonus(int i) const // accesseur sur l'élément d'indice passé en paramètre du tableau tabBonus
{
    return tabBonus[i];
}

int Jeu::getNbBonus() const // accesseur sur le nombre de bonus
{
    return tabBonus.size();
}

int Jeu::getScore() // accesseur sur le score
{
    return score;
}

int Jeu::getMeilleurScore() // accesseur sur le meilleur score
{
    return meilleurScore;
}

void Jeu::setScore(int val) // mutateur sur le score
{
    score += val*multiplicateur; // incrémente le score avec la valeur passé en paramètre 
}

int Jeu::stockerMeilleurScore() // stocke le meilleur score dans un fichier 
{
    ifstream monMeilleurScoreL("data/bestScore.txt"); // ouvre le fichier enn lecture 
    if (monMeilleurScoreL) // si le fichier s'ouvre
    {
        monMeilleurScoreL >> meilleurScore; // l'entier contenue dans le fichier est assigné à l'attribue meilleurScore
        monMeilleurScoreL.close(); // on ferme la lecture du fichier 
        if (meilleurScore < score) // si la valeur contenue dans le fichier est inférieur au score 
        {
            ofstream monMeilleurScoreE("data/bestScore.txt"); // ouverture du fichier en écriture 
            if (monMeilleurScoreE) // si le fichier s'ouvre 
            {
                monMeilleurScoreE << score; // le score est écrie dans le fichier
                monMeilleurScoreE.close(); // on ferme le fichier en écriture 
                meilleurScore = score; // meilleurScore prend la valeur de score 
                return score;
            }
            else // sinon (ne s'ouvre pas en écriture)
            {
                cout << "ERREUR: Impossible d'ouvrir le fichier en ecriture !" << endl;
            }
        }
        else // sinon (valeur contenue dans le fichier supérieur au score)
        {
            return meilleurScore;
        }
    }
    else // sinon (ne s'ouvre pas en lecture)
        {
            cout << "ERREUR: Impossible d'ouvrir le fichier en lecture !" << endl;
        }
    return 0;
}

void Jeu::actionClavier(const char touche) // gestion des touches pour les différentes actions
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
}

void Jeu::placementAleatoireBonus() // place aléatoirement les bonus dans le niveau 
{
    int x, y, a;
    int dimx = terrain.getDimX(); // on récupère la dimension en x du terrain
    int dimy = terrain.getDimY(); // on récupère la dimension en y du terrain

    for (int i = 0; i < 3; i++) // boucle for qui créé et stocke 3 bonus dans le tableau tabBonus
    {
        a = rand() % 3; // a prend une valeur aléatoire entre 0 et 2
        if (i == 0) // si c'est le premier élément 
        {
            do
            {
                x = rand() % dimx; // valeur aléatoire entre 0 et dimx - 1
                y = rand() % dimy; // valeur aléatoire entre 0 et dimy - 1
            } while (!terrain.posValide(x, y)); // faire ... tant que les coordonnées ne sont pas valides 
        }
        else // sinon 
        {
            do
            {
                x = rand() % dimx; // valeur aléatoire entre 0 et dimx - 1
                y = rand() % dimy; // valeur aléatoire entre 0 et dimy - 1
            } while (!terrain.posValide(x, y) || ((tabBonus[i - 1].getX() == x) && 
                    (tabBonus[i - 1].getY() == y))); // faire ... tant que la pose n'est pas valide ou qu'un autre bonus à les mêmes coordonnées 
        }
        Bonus b(a, x, y);
        tabBonus.push_back(b); // on stocke le bonus dans le tableau tabBonus
        terrain.setXY(tabBonus[i].getX(), tabBonus[i].getY(), 'b'); // on place le caractère b aux coordonnées correspondant au bonus
    }
}

bool Jeu::SerpentBouge() // gère le déplacement du serpent 
{

    Point dir = serpent.getDirection();
    int x = serpent.getTete().x; // récupère les coordonnées en x de la tête du serpent
    int y = serpent.getTete().y; // récupère les coordonnées en y de la tête du serpent

    for (int i = 1; i < serpent.getTailleSerpent(); i++) // boucle sur le serpent
    {
        if ((serpent.getCorps(i).x == x) && (serpent.getCorps(i).y == y)) // si le serpent entre en collision avec lui même
            return false;
    }

    // gestion des déplacements en fonction de la valeur de l'attribue dir 
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

void Jeu::actionSurSerpent() // gère les actions liées au serpent
{
    int x = serpent.getTete().x; // récupère les coordonnées en x de la tête du serpent
    int y = serpent.getTete().y; // récupère les coordonnées en y de la tête du serpent
    int cpt = terrain.compteurPiece(); // récupère le nombre de pièce présentes dans le niveau  
    int dimx = terrain.getDimX(); // on récupère la dimension en x du terrain
    int dimy = terrain.getDimY(); // on récupère la dimension en y du terrain
    char element = terrain.getXY(x, y); // récupère le caractère de la case passé en paramètre 
    int nbCle = terrain.getNbCle(); // récupère le nombre de clé présent dans le niveau 
    int tailleTabBonus = tabBonus.size(); // récupère la taille du tableau tabBonus

    for (int i = 0; i < nbCle; i++) // place les clés dans le niveau
    {
        terrain.setXY(terrain.getCle(i).x, terrain.getCle(i).y, 'c');
    }

    if (element == '.') // si l'élément de la case est une pièce
    {   
        serpent.allongeCorps(terrain);  // on appel la fonction qui allonge le serpent 
        terrain.mangeElement(x, y); // le serpent mange l'élément 
        setScore(100); // on incrémente le score de 100

        cpt--; // on décrémente le nombre de pièces
    }

    if (element == 'b') // si l'élément de la case est un bonus
    {
        terrain.mangeElement(x, y); // le serpent mange l'élément 
        int indice, action, coordx, coordy;
        for (int i = 0; i < tailleTabBonus; i++) // boucle for qui récupère l'indice du bonus en question
        {
            if (x == tabBonus[i].getX() && y == tabBonus[i].getY())
            {
                indice = i;
                break;
            }
        }

        tabBonus[indice].actionBonus(serpent, terrain); // appel la fonction qui effectue l'action liée au bonus
        if (tabBonus[indice].getAction() == 1) {
            setScore(500);
            multiplicateur = 1;
        }
        else if (tabBonus[indice].getAction() == 2)
            multiplicateur = 2;
        else multiplicateur = 0.5;
        
        do // boncle tant que qui génère un nouveau bonus
        {
            action = rand() % 3;
            coordx = rand() % dimx;
            coordy = rand() % dimy;
        } while (!terrain.posValide(coordx, coordy) || !terrain.emplacementLibre(coordx, coordy));
        tabBonus[indice].setBonus(action, coordx, coordy);
    }

    if (cpt < 30) // si le nombre de pièce dans le niveau est inférieur à 30 
    {
        do // boucle tant que qui génère des pièces
        {
            x = rand() % dimx;
            y = rand() % dimy;
        } while (!terrain.posValide(x, y) || !terrain.emplacementLibre(x, y));
        terrain.setXY(x, y, '.');
    }

    if (element == 'c') // si l'élément de la case est une clé 
    {
        terrain.mangeElement(x, y); // le serpent mange l'élément 
        for (int i = 0; i < 3; i++)
            if ((terrain.getCle(i).x == x) && (terrain.getCle(i).y == y))
            {
                terrain.supprimeCle(i); // on supprime la clé du tableau tabCle
                break;
            }
    }
}

void Jeu::actionPortail() // gère le fonctionnement des portails
{
    int px1 = tabPortail[0].getPortail1().x; // récupère la position en x du premier portail 
    int py1 = tabPortail[0].getPortail1().y; // récupère la position en y du premier portail 

    int px2 = tabPortail[0].getPortail2().x; // récupère la position en x du second portail 
    int py2 = tabPortail[0].getPortail2().y; // récupère la position en y du second portail 

    // on vérifie si le serpent entre dans le portail et on l'envoie dans l'autre portail si oui
    if ((serpent.getTete().x == px1) && (serpent.getTete().y == py1))
    {
        serpent.setTete(px2, py2);
    }

    else if ((serpent.getTete().x == px2) && (serpent.getTete().y == py2))
    {
        serpent.setTete(px1, py1);
    }
}

bool Jeu::caseContientSerpent(int x, int y) // determine si le serpent est dans la case passé en paramètre
{
    for (int i = 0; i < serpent.getTailleSerpent(); i++)
        if ((x == serpent.getCorps(i).x) && (y == serpent.getCorps(i).y))
            return true;
    return false;
}

void Jeu::tabMursTerrain() // stocke les murs du niveau dans un tableau
{
    vector<Rect> posMurTerrain; 
    vector<Rect> murs;
    Rect tampon;
    int dimx = terrain.getDimX();
    int dimy = terrain.getDimY();
    
    for (int y = 1; y < dimy - 1; y++) // boucle for qui stocke dans le tableau posMurTerrain toute les positions des caractères '#' excepté ceux des bordures du niveau
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
        murs.push_back(posMurTerrain[0]); // insert le première élément du tableau posMursTerrain dans le tableau murs
        tailleMurs = 1;
        bool valSortie;

        for (int i = 1; i < taillePosMur; i++) // boucle for qui stocke les coordonnées du premières élément de chaque mur ainsi que leur dimension
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

        for (int i = 0; i < tailleMurs; i++) // boucle for qui stocke les éléments de murs dans le tableau de type Mur, tabMurs
        {
            if (murs.at(i).w > (terrain.getDimX()/2+1) || murs.at(i).h > (terrain.getDimY()/2+1)) {}
            else {
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
        }

        // on vide les deux tableaux tampons 
        posMurTerrain.clear(); 
        murs.clear();
    }
}

void Jeu::placementMurs(bool etat) // gère le placement des murs 
{
    int nbMurs = getNbMurs(); // récupère le nombre de murs
    int dimx = terrain.getDimX(); // on récupère la dimension en x du terrain
    int dimy = terrain.getDimY(); // on récupère la dimension en y du terrain

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

void Jeu::actionInterrupteur(bool &etat) // gère le fonctionnement des interrupteurs
{
    int x = serpent.getTete().x; // récupère les coordonnées en x de la tête du serpent 
    int y = serpent.getTete().y; // récupère les coordonnées en y de la tête du serpent 
    if (terrain.getXY(x, y) == 'i') // si la case contient un interrupteur 
    {
        if (etat)
            etat = false;
        else
            etat = true;
        placementMurs(etat); // on appel la fonction qui gère le placlement des murs en fonction de l'etat passé en paramètre
    }
}
