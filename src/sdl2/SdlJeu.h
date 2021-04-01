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

#endif