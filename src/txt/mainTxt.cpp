#include "TxtJeu.h"
#include "TxtFenetre.h"

int main(int argc, char **argv)
{
	termClear();
	Jeu jeu("./data/niveau2.txt");
	txtJeu(jeu);
	termClear();
	int score = jeu.getScore();
	int meilleurScore = jeu.getMeilleurScore();
	cout << "GAME OVER!" << endl
		 << "Score: " << score << endl
		 << "Best Score: " << meilleurScore << endl;
	return 0;
}
