#include "Terrain.h"
#include "Serpent.h"
#include "Point.h"
#include "Mur.h"
#include "Bonus.h"
#include "Rect.h"
#include "../txt/TxtFenetre.h"
#include <vector>
using namespace std;

#ifndef _JEU_H
#define _JEU_H

/**
 * \class Jeu
 * \brief Classe qui permet la gestion des fonctionnalités du jeu 
 */
class Jeu
{
private:
    Terrain terrain; //!< terrain de type Terrain, correspond au niveau dans lequel vont ce dérouler le jeu   
    Serpent serpent; //!< serpent de type Serpent, serpent sur lequel des éléments vont intéragir 
    vector<Portail> tabPortail; //!< tabPortail de type vector (tableau dynamique), va contenir les portails placés dans le niveau 
    vector<Bonus> tabBonus; //!< tabBonus de type vector (tableau dynamique), va contenir les bonus placés dans le niveau
    vector<Mur> tabMurs; //!< tabMurs de type vector (tableau dynamique), va contenir les murs placés dans le niveau
    int score; //!< score de type entier, récupère le score d'une partie
    int meilleurScore; //!< meilleurScore de type entier, récupère le meilleur score 
    int multiplicateur; //!< multiplicateur de type entier, sert à modifier la vitesse d'incrémentation du score 

public:

    /**
     * @brief constructeur de la classe Jeu 
     * @param namefile de type string passé en donnée/résultat: fichier contenant le niveau du jeu
     * @code 
     * Jeu::Jeu(const string &nomFichier) : serpent(3, terrain.getDimX() / 2, 
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
     * @endcode 
    */
    Jeu(const string &nomFichier);

    /**
     * @brief destructeur de la classe Jeu 
    */
    ~Jeu();

    /**
     * @brief accesseur sur un objet Terrain
     * @code 
     * const Terrain &Jeu::getTerrain() const { return terrain; }
     * @endcode 
     * @return terrain de type Terrain
    */
    const Terrain &getTerrain() const;

    /**
     * @brief accesseur sur un objet Serpent 
     * @code 
     * const Terrain &Jeu::getSerpent() const { return serpent; }
     * @endcode 
     * @return serpent de type Serpent
    */
    const Serpent &getSerpent() const;

    /**
     * @brief accesseur sur un tableau d'objets de type Mur
     * @code 
     * int Jeu::getNbMurs() const
        {
            return tabMurs.size();
        }
     * @endcode 
     * @return taille du tableau tabMurs de type Mur 
    */
    int getNbMurs() const;

    /**
     * @brief accesseur sur un objet de type Mur
     * @param i de type entier: indice sur le tableau tabBonus  
     * @code 
     * Mur Jeu::getMur(int i) const
        {
            return tabMurs[i];
        }
     * @endcode
     * @return tabMurs d'indice i, de type Mur 
    */
    Mur getMur(int i) const;

    /**
     * @brief accesseur sur un tableau d'objets de type Portail
     * @param i de type entier: indice sur le tableau tabBonus 
     * @code 
     * Portail Jeu::getPortail(int i) const
        {
            return tabPortail[i];
        }
     * @endcode 
     * @return élément de type Portail appartenant au tableau tabPortail à l'indice i
    */
    Portail getPortail(int i) const;

    /**
     * @brief accesseur sur le nombre de portail dans le tableau tabPortail
     * @code
     * int Jeu::getNbPortails() const
        {
            return tabPortail.size();
        }
     * @endcode
     * @return taille du tableau tabPortail de type entier 
    */
    int getNbPortails() const;

    /**
     * @brief accesseur sur bonus 
     * @param i de type entier: indice sur le tableau tabBonus
     * @code 
     * Bonus Jeu::getBonus(int i) const
        {
            return tabBonus[i];
        }
     * @endcode 
     * @return élément d'indice i du tableau tabBonus de type Bonus
    */
    Bonus getBonus(int i) const;

    /**
     * @brief accesseur sur la taille du tableau tabBonus 
     * @code 
     * int Jeu::getNbBonus() const
        {
            return tabBonus.size();
        }   
     * @endcode 
     * @return taille du tableau tabBonus de type entier
    */
    int getNbBonus() const;

    /**
     * @brief accesseur sur l'élément score 
     * @code 
     * int Jeu::getScore()
        {
            return score;
        }
     * @endcode
     * @return score de type entier
    */
    int getScore();

    /**
     * @brief accesseur sur l'élément meilleurScore
     * @code
     * int Jeu::getMeilleurScore()
        {
            return meilleurScore;
        }
     * @endcode 
     * @return meilleurScore de type entier 
    */
    int getMeilleurScore();

    /**
     * @brief mutateur sur l'élément score 
     * @param val de type entier: valeur que l'on ajoute à l'élément score
     * @code 
     * void Jeu::setScore(int val)
        {
            score += val*multiplicateur;
        }
     * @endcode
    */
    void setScore(int val);

    /**
     * @brief fonction qui stocke le meilleut score dans un fichier 
     * @code 
     * int Jeu::stockerMeilleurScore()
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
     * @endcode
     * @return meilleurScore ou 0 de type entier  
    */
    int stockerMeilleurScore();

    /**
     * @brief fonction qui assigne les touches du clavier à des actions
     * @param touche de type char: correspond à une touche du clavier 
     * @code 
     * void Jeu::actionClavier(const char touche) // gestion des touches pour les différentes actions
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
     * @endcode
     * @return true si le serpent mange une pièce false sinon
    */
    void actionClavier(const char touche);

    /**
     * @brief fonction qui place aléatoirement les bonus 
     * @code 
     * void Jeu::placementAleatoireBonus()
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
     * @endcode 
    */
    void placementAleatoireBonus();

    /**
     * @brief fonction qui met en mouvement le serpent
     * @code 
     * bool Jeu::SerpentBouge()
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
     * @endcode
     * @return true si le serpent avance, false si le serpent entre en collision avec lui même
    */
    bool SerpentBouge();

    /**
     * @brief fonction qui gère les actions liées au serpent 
     * @code 
     * void Jeu::actionSurSerpent()
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
     * @endcode 
    */
    void actionSurSerpent();

    /**
     * @brief fonction qui gère le fonctionnement des portails 
     * @code 
     * void Jeu::actionPortail()
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
     * @endcode
    */
    void actionPortail();

    /**
     * @brief vérifie si la case donnée par les coordonnées passées en paramètre contient un élément du serpent
     * @param x de type entier: position en x de la case
     * @param y de type entier: position en y de la case
     * @code 
     * bool Jeu::caseContientSerpent(int x, int y)
        {
            for (int i = 0; i < serpent.getTailleSerpent(); i++)
                if ((x == serpent.getCorps(i).x) && (y == serpent.getCorps(i).y))
                    return true;
            return false;
        }
     * @endcode 
     * @return true si un élément du serpent ce trouve aux coordonnées passées en paramètre false sinon
    */
    bool caseContientSerpent(int x, int y);

    /**
     * @brief fonction qui récupère la position ainsi que les dimensions de chaque mur du niveau et les stocke dans un tableau 
     * @code 
     * void Jeu::tabMursTerrain()
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
     * @endcode
    */
    void tabMursTerrain();

    /**
     * @brief fonction qui gère la position de chaque mur stockés dans le tableau tabMurs
     * @param etat de type booléen: désigne l'état dans lequel est le mur (position une ou position deux)
     * @code 
     * void Jeu::placementMurs(bool etat)
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
     * @endcode
    */
    void placementMurs(bool etat);

    /**
     * @brief gère le fonctionnement des interrupteurs
     * @param etat de type booléen passé en donnée/résultat: etat du mur en fonction de si un interrupteur à été activé ou pas
     * @code 
     * void Jeu::actionInterrupteur(bool &etat)
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
     * @endcode 
    */
    void actionInterrupteur(bool &etat);

};

#endif
