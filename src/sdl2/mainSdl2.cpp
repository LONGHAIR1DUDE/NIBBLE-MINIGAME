#include "SdlJeu.h"
#include "../core/Jeu.h"

int main (int argc, char** argv) {
	Jeu jeu("./data/niveau5.txt");
	sdlJeu sj;
	sj.sdlBoucle();
	int score = jeu.getScore();
	int meilleurScore = jeu.getMeilleurScore();
	sj.sdlGameOver();
	cout << "GAME OVER!" << endl << "Score: " << score << endl << "Best Score: " << meilleurScore << endl;
	return 0;
}