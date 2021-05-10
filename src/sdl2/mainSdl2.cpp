#include "SdlJeu.h"
#include "../core/Jeu.h"

int main(int argc, char **argv)
{
	
	sdlJeu sj(argv[1],"./data/niveau2.txt");
	
	sj.sdlBoucle();
	
	cout << "GAME OVER!" << endl
		 << "Score: " << sj.sdlJeu_score<< endl
		 << "Best Score: " << sj.meilleurScore << endl;
	return 0;
}