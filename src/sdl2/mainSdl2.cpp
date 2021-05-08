#include "SdlJeu.h"
#include "../core/Jeu.h"

int main(int argc, char **argv)
{
	Jeu jeu("./data/niveau5.txt");
	sdlJeu sj(argv[1]);
	
	sj.sdlBoucle();
	
	cout << "GAME OVER!" << endl
		 << "Score: " << sj.sdlJeu_score<< endl
		 << "Best Score: " << sj.meilleurScore << endl;
	return 0;
}