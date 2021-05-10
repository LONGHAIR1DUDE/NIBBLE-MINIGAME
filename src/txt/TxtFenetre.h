#ifndef _TXTFENETRE_H
#define _TXTFENETRE_H
#include "../core/Point.h"

/**
 * \class Terrain
 * \brief Classe qui permet l'affichae texte du jeu dans le terminal
 */
class TxtFenetre
{
private:
    int dimx, dimy; //!< dimx et dimy de type entier, dimensions de la fenetre du jeu en version txt
    char *fenetre; //!< fenetre pointeur de type caractère, tableau contenant les caractères affichés dans le terminal

public:

    /**
     * @brief constructeur par copie de la classe
     * @param dx de type entier: dimension en x de la fenêtre de jeu 
     * @param dy de type entier: dimension en y de la fenêtre de jeu
     * @code 
     * TxtFenetre::TxtFenetre(int dx, int dy)
        {
            dimx = dx;
            dimy = dy;
            fenetre = new char[dimx * dimy];
            effacer();
            termInit();
        }
     * @endcode  
    */
    TxtFenetre(int dx, int dy);

    /**
     * @brief destructeur de la classe
     * @code 
     * TxtFenetre::~TxtFenetre()
        {
            delete[] fenetre;
        }
     * @endcode
    */
    ~TxtFenetre();

    /**
     * @brief efface le terminal et affiche le caractère passé en paramètre (par défaut ce caractère est ' 'ce qui affiche une fenêtre vide)
     * @param c de type caractère: caractère affiché dans le terminal
     * @code 
     * void TxtFenetre::effacer(char c)
        {
            termClear();
            for (int i = 0; i < dimx; ++i)
                for (int j = 0; j < dimy; ++j)
                    ecrire(i, j, c);
        }
     * @endcode  
    */
    void effacer(char c = ' ');

    /**
     * @brief écrie le caractère passé en paramètre aux coordonnées passées en paramètre 
     * @param x de type entier: coordonné en x du caractère
     * @param y de type entier: coordonné en y du caractère 
     * @param c de type caractère: caractère que l'on souhaite afficher 
     * @code 
     * void TxtFenetre::ecrire(int x, int y, char c)
        {
            if (x < 0)
                return;
            if (y < 0)
                return;
            if (x >= dimx)
                return;
            if (y >= dimy)
                return;
            fenetre[y * dimx + x] = c;
        }
     * @endcode
    */
    void ecrire(int x, int y, char c);

    /**
     * @brief écrie la chaine de caractère passé en paramètre aux coordonnées passées en paramètre 
     * @param x de type entier: coordonné en x du caractère
     * @param y de type entier: coordonné en y du caractère 
     * @param c de type pointeur sur caractère: caractère que l'on souhaite afficher 
     * @code 
     * void TxtFenetre::ecrire(int x, int y, char *c)
        {
            int i = 0;
            while (c[i] != '\0')
            {
                ecrire(x + i, y, c[i]);
                ++i;
            }
        }
     * @endcode
    */
    void ecrire(int x, int y, char *c);

    /**
     * @brief deesine la fenêtre de jeu 
     * @param x de type entier: coordonnée en x où l'on souhaite dessiner le niveau 
     * @param y de type entier: coordonnée en y où l'on souhaite dessiner le niveau 
     * @code
     * void TxtFenetre::dessiner(int x, int y)
        {
            termMove(x, y);
            for (int j = 0; j < dimy; ++j)
            {
                termMove(x, y + j);
                for (int i = 0; i < dimx; ++i)
                {
                    printf("%c", fenetre[j * dimx + i]);
                }
                printf("\n");
            }
            termMove(0, dimy);
        }
     * @endcode
    */
    void dessiner(int x = 0, int y = 0);

    /**
     * @brief met en pause le jeu 
     * @code
     * void TxtFenetre::pause()
        {
        #ifdef _WIN32
            system("pause");
        #else
            printf("Appuyer sur une touche\n");
            while (!kbhit())
                ;
        #endif
        }
     * @endcode
    */
    void pause();

    /**
     * @brief lie un carctere si une touche a ete presee
     * @code
     * char TxtFenetre::getCh()
        { // lire un carctere si une touche a ete presee
            char touche = 0;
        #ifdef _WIN32
            if (kbhit())
            {
                DWORD mode;
                DWORD n;
                HANDLE consoleI = GetStdHandle(STD_INPUT_HANDLE);
                GetConsoleMode(consoleI, &mode);
                SetConsoleMode(consoleI, mode & ~ENABLE_LINE_INPUT & ~ENABLE_ECHO_INPUT);
                ReadConsole(consoleI, &touche, 1, &n, NULL);
            }
        #else
            if (kbhit())
                touche = fgetc(stdin);
        #endif
            return touche;
        }
     * @endcode
    */
    char getCh();

    /**
     * @brief accesseur sur le caractère aux coordonnées passées en paramètre 
     * @param x de type entier: coordonnée en x du caractère
     * @param y de type entier: coordonnée en y du caractère 
     * @code 
     * char TxtFenetre::getCarFenetre(int x, int y)
        {
            return fenetre[y * dimx + x];
        }
     * @endcode
    */
    char getCarFenetre(int x, int y);
};

Point getDimTerminale();
void termClear();

#endif