#ifndef _GALLERY_H
#define _GALLERY_H
#include <SDL.h>
#include<SDL_image.h>
#include<iostream>
struct gallery
{
    SDL_Texture* image_block[7];
    SDL_Color color;
    SDL_Texture* bg_start;
    SDL_Texture* bg_setting;
    SDL_Texture* bg_game;
    SDL_Texture* button;
    SDL_Texture* pause;
    SDL_Texture* tutorial;
    SDL_Texture* gameover;
    gallery(SDL_Renderer* renderer);
    ~gallery();
    void loadImage(SDL_Renderer* renderer);
};


#endif // _GALLERY_H
