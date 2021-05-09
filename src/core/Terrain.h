#ifndef _TERRAIN_H
#define _TERRAIN_H
#include <iostream>
#include <vector>
#include "Point.h"
#include <string>
#include "Mur.h"
#include "Portail.h"
#include "Rect.h"
using namespace std;

/**
 * \class Terrain
 * \brief Classe qui permet la création d'un terrain
 */
class Terrain
{
private:
    vector<char> ter;     /* !< tableau dynamique de caractère */
    int dimx;             /* !< dimension en x du terrain */
    int dimy;             /* !< dimension en y du terrain */
    int tailleTerrain;    /* !< taille du terrain */
    vector<Point> tabCle; /* !< tableau dynamique de Point qui stocke les cles */
    // vector<Point> posInterrupteur;
    vector<Mur> tabMurs; /* !< tableau dynamique de Mur */

public:
    /**
     * \brief Constructeur par défaut
     * \code
     *  Terrain::Terrain() : dimx(100), dimy(100) {
     *      // procédure qui lie un fichier et qui stocke son contenue dans le tableau ter
            recupNiveau("./data/niveau2.txt");

            // procéfure qui initialise les clés sur le terrain
            posAleaCle();
        }
     * \endcode
     */
    Terrain();

    /**
     * \brief Constructeur qui prend un fichier en lecture
     * \param nomFichier contenant le terrain que l'on souhaite afficher 
     * \code
     * Terrain::Terrain(const string& namefile) {
     *      // procédure qui lie un fichier et qui stocke son contenue dans le tableau ter
            recupNiveau(namefile);

            // procéfure qui initialise les clés sur le terrain
            posAleaCle();

            // procédure qui initialise le tableau contenant les murs du terrain
            tabMursTerrain();

            // procédure qui place les murs contenu dans tabMurs sur le terrain
            placementMurs(true);
        }
     * \endcode
     */
    Terrain(const string &nomFichier);

    /**
     * \brief Destructeur
     * \code
     *  Terrain::~Terrain () {}
     * \endcode
     */
    ~Terrain();

    /**
     * \brief accesseur qui récupère le caractère qui se trouve aux coordonnées (x, y) dans le tableau ter
     * \param x coordonnée en x
     * \param y coordonnée en y
     * \code
     *  char Terrain::getXY(int x, int y) const {
            assert(x>=0);
            assert(x<dimx);
            assert(y>=0);
            assert(y<dimy);
            return ter[y*dimx+x];
        }   
     * \endcode
     */
    char getXY(const int x, const int y) const;

    /**
     * \brief Retourne la valeur de dimx
     * \code
     *  int Terrain::getDimX () const { 
     *      return dimx; 
     * }
     * \endcode
     */
    int getDimX() const;

    /**
     * \brief Retourne la valeur de dimy
     * \code
     *  int Terrain::getDimY () const { 
     *      return dimy; 
     *  }
     * \endcode
     */
    int getDimY() const;

    /**
     * \brief Retourne la taille du tableau dynamique ter
     * \code
     *  int Terrain::getTailleTerrain() const { 
     *      return tailleTerrain; 
     *  }
     * \endcode
     */
    int getTailleTerrain() const;

    /**
     * \brief retourne les coordonnées de la clé du tableau de clés d'indice passé en paramètre
     * \param indice indique l'élément du tableau tabCles dont on souhaite connaitre les coordonnées
     * \code
     * Point Terrain::getCle(int indice) const {
            return tabCle.at(indice);
        } 
     * \endcode
     */
    Point getCle(int indice) const;

    /**
     * \brief retourne le mur d'indice i passé en paramètre 
     * \param i indice du mur que l'on souhaite retourner 
     * \code
     *  Mur Terrain::getTabMurs (int i) const {
            return tabMurs[i];
        }
     * \endcode
     */
    Mur getTabMurs(int indice) const;

    /**
     * \brief retourne le nombre de clé
     * \code
     *  int Terrain::getNbCle () const {
            return tabCle.size();
        }
     * \endcode
     */
    int getNbCle() const;

    /**
     * \brief retourne le nombre de mur
     * \code
     *  int Terrain::getNbMurs () const {
            return tabMurs.size();
        }
     * \endcode
     */
    int getNbMurs() const;

    /**
     * \brief affecte le caractère passé en paramètre au coordonées souhaité dans le tabelau ter
     * \param x coordonées en x
     * \param y coordonnée en y 
     * \param c caractère que l'on souhaite affecté
     * \code
     *  void Terrain::setXY (const int x, const int y, const char c) {
            assert(x>=0);
            assert(x<dimx);
            assert(y>=0);
            assert(y<dimy);
            // assert(posValide(x, y));
            // assert(emplacementLibre(x, y));  
            ter[y*dimx+x] = c;
        }
     * \endcode
     */
    void setXY(const int x, const int y, const char c);

    /**
     * \brief Fonction qui renvoie true si les coordonnées (x,y) passées en paramètres ce trouve dans le niveau false sinon
     * \param x coordonnée en x
     * \param y coordonnée en y
     * \code
        bool Terrain::posValide(int x, int y) const {
            return ((x>=0) && (x<dimx) && (y>=0) && (y<dimy) && ter[y*dimx+x] != '#');
        }
     * \endcode
     */
    bool posValide(int x, int y) const;

    /**
     * \brief procédure qui permet la récupération d'un niveau via un fichier 
     * \param nomfichier fichier ouvert en lecture 
     * \code
     *  void Terrain::recupNiveau (const string& nomFichier) {
     *      // ouverture du fichier en lecture 
            ifstream monFichier(nomFichier);

            // si le fichier est ouvert 
            if (monFichier) {
                ter.clear();

                // variable de type chaîne de caractère qui permet de stocker la ligne lue dans le fichier 
                string nbCarLigne;
                getline(monFichier, nbCarLigne);

                // dimx prend la valeur de la taille de la première ligne lue
                dimx = nbCarLigne.size();

                // retoure au début du fichier
                monFichier.seekg(0, std::ios::beg);

                // variable de type caractère qui va stocker le caractère lu dans le fichier 
                char a;

                // compteur qui permet de déterminer la fin d'une ligne afin d'éviter de stocker les caractères de fin de chaîne
                int cpt = 1;
                while (monFichier.get(a)) { // tant que le fichier contient des caractères 
                    if (cpt % (dimx+1) != 0) {

                        // le caractère lu est stocké dans le tableau ter
                        ter.push_back(a);
                    }
                    cpt++;
                }

                // tailleTerrain prend la valeur de la taille du tableau ter 
                tailleTerrain = ter.size();

                // dimy est définit grace à tailleTerrain et dimx 
                dimy = (tailleTerrain/dimx);

            } else { // sinon on envoie un message d'erreur 
                cout << "ERREUR: Impossible d'ouvrir le fichier en lecture !" << endl;
            }
        }
     * \endcode
     */
    void recupNiveau(const string &nomFichier);

    /**
     * \brief Procédure qui place aléatoirement 3 clés dans un niveau
     * \code
        void Terrain::posAleaCle () {
            // initialisation du rand()
            srand(time(NULL));

            // boucle for qui initialise le tableau de clés 
            Point cle{0, 0};
            for (int i = 0; i < 3; i++)
                tabCle.push_back(cle);

            // boucle for qui donne une valeur alétoire en x et en y à chaque élément du tableau de clés
            // en respectant certaines conditions 
            for (int c = 0; c < 3; c++) {
                if (c == 0) {
                    do {
                        tabCle.at(c).x = rand()% dimx;
                        tabCle.at(c).y = rand()% dimy;
                    } while (!posValide(tabCle.at(c).x, tabCle.at(c).y));
                }
                
                else 
                    do {
                        tabCle.at(c).x = rand()% dimx;
                        tabCle.at(c).y = rand()% dimy;
                    } while (!posValide(tabCle.at(c).x, tabCle.at(c).y) || 
                            ((tabCle.at(c).x == tabCle.at(c-1).x) && (tabCle.at(c).y == tabCle.at(c-1).y)) || 
                            ((tabCle.at(2).x == tabCle.at(0).x) && (tabCle.at(2).y == tabCle.at(0).y)));
            } 
        }
     * \endcode
     */
    void posAleaCle();

    /**
     * \brief Procédure qui mais le caractère ' ' aux coordonnées (x,y) passées en paramètre
     * \param x coordonnée en x
     * \param y coordonnée en y
     * \code
     *  void Terrain::mangeElement(int x, int y) {
            assert(x>=0);
            assert(x<dimx);
            assert(y>=0);
            assert(y<dimy);
            ter[y*dimx+x] = ' ';
        }
     * \endcode
     */
    void mangeElement(const int x, const int y);

    /**
     * \brief retourne le nombre de pièces présentent dans le terrain 
     * \code
     *  int Terrain::compteurPiece () {
        char c;
        int cmpt = 0;

        // boucle for ou cmpt prend +1 si le caractère lu est '.'
        for (int x = 0; x < dimx; x++) {
            for (int y = 0; y < dimy; y++) {
                c = getXY(x, y);
                if (c == '.')
                    cmpt++;
            }
        }
            return cmpt;
        }
     * \endcode
     */
    int compteurPiece();

    /**
     * \brief retourne true si l'emplacement contient ' ' ou '.', false sinon
     * \param x coordonnée en x
     * \param y coordonnée en y
     * \code
     *  bool Terrain::emplacementLibre(int x, int y) {
            return (((x>=0) && (x<dimx) && (y>=0) && (y<dimy) && ter[y*dimx+x] == ' ') || 
                    ((x>=0) && (x<dimx) && (y>=0) && (y<dimy) && ter[y*dimx+x] == '.'));
        }
     * \endcode
     */
    bool emplacementLibre(int x, int y);

    /**
     * \brief supprime la cle du tableau tabCle à l'indice passé en paramètre
     * \param indice indice du tableau tabCle
     * \code
     *  void Terrain::supprimeCle (int indice) {
            if (indice == 0) 
                tabCle.erase(tabCle.begin());
            else if (indice == 2)
                tabCle.erase(tabCle.begin()+2);
            else tabCle.erase(tabCle.begin()+1);
        }
     * \endcode
     */
    void supprimeCle(int indice);

    /**
     * \brief procédure de test de régression 
     * \code
     *  void Terrain::testRegression(){
	
            int pos;
            int compteur=0;
            
            for(int i=0;i<dimx;i++){
                assert(ter[i]=='#');
            }
            for(int i=1;i<17;i++){
                for(int j=1;j<dimx-1;j++){
                    assert(ter[i*dimx+j]=='.');
                }
            }
            for(int i=(dimy-1)*dimx;i<(dimy-1)*dimx+dimx;i++){
                assert(ter[i]=='#');
            }

            
            for(int i=0;i<dimx;i++){
                pos=posValide(i,0);
                assert(pos==false);
            }
            for(int i=1;i<dimy-1;i++){
                for(int j=1;j<dimx-1;j++){
                    pos=posValide(j,i);
                    assert(pos==true);
                }
            }
            
            posAleaCle();
            for(int i=0;i<3;i++){
                if(ter[tabCle[i].y*dimx+tabCle[i].x]=='c')
                    compteur++;
            }
            assert(compteur==3);
            
            for(int i=1;i<dimy-1;i++){
                for(int j=1;j<dimx-1;j++){
                    mangeElement(j,i);
                    assert(ter[i*dimx+j]==' ');
                }
            }
            cout<<"Class Terrain: assert ended successfully."<<endl;
        }
     * \endcode
     */
    void testRegression();
};

#endif
