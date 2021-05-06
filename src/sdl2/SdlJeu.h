#ifndef SDLJEU_H_NIBBLE
#define SDLJEU_H_NIBBLE

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

#include "../core/Jeu.h"

//! \brief Pour gérer une image avec SDL2
class Image {

private:

    SDL_Surface * surface;
    SDL_Texture * texture;
    bool aChange;

public:
    Image () ;
    void chargeFichier (const char* nomFichier, SDL_Renderer * renderer);
    void chargeSurface (SDL_Renderer * renderer);
    void dessiner (SDL_Renderer * renderer, int x, int y, int w=-1, int h=-1);
    SDL_Texture * getTexture() const;
    void setSurface(SDL_Surface * surf);
};
class sdlJeu{
    private : 
    Jeu jeu;
    SDL_Window * window;
    SDL_Renderer * renderer;
    TTF_Font * font ;
    Image font_im;
    Image score_im;
    Image score_up_im;
    SDL_Color font_color;
    Mix_Chunk * son ;
    bool avecson;
    
    Image im_TeteSerpent;
    Image im_CorpsSerpent;
    Image im_QueueSerpent;
    Image im_Piece;
    Image im_Bonus;
    Image im_Mur;
    Image im_Cle;
    Image im_Portail;
    Image im_Interrupteur;
    Image im_GameOver;
    bool souris;
    bool touche;
    public : sdlJeu();
    ~sdlJeu();
    void sdlBoucle();
    void sdlAff();
    void sdlGameOver();
    int sdlJeu_score;
};
#endif