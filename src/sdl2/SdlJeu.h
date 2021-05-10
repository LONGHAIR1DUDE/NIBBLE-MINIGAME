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
/**
 * \class sdlJeu
 * \brief Classe qui permet la gestion d'affichage a l'aide du SDL2
 */
class sdlJeu
{
private:
    Jeu jeu;//!<jeu de type jeu,correspond a une instance du jeu
    SDL_Window *window;//!<window de type SDL_Window,correspond a la fenetre ou on fera l'affichage de nos elements
    SDL_Renderer *renderer;
    TTF_Font *font;//!<font de type TTF_font,le nom du font est crackman
    TTF_Font *pdark;//!<font de type TTF_font,le nom du font est neuropol xrg
    TTF_Font *player;//!<font de type TTF_font,le nom du font est player1up
    Image font_im;//!<font_im de type Image,va contenir le titre de l'application "Nibble"
    Image score_im;//!<score_im de type Image,va contenir le score
    Image score_up_im;//!<score_up_im de type Image,va contenir le score dans l'ecran "GAME OVER"
    Image over_best_im;//!<over_best_im de type Image,va contenir le meilleur score dans l'ecran "GAME OVER"
    Image best_score_im;//!<best_score_im de type Image,va contenir le meilleur score
    SDL_Color font_color;//!<font_color de type SDL_Color , correspond a la couleur des scores
    SDL_Color Title_color;//!<Title_color de type SDL_Color,correspond a la couleur du titre "Nibble"
    SDL_Color best_col;//!<best_col de type SDL_Color , correspond a la couleur du meilleur score
    SDL_Color game_color;//!<game_color de type SDL_Color , correspond a la couleur du game over
    Mix_Chunk *son;//!< son de type Mix_chunk* , contient le son du jeu
    bool avecson;//!< avecson de type bool , indique si le jeu est avec ou sans son

    Image im_TeteSerpent;//!<im_TeteSerpent de Type Image va contenir la tete du serpent
    Image im_CorpsSerpent;//!<im_CorpsSerpent de Type Image va contenir le corps du serpent
    Image im_QueueSerpent;//!<im_TeteSerpent de Type Image va contenir la queue du serpent
    Image im_Piece;//!<im_Piece de Type Image va contenir les pieces 
    Image im_Bonus;//!<im_Bonus de Type Image va contenir les bonus
    Image im_Mur;//!<im_Mur de Type Image va contenir les murs
    Image im_Cle;//!<im_Cle de Type Image va contenir les cles
    Image im_Portail;//!<im_Portail de Type Image va contenir les portails
    Image im_Interrupteur;//!<im_Interrupteur de Type Image va contenir les interrupteurs
    Image im_GameOver;//!<im_GameOver de Type Image correspond a l'écran "Game Over"
    double TAILLE_SPRITE ;//!<TAILLE_SPRITE de type double correspond a la largeur des sprite
    double TAILLE_SPRITE_Y ;//!<TAILLE_SPRITE_Y de type double correspond a la hauteur des sprite
    int screen_width;//!<screen_width de type int correspond a la largeur de la fenetre d'affichage
    int screen_height;//!<screen_height de type int correspond a la hauteur de la fenetre d'affichage
    SDL_Rect r_score;//!<r_score de type SDL_Rect correspond au rectangle sur lequel on affiche le score
    SDL_Rect r_score_border;//!<r_score_border de type SDL_Rect est le rectangle qui sert a dessiner des bordures pour le rectangle r_score
    SDL_Rect r_best_score;//!<r_best_score de type SDL_Rect correspond au rectangle sur lequel on affiche le meilleur score
    SDL_Rect r_best_score_border;//!<r_best_score_border de type SDL_Rect est le rectangle qui sert a dessiner des bordures pour le rectangle r_best_score
    SDL_Rect r_game_over;//!<r_game_over de type SDL_Rect correspond au rectangle sur lequel on affiche "GAME OVER" et les scores

    bool souris;
    bool touche;

public:
    /**
     * @brief constructeur de la classe sdlJeu 
     * @param  de type string passé en donnée/résultat: fichier contenant le niveau du jeu
     * @code 
     * sdlJeu::sdlJeu(char * size,const string &filename) : jeu(filename)
{   
    
    // Initialisation de la SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        cout << "Erreur lors de l'initialisation de la SDL : " << SDL_GetError() << endl;
        SDL_Quit();
        exit(1);
    }

    if (TTF_Init() != 0)
    {
        cout << "Erreur lors de l'initialisation de la SDL_ttf : " << TTF_GetError() << endl;
        SDL_Quit();
        exit(1);
    }

    int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
    if (!(IMG_Init(imgFlags) & imgFlags))
    {
        cout << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << endl;
        SDL_Quit();
        exit(1);
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        cout << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << endl;
        cout << "No sound !!!" << endl;
        //SDL_Quit();exit(1);
        avecson = false;
    }
    else
        avecson = true;

    int dimx, dimy;
    dimx = jeu.getTerrain().getDimX();
    dimy = jeu.getTerrain().getDimY();
    if(*size == '0')
    {   screen_width = 1280;
    screen_height = 720;
    }
    if(*size == '1')
    {   screen_width = 960;
    screen_height = 540;
    }
        TAILLE_SPRITE = screen_width/dimx;
    TAILLE_SPRITE_Y = screen_height/dimy;

    // Creation de la fenetre
    window = SDL_CreateWindow("Nibble", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screen_width, screen_height, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if (window == NULL)
    {
        cout << "Erreur lors de la creation de la fenetre : " << SDL_GetError() << endl;
        SDL_Quit();
        exit(1);
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    
    
     
    // IMAGES
    im_TeteSerpent.chargeFichier("data/snake-head.png", renderer);
    im_CorpsSerpent.chargeFichier("data/snake-tex.png", renderer);
    im_QueueSerpent.chargeFichier("data/tail.png", renderer);
    im_Piece.chargeFichier("data/food.png", renderer);
    im_Bonus.chargeFichier("data/fruit2.png", renderer);
    im_Mur.chargeFichier("data/nibble-map.png", renderer);
    im_Cle.chargeFichier("data/cle.png", renderer);
    im_Portail.chargeFichier("data/portail1.png", renderer);
    im_Interrupteur.chargeFichier("data/interrupteurEteint.png", renderer);
    
    // FONTS
    font = TTF_OpenFont("data/crackman.ttf", 50);
    if (font == NULL)
        font = TTF_OpenFont("../data/crackman.ttf", 50);
    if (font == NULL)
        font = TTF_OpenFont("../data/crackman.ttf",50);
    if (font == NULL) {
            cout << "Failed to load crackman.ttf! SDL_TTF Error: " << TTF_GetError() << endl; 
            SDL_Quit(); 
            exit(1);
	}
    pdark = TTF_OpenFont("data/neuropolxrg.ttf", 70);
    if (pdark == NULL)
        pdark = TTF_OpenFont("../data/neuropolxrg.ttf", 70);
    if (pdark == NULL)
        pdark = TTF_OpenFont("../data/neuropolxrg.ttf",70);
    if (pdark == NULL) {
            cout << "Failed to load neuropolxrg.ttf! SDL_TTF Error: " << TTF_GetError() << endl; 
            SDL_Quit(); 
            exit(1);
	}
        player = TTF_OpenFont("data/ghostclan.ttf", 70);
    if (player == NULL)
        player = TTF_OpenFont("../data/ghostclan.ttf", 70);
    if (player == NULL)
        player = TTF_OpenFont("../data/ghostclan.ttf",70);
    if (player == NULL) {
            cout << "Failed to load pdark.ttf! SDL_TTF Error: " << TTF_GetError() << endl; 
            SDL_Quit(); 
            exit(1);
	}
	Title_color.r = 220;Title_color.g = 20;Title_color.b = 60;
	font_im.setSurface(TTF_RenderText_Solid(font,"Nibble",Title_color));
	font_im.chargeSurface(renderer);

    // SONS
    if (avecson)
    {
        son = Mix_LoadWAV("data/snake-music.wav");
        if (son == NULL) 
            son = Mix_LoadWAV("../data/snake-music.wav");
        if (son == NULL) {
                cout << "Failed to load son1.wav! SDL_mixer Error: " << Mix_GetError() << endl; 
                SDL_Quit();
                exit(1);
        }
    }
    r_score.x = screen_width/2-screen_width/20;
    r_score.y=0;
    r_score.w = screen_width/10;
    r_score.h= TAILLE_SPRITE_Y;
    r_score_border.y=screen_height/200;
    r_score_border.x = screen_width/2-screen_width/20 + r_score_border.y;
    r_score_border.w = screen_width/10 - 2*r_score_border.y;
    r_score_border.h= TAILLE_SPRITE_Y- 2*r_score_border.y;

    r_best_score.x = r_score.x + r_score.w +screen_width/200;
    r_best_score.y=r_score.y;
    r_best_score.w = r_score.w ;
    r_best_score.h= r_score.h;
    r_best_score_border.y=r_score_border.y;
    r_best_score_border.x = r_best_score.x + r_score_border.y;
    r_best_score_border.w = r_score_border.w;
    r_best_score_border.h= r_score_border.h;
    r_game_over.x=0;
    r_game_over.y=0;
    r_game_over.w=screen_width;
    r_game_over.h=screen_height;
}    
      * @endcode 
    */
    sdlJeu(char * size , const string &filename);
        /**
     * @brief destructeur de la classe sdlJeu 
    */
    ~sdlJeu();
    int meilleurScore;//!<meilleurScore de type int correspond au meilleur score
    int sdlJeu_score;//!<sdlJeu_score de type int correspond au score dans le jeu

    void sdlBoucle();
    void sdlAff();
    void sdlGameOver();

};
#endif