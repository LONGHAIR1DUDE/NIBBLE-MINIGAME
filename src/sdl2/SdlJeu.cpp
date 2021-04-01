#include <cassert>
#include <time.h>
#include "SdlJeu.h"
#include <stdlib.h>
#include <iostream>
using namespace std;

const int TAILLE_SPRITE = 32;

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
        string nfn = string("../") + nomFichier;
        cout << "Error: cannot load "<< nomFichier <<". Trying "<<nfn<<endl;
        surface = IMG_Load(nfn.c_str());
        if (surface == NULL) {
            nfn = string("../") + nfn;
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

// sdlJeu::sdlJeu () : jeu() {
//     // Initialisation de la SDL
//     if (SDL_Init(SDL_INIT_VIDEO) < 0) {
//         cout << "Erreur lors de l'initialisation de la SDL : " << SDL_GetError() << endl;
//         SDL_Quit();
//         exit(1);
//     }

//     if (TTF_Init() != 0) {
//         cout << "Erreur lors de l'initialisation de la SDL_ttf : " << TTF_GetError() << endl;
//         SDL_Quit();
//         exit(1);
//     }

//     int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
//     if( !(IMG_Init(imgFlags) & imgFlags)) {
//         cout << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << endl;
//         SDL_Quit();
//         exit(1);
//     }

//     if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
//     {
//         cout << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << endl;
//         cout << "No sound !!!" << endl;
//         //SDL_Quit();exit(1);
//         withSound = false;
//     }
//     else withSound = true;

// 	int dimx, dimy;
// 	dimx = jeu.getConstTerrain().getDimX();
// 	dimy = jeu.getConstTerrain().getDimY();
// 	dimx = dimx * TAILLE_SPRITE;
// 	dimy = dimy * TAILLE_SPRITE;

//     // Creation de la fenetre
//     window = SDL_CreateWindow("Pacman", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, dimx, dimy, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
//     if (window == NULL) {
//         cout << "Erreur lors de la creation de la fenetre : " << SDL_GetError() << endl; 
//         SDL_Quit(); 
//         exit(1);
//     }

//     renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);

//     // IMAGES
//     im_pacman.loadFromFile("data/pacman.png",renderer);
//     im_mur.loadFromFile("data/mur.png",renderer);
//     im_pastille.loadFromFile("data/pastille.png",renderer);
//     im_fantome.loadFromFile("data/fantome.png",renderer);

//     // FONTS
//     font = TTF_OpenFont("data/DejaVuSansCondensed.ttf",50);
//     if (font == NULL)
//         font = TTF_OpenFont("../data/DejaVuSansCondensed.ttf",50);
//     if (font == NULL) {
//             cout << "Failed to load DejaVuSansCondensed.ttf! SDL_TTF Error: " << TTF_GetError() << endl; 
//             SDL_Quit(); 
//             exit(1);
// 	}
// 	font_color.r = 50;font_color.g = 50;font_color.b = 255;
// 	font_im.setSurface(TTF_RenderText_Solid(font,"Pacman",font_color));
// 	font_im.loadFromCurrentSurface(renderer);

//     // SONS
//     if (withSound)
//     {
//         sound = Mix_LoadWAV("data/son.wav");
//         if (sound == NULL) 
//             sound = Mix_LoadWAV("../data/son.wav");
//         if (sound == NULL) {
//                 cout << "Failed to load son.wav! SDL_mixer Error: " << Mix_GetError() << endl; 
//                 SDL_Quit();
//                 exit(1);
//         }
//     }
// }

// sdlJeu::~sdlJeu () {
//     if (withSound) Mix_Quit();
//     TTF_CloseFont(font);
//     TTF_Quit();
//     SDL_DestroyRenderer(renderer);
//     SDL_DestroyWindow(window);
//     SDL_Quit();
// }

// void sdlJeu::sdlAff () {
// 	//Remplir l'�cran de blanc
//     SDL_SetRenderDrawColor(renderer, 230, 240, 255, 255);
//     SDL_RenderClear(renderer);

// 	int x,y;
// 	const Terrain& ter = jeu.getConstTerrain();
// 	const Pacman& pac = jeu.getConstPacman();
// 	const Fantome& fan = jeu.getConstFantome();

//     // Afficher les sprites des murs et des pastilles
// 	for (x=0;x<ter.getDimX();++x)
// 		for (y=0;y<ter.getDimY();++y)
// 			if (ter.getXY(x,y)=='#')
// 				im_mur.draw(renderer,x*TAILLE_SPRITE,y*TAILLE_SPRITE,TAILLE_SPRITE,TAILLE_SPRITE);
// 			else if (ter.getXY(x,y)=='.')
// 				im_pastille.draw(renderer,x*TAILLE_SPRITE,y*TAILLE_SPRITE,TAILLE_SPRITE,TAILLE_SPRITE);

// 	// Afficher le sprite de Pacman
// 	im_pacman.draw(renderer,pac.getX()*TAILLE_SPRITE,pac.getY()*TAILLE_SPRITE,TAILLE_SPRITE,TAILLE_SPRITE);

// 	// Afficher le sprite du Fantome
// 	im_fantome.draw(renderer,fan.getX()*TAILLE_SPRITE,fan.getY()*TAILLE_SPRITE,TAILLE_SPRITE,TAILLE_SPRITE);

//     // Ecrire un titre par dessus
//     SDL_Rect positionTitre;
//     positionTitre.x = 270;positionTitre.y = 49;positionTitre.w = 100;positionTitre.h = 30;
//     SDL_RenderCopy(renderer,font_im.getTexture(),NULL,&positionTitre);

// }