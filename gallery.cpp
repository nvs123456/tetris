#include "gallery.h"
gallery::gallery(SDL_Renderer* renderer)
{
    loadImage(renderer);
}
 gallery::~gallery()
{
    for(int i=0;i<7;i++)
    SDL_DestroyTexture(image_block[i]);
    SDL_DestroyTexture(bg_game);
    SDL_DestroyTexture(bg_setting);
    SDL_DestroyTexture(bg_start);
    SDL_DestroyTexture(button);
    SDL_DestroyTexture(pause);
    SDL_DestroyTexture(tutorial);
    SDL_DestroyTexture(gameover);
}
void gallery::loadImage(SDL_Renderer* renderer)
{
    SDL_Surface* surface=IMG_Load("image/I.png");
    image_block[0]=SDL_CreateTextureFromSurface(renderer,surface);
    surface=IMG_Load("image/L.png");
    image_block[1]=SDL_CreateTextureFromSurface(renderer,surface);
    surface=IMG_Load("image/J.png");
    image_block[2]=SDL_CreateTextureFromSurface(renderer,surface);
    surface=IMG_Load("image/O.png");
    image_block[3]=SDL_CreateTextureFromSurface(renderer,surface);
    surface=IMG_Load("image/Z.png");
    image_block[4]=SDL_CreateTextureFromSurface(renderer,surface);
    surface=IMG_Load("image/S.png");
    image_block[5]=SDL_CreateTextureFromSurface(renderer,surface);
    surface=IMG_Load("image/T.png");
    image_block[6]=SDL_CreateTextureFromSurface(renderer,surface);
    surface=IMG_Load("image/bg_game.jpg");
    bg_game=SDL_CreateTextureFromSurface(renderer,surface);
    surface=IMG_Load("image/start2.png");
    bg_start=SDL_CreateTextureFromSurface(renderer,surface);
    surface=IMG_Load("image/button2.png");
    button=SDL_CreateTextureFromSurface(renderer,surface);
    surface=IMG_Load("image/tutorial.png");
    tutorial=SDL_CreateTextureFromSurface(renderer,surface);
    surface=IMG_Load("image/pause.png");
    SDL_SetColorKey(surface,SDL_TRUE,SDL_MapRGB(surface->format,255,0,0));
    pause=SDL_CreateTextureFromSurface(renderer,surface);
    surface=IMG_Load("image/gameover.png");
    gameover=SDL_CreateTextureFromSurface(renderer,surface);
    SDL_FreeSurface(surface);
    color={255,255,255};

}
