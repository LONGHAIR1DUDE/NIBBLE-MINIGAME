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



float temps()
{
    return float(SDL_GetTicks()) / CLOCKS_PER_SEC; // conversion des ms en secondes en divisant par 1000
}

// ============= CLASS IMAGE =============== //

Image::Image()
{
    surface = NULL;
    texture = NULL;
    aChange = false;
}

void Image::chargeFichier(const char *nomFichier, SDL_Renderer *renderer)
{
    surface = IMG_Load(nomFichier);
    if (surface == NULL)
    {
        string nfn = string("./") + nomFichier;
        cout << "Error: cannot load " << nomFichier << ". Trying " << nfn << endl;
        surface = IMG_Load(nfn.c_str());
        if (surface == NULL)
        {
            nfn = string("./") + nfn;
            surface = IMG_Load(nfn.c_str());
        }
    }
    if (surface == NULL)
    {
        cout << "Error: cannot load " << nomFichier << endl;
        SDL_Quit();
        exit(1);
    }

    SDL_Surface *surfaceCorrectPixelFormat = SDL_ConvertSurfaceFormat(surface, SDL_PIXELFORMAT_ARGB8888, 0);
    SDL_FreeSurface(surface);
    surface = surfaceCorrectPixelFormat;

    texture = SDL_CreateTextureFromSurface(renderer, surfaceCorrectPixelFormat);
    if (texture == NULL)
    {
        cout << "Error: problem to create the texture of " << nomFichier << endl;
        SDL_Quit();
        exit(1);
    }
    SDL_FreeSurface(surfaceCorrectPixelFormat);
}

void Image::chargeSurface(SDL_Renderer *renderer)
{
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (texture == NULL)
    {
        cout << "Error: problem to create the texture from surface " << endl;
        SDL_Quit();
        exit(1);
    }
}

void Image::dessiner(SDL_Renderer *renderer, int x, int y, int w, int h)
{
    int ok;
    SDL_Rect r;
    r.x = x;
    r.y = y;
    r.w = (w < 0) ? surface->w : w;
    r.h = (h < 0) ? surface->h : h;

    if (aChange)
    {
        ok = SDL_UpdateTexture(texture, NULL, surface->pixels, surface->pitch);
        assert(ok == 0);
        aChange = false;
    }

    ok = SDL_RenderCopy(renderer, texture, NULL, &r);
    assert(ok == 0);
}

SDL_Texture *Image::getTexture() const { return texture; }

void Image::setSurface(SDL_Surface *surf) { surface = surf; }

sdlJeu::sdlJeu(char * size,const string &filename) : jeu(filename)
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
    im_Bonus.chargeFichier("data/fruit1.png", renderer);
    im_Mur.chargeFichier("data/nibble-map.png", renderer);
    im_Cle.chargeFichier("data/cle.png", renderer);
    im_Portail.chargeFichier("data/portail.png", renderer);
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

sdlJeu::~sdlJeu()
{
    if (avecson)
        Mix_Quit();
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void sdlJeu::sdlAff()
{
    //Remplir l'�cran de blanc
    SDL_SetRenderDrawColor(renderer, 255, 255, 204, 255);
    SDL_RenderClear(renderer);
    
    int x, y;
    const Terrain &ter = jeu.getTerrain();
    const Serpent &serp = jeu.getSerpent();
    Bonus bon = jeu.getBonus(0);
    Portail p = jeu.getPortail(0);
    int score = jeu.getScore();
            std::string s = std::to_string(score);
              char const *pchar = s.c_str();
              if(score < 200){font_color.r = 119;font_color.g = 136;font_color.b = 135;}
              	else if(score < 500){font_color.r = 16;font_color.g = 77;font_color.b = 72;}
                  else if(score < 1500){font_color.r = 41;font_color.g = 153;font_color.b = 0;}
                  else if(score < 2500){font_color.r = 255;font_color.g = 126;font_color.b = 0;}
                  else if(score < 3500){font_color.r = 204;font_color.g = 55;font_color.b = 35;}
                  else if(score < 7500){font_color.r = 236;font_color.g = 25;font_color.b = 231;}
                  else if(score > 7500){font_color.r = 31;font_color.g = 25;font_color.b = 236;}
	score_im.setSurface(TTF_RenderText_Solid(pdark,pchar,font_color));
	score_im.chargeSurface(renderer);
    int bestscore = jeu.stockerMeilleurScore();
    std::string sc = std::to_string(bestscore);
    best_col.r =102;best_col.g=0;best_col.b =51;
    std::string be = "Best :";
    std::string combo = be.append(sc);
    char const *b = combo.c_str();
    best_score_im.setSurface(TTF_RenderText_Solid(pdark,b,best_col));
    best_score_im.chargeSurface(renderer);
    // Afficher les sprites des murs et des pieces
    for (x = 0; x < ter.getDimX(); ++x)
        for (y = 0; y < ter.getDimY(); ++y)
            if (ter.getXY(x, y) == '#')
                im_Mur.dessiner(renderer, x * TAILLE_SPRITE, y * TAILLE_SPRITE_Y, TAILLE_SPRITE, TAILLE_SPRITE_Y);
            else if (ter.getXY(x, y) == '.')
                im_Piece.dessiner(renderer, x * TAILLE_SPRITE, y * TAILLE_SPRITE_Y, TAILLE_SPRITE, TAILLE_SPRITE_Y);
            else if (ter.getXY(x, y) == 'i')
                im_Interrupteur.dessiner(renderer, x * TAILLE_SPRITE, y * TAILLE_SPRITE_Y, TAILLE_SPRITE, TAILLE_SPRITE_Y);
            else if (ter.getXY(x, y) == 'b')
                im_Bonus.dessiner(renderer, x * TAILLE_SPRITE, y * TAILLE_SPRITE_Y, TAILLE_SPRITE, TAILLE_SPRITE_Y);
            else if (ter.getXY(x, y) == 'c')
                im_Cle.dessiner(renderer, x * TAILLE_SPRITE, y * TAILLE_SPRITE_Y, TAILLE_SPRITE, TAILLE_SPRITE_Y);
    //Afficher les sprites des bonus

    for (int j = 0; j < jeu.getNbBonus(); j++)
    {
        im_Bonus.dessiner(renderer, bon.getX() * TAILLE_SPRITE, bon.getY() * TAILLE_SPRITE_Y, TAILLE_SPRITE, TAILLE_SPRITE_Y);
    }
    // Afficher le sprite de Serpent
    im_TeteSerpent.dessiner(renderer, serp.getTete().x * TAILLE_SPRITE, serp.getTete().y * TAILLE_SPRITE_Y, TAILLE_SPRITE, TAILLE_SPRITE_Y);
    int a = serp.getTailleSerpent();
    for (int i = 1; i < a - 1; ++i)
    {
        im_CorpsSerpent.dessiner(renderer, serp.getCorps(i).x * TAILLE_SPRITE, serp.getCorps(i).y * TAILLE_SPRITE_Y, TAILLE_SPRITE, TAILLE_SPRITE_Y);
    }
    if (serp.getCorps(a - 2).x == serp.getCorps(a - 1).x - 1)
    {
        im_QueueSerpent.chargeFichier("data/tail-right.png", renderer);
    }
    else if (serp.getCorps(a - 2).x == serp.getCorps(a - 1).x + 1)
    {
        im_QueueSerpent.chargeFichier("data/tail-left.png", renderer);
    }
    else if (serp.getCorps(a - 2).y == serp.getCorps(a - 1).y - 1)
    {
        im_QueueSerpent.chargeFichier("data/tail.png", renderer);
    }
    else if (serp.getCorps(a - 2).y == serp.getCorps(a - 1).y + 1)
    {
        im_QueueSerpent.chargeFichier("data/tail-down.png", renderer);
    }

    im_QueueSerpent.dessiner(renderer, serp.getCorps(a - 1).x * TAILLE_SPRITE, serp.getCorps(a - 1).y * TAILLE_SPRITE_Y, TAILLE_SPRITE, TAILLE_SPRITE_Y);

    im_Portail.dessiner(renderer, p.getPortail1().x * TAILLE_SPRITE, p.getPortail1().y * TAILLE_SPRITE_Y, TAILLE_SPRITE, TAILLE_SPRITE_Y);
    im_Portail.dessiner(renderer, p.getPortail2().x * TAILLE_SPRITE, p.getPortail2().y * TAILLE_SPRITE_Y, TAILLE_SPRITE, TAILLE_SPRITE_Y);
    // Ecrire un titre par dessus
     SDL_SetRenderDrawColor( renderer, 0, 0, 153, 0 );
    SDL_RenderFillRect( renderer, &r_score );
         SDL_SetRenderDrawColor( renderer,153, 255, 153,0 );
    SDL_RenderFillRect( renderer, &r_score_border );
         SDL_SetRenderDrawColor( renderer, 139, 0, 0, 0 );
    SDL_RenderFillRect( renderer, &r_best_score );
         SDL_SetRenderDrawColor( renderer,20, 219, 180,0 );
    SDL_RenderFillRect( renderer, &r_best_score_border );
    SDL_Rect positionTitre;
    positionTitre.x = screen_width/2 - screen_width/30;
    positionTitre.y = 7*screen_height/8;
    positionTitre.w = screen_width/15;
    positionTitre.h = screen_height/15;
    SDL_RenderCopy(renderer, font_im.getTexture(), NULL, &positionTitre);
        SDL_Rect posTitre;
    posTitre.x = screen_width/2 - screen_width/54;
    posTitre.y = 0;
    posTitre.w = screen_width/27;
    posTitre.h = TAILLE_SPRITE_Y;
    SDL_RenderCopy(renderer, score_im.getTexture(), NULL, &posTitre);
    SDL_Rect posBest;
    posBest.x = r_best_score_border.x ;
    posBest.y = 0;
    posBest.w = r_best_score_border.w;
    posBest.h = r_score.h;
    SDL_RenderCopy(renderer, best_score_im.getTexture(), NULL, &posBest);

       
}
void sdlJeu::sdlGameOver()
{  
        
    SDL_SetRenderDrawColor(renderer, 204, 255, 255, 2);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

    SDL_RenderFillRect( renderer, &r_game_over ); 
      int score = jeu.getScore();
            std::string s = std::to_string(score);
            std::string a = "Your Score : ";
            std::string r = a.append(s);
              char const *pchar = r.c_str();
              	font_color.r = 251;font_color.g = 0;font_color.b = 255;
	score_up_im.setSurface(TTF_RenderText_Solid(pdark,pchar,font_color));
	score_up_im.chargeSurface(renderer);
    //im_GameOver.dessiner(renderer,0,0,screen_width,screen_height);
    game_color.r = 43;game_color.g = 91;game_color.b = 196;
    im_GameOver.setSurface(TTF_RenderText_Solid(player,"Game Over",game_color));
    im_GameOver.chargeSurface(renderer);
    
    SDL_Rect posGame;
    posGame.x = screen_width/2 - screen_width/8;
    posGame.y = screen_height/7;
    posGame.w = screen_width/4;
    posGame.h = screen_height/5;
    SDL_RenderCopy(renderer, im_GameOver.getTexture(), NULL, &posGame);

        
    SDL_Rect posScore;
    posScore.x = screen_width/4 - screen_width/10;
    posScore.y = screen_height/3;
    posScore.w = screen_width/5;
    posScore.h = screen_height/10;
    SDL_RenderCopy(renderer, score_up_im.getTexture(), NULL, &posScore);


    int bestscore = jeu.stockerMeilleurScore();
    std::string sc = std::to_string(bestscore);
    best_col.r =102;best_col.g=0;best_col.b =51;
    std::string be = "Best score : ";
    std::string combo = be.append(sc);
    char const *b = combo.c_str();
    over_best_im.setSurface(TTF_RenderText_Solid(pdark,b,font_color));
    over_best_im.chargeSurface(renderer);
            
    
    SDL_Rect posBest_over;
    posBest_over.x = 3*screen_width/4 - screen_width/10;
    posBest_over.y = screen_height/3;
    posBest_over.w = screen_width/5;
    posBest_over.h = screen_height/10;
    SDL_RenderCopy(renderer, over_best_im.getTexture(), NULL, &posBest_over);





}
void sdlJeu::sdlBoucle()
{
    SDL_Event events;
    bool quit = false;
    bool etat = true;
    bool ok = true;
    
   
   Mix_PlayChannel(-1,son,-1);
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
                    
                    im_CorpsSerpent.chargeFichier("data/snake-tex.png",renderer); 
                    
					if(jeu.getSerpent().getMouv() && jeu.getSerpent().getDirection().x == 0 && jeu.getSerpent().getDirection().y == -1)
                    {im_TeteSerpent.chargeFichier("data/snake-head.png",renderer);}
                     else if(!jeu.getSerpent().getMouv() && jeu.getSerpent().getDirection().x == 0 && jeu.getSerpent().getDirection().y == 1)
                    {im_TeteSerpent.chargeFichier("data/snake-head-down.png",renderer);}  
                    break;
				case SDLK_s:
					jeu.actionClavier('s');
                     
                    im_CorpsSerpent.chargeFichier("data/snake-tex.png",renderer);
                    if(jeu.getSerpent().getMouv() && jeu.getSerpent().getDirection().x == 0 && jeu.getSerpent().getDirection().y == 1)
                    {im_TeteSerpent.chargeFichier("data/snake-head-down.png",renderer);}    
                     else if(!jeu.getSerpent().getMouv() && jeu.getSerpent().getDirection().x == 0 && jeu.getSerpent().getDirection().y == -1)
                    {im_TeteSerpent.chargeFichier("data/snake-head.png",renderer);}  
                    break;
				case SDLK_q:
				    jeu.actionClavier('q');
                    
                    if(jeu.getSerpent().getMouv() && jeu.getSerpent().getDirection().x == -1 && jeu.getSerpent().getDirection().y == 0)
                    {im_CorpsSerpent.chargeFichier("data/snake-tex-right.png",renderer);
					im_TeteSerpent.chargeFichier("data/snake-head-left.png",renderer);
                    }
                    else if(!jeu.getSerpent().getMouv() && jeu.getSerpent().getDirection().x == 1 && jeu.getSerpent().getDirection().y == 0)
                    {im_CorpsSerpent.chargeFichier("data/snake-tex-right.png",renderer);
					im_TeteSerpent.chargeFichier("data/snake-head-right.png",renderer);
                    }
                    break;
				case SDLK_d:
					jeu.actionClavier('d');
                    if(jeu.getSerpent().getMouv() && jeu.getSerpent().getDirection().x == 1 && jeu.getSerpent().getDirection().y == 0)
                    {im_CorpsSerpent.chargeFichier("data/snake-tex-right.png",renderer);
					im_TeteSerpent.chargeFichier("data/snake-head-right.png",renderer);
                    }
                    else if(!jeu.getSerpent().getMouv() && jeu.getSerpent().getDirection().x == -1 && jeu.getSerpent().getDirection().y == 0)
                    {im_CorpsSerpent.chargeFichier("data/snake-tex-right.png",renderer);
					im_TeteSerpent.chargeFichier("data/snake-head-left.png",renderer);
                    }
                    break;
                case SDL_SCANCODE_ESCAPE:
                case SDLK_ESCAPE:
                quit = true;
                    break;
                default:
                    break;
                }

                //if (avecson)
                //  Mix_PlayChannel(-1,son,0);
            }
        }

        // on affiche le jeu sur le buffer cach�
        sdlAff();

        // on permute les deux buffers (cette fonction ne doit se faire qu'une seule fois dans la boucle)
        SDL_RenderPresent(renderer);
        
    } while (!quit && ok);
sdlJeu_score = jeu.getScore();
meilleurScore = jeu.stockerMeilleurScore();
cout<<endl<<jeu.stockerMeilleurScore()<<endl;
quit = false;
    
    do
    {
        sdlGameOver();
        while (SDL_PollEvent(&events))
        {
            if (events.type == SDL_QUIT)
                quit = true; // Si l'utilisateur a clique sur la croix de fermeture
            else if (events.type == SDL_KEYDOWN)
            {
                switch (events.key.keysym.sym)
                {
                case SDL_SCANCODE_ESCAPE:
                case SDLK_ESCAPE:
                    quit = true;
                    break;
				
                default:
                    break;
                }
            }
        }
        SDL_RenderPresent(renderer);

    } while (!quit);
}
