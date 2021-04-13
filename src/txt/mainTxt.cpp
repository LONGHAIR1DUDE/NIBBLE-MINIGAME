#include "TxtJeu.h"
#include "TxtFenetre.h"

int main ( int argc, char** argv ) {
    termClear();
	Jeu jeu("./data/niveau2.txt");
	txtJeu(jeu);
    termClear();
	int bestScore = jeu.stockerMeilleurScore();
	cout << "GAME OVER!" << endl << "Score: " << jeu.getScore() << endl << "Best Score: " << bestScore << endl;
	return 0;
}
