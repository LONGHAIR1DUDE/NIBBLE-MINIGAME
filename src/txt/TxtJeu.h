#ifndef _TXTJEU_H
#define _TXTJEU_H

#include "../core/Jeu.h"

/**
 * @brief boucle du jeu nibble en mode txt
 * @param j de type jeu passé par référence
 * @code 
 * void txtJeu(Jeu &j)
    {
        TxtFenetre fenetre(j.getTerrain().getDimX(), j.getTerrain().getDimY());
        TxtFenetre score(10, 10);

        bool etat = true;
        bool ok = true;
        char car;

        do
        {
            affichageTxt(fenetre, j);
            affichageScore(score, j);

    #ifdef _WIN32
            Sleep(100);
    #else
            usleep(100000);
    #endif // WIN32

            j.setScore(1);
            ok = j.SerpentBouge();
            j.actionSurSerpent();
            j.actionPortail();
            j.placementAleatoireBonus();
            j.actionInterrupteur(etat);
            car = fenetre.getCh();
            switch (car)
            {
            case 'z':
                j.actionClavier('z');
                break;
            case 'q':
                j.actionClavier('q');
                break;
            case 's':
                j.actionClavier('s');
                break;

            case 'd':
                j.actionClavier('d');
                break;

            case 'l':
                ok = false;
                break;
            }
        } while (ok);
    }
 * @endcode
*/
void txtJeu(Jeu &j);

#endif