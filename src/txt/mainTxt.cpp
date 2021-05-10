#include "TxtJeu.h"
#include "TxtFenetre.h"

int main(int argc, char **argv)
{
	termClear(); // efface le terminal
	Jeu jeu("./data/niveau4.txt"); // appel le constructeur de la classe jeu avec un niveau passé en paramètre 
	txtJeu(jeu); // lance la boucle de jeu 
	termClear(); // efface le terminal
	int score = jeu.getScore(); // récupère le score de la partie
	int meilleurScore = jeu.getMeilleurScore(); // récupère le meilleur score 
	cout << "GAME OVER!" << endl // affichage de fin de partie
		 << "Score: " << score << endl
		 << "Best Score: " << meilleurScore << endl;
	return 0;
}
