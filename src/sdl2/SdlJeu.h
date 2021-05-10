#ifndef SDLJEU_H_NIBBLE
#define SDLJEU_H_NIBBLE

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>



#include "../core/Jeu.h"

//! \brief Pour gérer une image avec SDL2
class Image
{

private:
    SDL_Surface *surface;
    SDL_Texture *texture;
    bool aChange;

public:
    Image();
    void chargeFichier(const char *nomFichier, SDL_Renderer *renderer);
    void chargeSurface(SDL_Renderer *renderer);
    void dessiner(SDL_Renderer *renderer, int x, int y, int w = -1, int h = -1);
    SDL_Texture *getTexture() const;
    void setSurface(SDL_Surface *surf);
};
class sdlJeu
{
private:
    Jeu jeu;
    SDL_Window *window;
    SDL_Renderer *renderer;
    TTF_Font *font;
    TTF_Font *pdark;
    TTF_Font *player;
    Image font_im;
    Image score_im;
    Image score_up_im;
    Image over_best_im;
    Image best_score_im;
    SDL_Color font_color;
    SDL_Color Title_color;
    SDL_Color best_col;
    SDL_Color game_color;
    Mix_Chunk *son;
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

public:
    sdlJeu(char * size , const string &filename);
    ~sdlJeu();
    double TAILLE_SPRITE ;
    double TAILLE_SPRITE_Y ;
    int screen_width;
    int screen_height;
    void sdlBoucle();
    void sdlAff();
    void sdlGameOver();
    SDL_Rect r_score;
    SDL_Rect r_score_border;
    SDL_Rect r_best_score;
    SDL_Rect r_best_score_border;
    SDL_Rect r_game_over;
    int meilleurScore;
    int sdlJeu_score;
};
#endif