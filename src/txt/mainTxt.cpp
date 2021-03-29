#include "TxtJeu.h"
#include "TxtFenetre.h"

int main ( int argc, char** argv ) {
    termClear();
	Jeu jeu;
	txtJeu(jeu);
    termClear();
	cout << "GAME OVER!" << endl << "Score: " << jeu.getScore() << endl;
	return 0;
}
