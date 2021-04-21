#include <cassert>
#include <time.h>
#include "SdlJeu.h"
#include <stdlib.h>
#include <iostream>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif // WIN32

using namespace std;

const int TAILLE_SPRITE = 42;

float temps () {
    return float(SDL_GetTicks()) / CLOCKS_PER_SEC;  // conversion des ms en secondes en divisant par 1000
}

// ============= CLASS IMAGE =============== //

Image::Image () {
    surface = NULL;
    texture = NULL;
    aChange = false;
}

void Image::chargeFichier (const char* nomFichier, SDL_Renderer * renderer) {
    surface = IMG_Load(nomFichier);
    if (surface == NULL) {
        string nfn = string("./") + nomFichier;
        cout << "Error: cannot load "<< nomFichier <<". Trying "<<nfn<<endl;
        surface = IMG_Load(nfn.c_str());
        if (surface == NULL) {
            nfn = string("./") + nfn;
            surface = IMG_Load(nfn.c_str());
        }
    }
    if (surface == NULL) {
        cout<<"Error: cannot load "<< nomFichier <<endl;
        SDL_Quit();
        exit(1);
    }

    SDL_Surface * surfaceCorrectPixelFormat = SDL_ConvertSurfaceFormat(surface,SDL_PIXELFORMAT_ARGB8888,0);
    SDL_FreeSurface(surface);
    surface = surfaceCorrectPixelFormat;
   
    texture = SDL_CreateTextureFromSurface(renderer,surfaceCorrectPixelFormat);
    if (texture == NULL) {
        cout << "Error: problem to create the texture of "<< nomFichier << endl;
        SDL_Quit();
        exit(1);
    }
    SDL_FreeSurface(surfaceCorrectPixelFormat);
}

void Image::chargeSurface (SDL_Renderer * renderer) {
    texture = SDL_CreateTextureFromSurface(renderer,surface);
    if (texture == NULL) {
        cout << "Error: problem to create the texture from surface " << endl;
        SDL_Quit();
        exit(1);
    }
}

void Image::dessiner (SDL_Renderer * renderer, int x, int y, int w, int h) {
    int ok;
    SDL_Rect r;
    r.x = x;
    r.y = y;
    r.w = (w<0)?surface->w:w;
    r.h = (h<0)?surface->h:h;

    if (aChange) {
        ok = SDL_UpdateTexture(texture,NULL,surface->pixels,surface->pitch);
        assert(ok == 0);
        aChange = false;
    }

    ok = SDL_RenderCopy(renderer,texture,NULL,&r);
    assert(ok == 0);
}

SDL_Texture * Image::getTexture() const {return texture;}

void Image::setSurface(SDL_Surface * surf) {surface = surf;}

sdlJeu::sdlJeu () : jeu("./data/niveau2.txt") {
    // Initialisation de la SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        cout << "Erreur lors de l'initialisation de la SDL : " << SDL_GetError() << endl;
        SDL_Quit();
        exit(1);
    }

    if (TTF_Init() != 0) {
        cout << "Erreur lors de l'initialisation de la SDL_ttf : " << TTF_GetError() << endl;
        SDL_Quit();
        exit(1);
    }

    int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
    if( !(IMG_Init(imgFlags) & imgFlags)) {
        cout << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << endl;
        SDL_Quit();
        exit(1);
    }

    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
    {
        cout << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << endl;
        cout << "No sound !!!" << endl;
        //SDL_Quit();exit(1);
        avecson = false;
    }
    else avecson = true;

	int dimx, dimy;
	dimx = jeu.getTerrain().getDimX();
	dimy = jeu.getTerrain().getDimY();
	dimx = dimx * TAILLE_SPRITE;
	dimy = dimy * TAILLE_SPRITE;

    // Creation de la fenetre
    window = SDL_CreateWindow("Nibble", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, dimx, dimy, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if (window == NULL) {
        cout << "Erreur lors de la creation de la fenetre : " << SDL_GetError() << endl; 
        SDL_Quit(); 
        exit(1);
    }

    renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);

    // IMAGES
    im_TeteSerpent.chargeFichier("data/snake-head.png",renderer);
    im_CorpsSerpent.chargeFichier("data/snake-tex.png",renderer);
    im_QueueSerpent.chargeFichier("data/tail.png",renderer);
    im_Piece.chargeFichier("data/food.png",renderer);
    im_Bonus.chargeFichier("data/fruit1.png",renderer);
    im_Mur.chargeFichier("data/nibble-map.png",renderer);
    im_Cle.chargeFichier("data/cle.png",renderer);
    im_Portail.chargeFichier("data/portail.png",renderer);
    im_Interrupteur.chargeFichier("data/interrupteurEteint.png",renderer);
    im_GameOver.chargeFichier("data/game-over.jpg",renderer);
    // FONTS
    font = TTF_OpenFont("data/DejaVuSansCondensed.ttf",50);
    if (font == NULL)
        font = TTF_OpenFont("../data/DejaVuSansCondensed.ttf",50);
    if (font == NULL) {
            cout << "Failed to load DejaVuSansCondensed.ttf! SDL_TTF Error: " << TTF_GetError() << endl; 
            SDL_Quit(); 
            exit(1);
	}
	font_color.r = 50;font_color.g = 50;font_color.b = 255;
	font_im.setSurface(TTF_RenderText_Solid(font,"Nibble",font_color));
	font_im.chargeSurface(renderer);

    // SONS
    if (avecson)
    {
        son = Mix_LoadWAV("data/son1.wav");
        if (son == NULL) 
            son = Mix_LoadWAV("../data/son1.wav");
        if (son == NULL) {
                cout << "Failed to load son1.wav! SDL_mixer Error: " << Mix_GetError() << endl; 
                SDL_Quit();
                exit(1);
        }
    }
}

sdlJeu::~sdlJeu () {
    if (avecson) Mix_Quit();
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void sdlJeu::sdlAff () {
	//Remplir l'�cran de blanc
    SDL_SetRenderDrawColor(renderer, 230, 240, 255, 255);
    SDL_RenderClear(renderer);

	int x,y;
	const Terrain& ter = jeu.getTerrain();
	const Serpent& serp = jeu.getSerpent();
    Bonus bon = jeu.getBonus(0);
	Portail p = jeu.getPortail(0);

    // Afficher les sprites des murs et des pieces
	for (x=0;x<ter.getDimX();++x)
		for (y=0;y<ter.getDimY();++y)
			if (ter.getXY(x,y)=='#')
				im_Mur.dessiner(renderer,x*TAILLE_SPRITE,y*TAILLE_SPRITE,TAILLE_SPRITE,TAILLE_SPRITE);
			else if (ter.getXY(x,y)=='.')
				im_Piece.dessiner(renderer,x*TAILLE_SPRITE,y*TAILLE_SPRITE,TAILLE_SPRITE,TAILLE_SPRITE);
                else if (ter.getXY(x, y) == 'i')
                        im_Interrupteur.dessiner(renderer,x*TAILLE_SPRITE,y*TAILLE_SPRITE,TAILLE_SPRITE,TAILLE_SPRITE);
                        else if (ter.getXY(x, y) == 'b')                              
                                im_Bonus.dessiner(renderer,x*TAILLE_SPRITE,y*TAILLE_SPRITE,TAILLE_SPRITE,TAILLE_SPRITE);           
                            else if (ter.getXY(x, y) == 'c')
                                im_Cle.dessiner(renderer,x*TAILLE_SPRITE,y*TAILLE_SPRITE,TAILLE_SPRITE,TAILLE_SPRITE);
    //Afficher les sprites des bonus
    
    for(int j= 0;j < jeu.getNbBonus();j++) {
    im_Bonus.dessiner(renderer,bon.getX()*TAILLE_SPRITE,bon.getY()*TAILLE_SPRITE,TAILLE_SPRITE,TAILLE_SPRITE);
    }
    // Afficher le sprite de Serpent
	im_TeteSerpent.dessiner(renderer,serp.getTete().x*TAILLE_SPRITE,serp.getTete().y*TAILLE_SPRITE,TAILLE_SPRITE,TAILLE_SPRITE);
    int a = serp.getTailleSerpent();
    for(int i=1;i<a-1;++i)
    {
        im_CorpsSerpent.dessiner(renderer,serp.getCorps(i).x*TAILLE_SPRITE,serp.getCorps(i).y*TAILLE_SPRITE,TAILLE_SPRITE,TAILLE_SPRITE);
    }
    if(serp.getCorps(a-2).x==serp.getCorps(a-1).x-1) 
    {
        im_QueueSerpent.chargeFichier("data/tail-right.png",renderer);
    }else if(serp.getCorps(a-2).x==serp.getCorps(a-1).x+1) 
    {
        im_QueueSerpent.chargeFichier("data/tail-left.png",renderer);
    }else if(serp.getCorps(a-2).y==serp.getCorps(a-1).y-1) 
    {
        im_QueueSerpent.chargeFichier("data/tail.png",renderer);
    }else if(serp.getCorps(a-2).y==serp.getCorps(a-1).y+1) 
    {
        im_QueueSerpent.chargeFichier("data/tail-down.png",renderer);
    }
    
    im_QueueSerpent.dessiner(renderer,serp.getCorps(a-1).x*TAILLE_SPRITE,serp.getCorps(a-1).y*TAILLE_SPRITE,TAILLE_SPRITE,TAILLE_SPRITE);

   im_Portail.dessiner(renderer,p.getPortail1().x*TAILLE_SPRITE,p.getPortail1().y*TAILLE_SPRITE,TAILLE_SPRITE,TAILLE_SPRITE);
   im_Portail.dessiner(renderer,p.getPortail2().x*TAILLE_SPRITE,p.getPortail2().y*TAILLE_SPRITE,TAILLE_SPRITE,TAILLE_SPRITE);
  // Ecrire un titre par dessus
    SDL_Rect positionTitre;
    positionTitre.x = 270;positionTitre.y = 49;positionTitre.w = 100;positionTitre.h = 30;
    SDL_RenderCopy(renderer,font_im.getTexture(),NULL,&positionTitre);

}
void sdlJeu::sdlGameOver()
{  
    
      
    im_GameOver.dessiner(renderer,0,0,1920,1080);
   

}

void sdlJeu::sdlBoucle () {
    SDL_Event events;
	bool quit = false;
    bool etat = true;
    bool ok = true;
    
    
   Mix_PlayChannel(-1,son,0);
	// tant que ce n'est pas la fin ...
	do {
        
        #ifdef _WIN32
        Sleep(100);
		#else
		usleep(100000);
        #endif // WIN32

            jeu.setScore(1);
        ok = jeu.SerpentBouge();
        jeu.actionSurSerpent();
        jeu.actionPortail();
        jeu.placementAleatoireBonus();
        jeu.actionInterrupteur(etat);
        
		// tant qu'il y a des evenements � traiter (cette boucle n'est pas bloquante)
		while (SDL_PollEvent(&events)) {
			if (events.type == SDL_QUIT) quit = true;           // Si l'utilisateur a clique sur la croix de fermeture
			else if (events.type == SDL_KEYDOWN) {              // Si une touche est enfoncee
              
				switch (events.key.keysym.sym) {
				case SDLK_z:
					jeu.actionClavier('z');  
                    im_CorpsSerpent.chargeFichier("data/snake-tex.png",renderer);  // car Y inverse
					im_TeteSerpent.chargeFichier("data/snake-head.png",renderer);
                    break;
				case SDLK_s:
					jeu.actionClavier('s'); 
                    im_CorpsSerpent.chargeFichier("data/snake-tex.png",renderer);
                    im_TeteSerpent.chargeFichier("data/snake-head-down.png",renderer);    // car Y inverse
					break;
				case SDLK_q:
					jeu.actionClavier('q');
                    im_CorpsSerpent.chargeFichier("data/snake-tex-right.png",renderer);
					im_TeteSerpent.chargeFichier("data/snake-head-left.png",renderer);
                    break;
				case SDLK_d:
					jeu.actionClavier('d');
                    im_CorpsSerpent.chargeFichier("data/snake-tex-right.png",renderer);
					im_TeteSerpent.chargeFichier("data/snake-head-right.png",renderer);
                    break;
                case SDL_SCANCODE_ESCAPE:
                case SDLK_l:
                    quit = true;
                    break;
				default: break;
				}
				
                //if (avecson)
                  //  Mix_PlayChannel(-1,son,0);
			}
		}

		// on affiche le jeu sur le buffer cach�
		sdlAff();

		// on permute les deux buffers (cette fonction ne doit se faire qu'une seule fois dans la boucle)
        SDL_RenderPresent(renderer);
	}while(!quit && ok);
    
    quit = false ;
    sdlJeu_score = jeu.getScore();
    do{ 
        sdlGameOver();
        		while (SDL_PollEvent(&events)) {
			if (events.type == SDL_QUIT) quit = true;           // Si l'utilisateur a clique sur la croix de fermeture
			else if (events.type == SDL_KEYDOWN) {   
                switch (events.key.keysym.sym) {
                case SDL_SCANCODE_ESCAPE:
                case SDLK_l:
                    quit = true;
                    break;
				default: break;
				}
            }
                }
        SDL_RenderPresent(renderer);
        
    }while(!quit);
    
}
