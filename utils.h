#ifndef UTILS_H
#define UTILS_H
#include<SDL.h>
#include<SDL_ttf.h>
#include<SDL_image.h>
#include<SDL_mixer.h>
#include "logic.h"
#include<iostream>
#include "menu.h"
#include"gallery.h"

void draw_board(SDL_Renderer *renderer,game _game);

void init(SDL_Window* &window,SDL_Renderer * &renderer,TTF_Font* &gFont);

void draw_single_block(game &_game,point &p,SDL_Renderer *renderer,gallery& _gallery,const int&x);

void draw_next_block(game& _game,gallery& _gallery,SDL_Renderer * renderer);

void draw_hold_block(game& _game,gallery& _gallery,SDL_Renderer * renderer);

void rendergame(TTF_Font* gFont,game& _game,SDL_Renderer* renderer,gallery& _gallery);

#endif // UTILS_H
