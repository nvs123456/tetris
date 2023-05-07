#ifndef _MENU_H
#define _MENU_H
#include<SDL_ttf.h>
#include<SDL.h>
#include<SDL_image.h>

#include<vector>
#include "gallery.h"

#include<bits/stdc++.h>

void render_text(SDL_Renderer* renderer,const char* text,TTF_Font* gFont,int size,int x,int y,SDL_Color);
bool mouse_inside(const SDL_Rect& rect);
bool in_button_pause();
bool resume();
bool quit_game();
bool home();
bool playagain();
int render_menu(TTF_Font *gFont, SDL_Renderer * renderer,gallery& _gallery,int& level,SDL_Event&e);
int render_tutotial(SDL_Renderer* renderer,gallery& _gallery,SDL_Event&e);
int render_gameover(SDL_Renderer* renderer,gallery& _gallery,SDL_Event&e);

#endif // _MENU_H
