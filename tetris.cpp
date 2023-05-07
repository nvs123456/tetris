#include<SDL.h>
#include<SDL_ttf.h>
#include <bits/stdc++.h>
#include<ctime>
#include "logic.h"
#include "utils.h"
#include "menu.h"
enum Screen
{
    QUIT_SCREEN,MAIN_MENU,GAME_SCREEN,TUTORIAL_SCREEN,GAMEOVER_SCREEN
};
int main(int argc, char *argv[])
{
    srand(time(0));
    SDL_Window * window=nullptr;
    SDL_Renderer* renderer=nullptr;
    TTF_Font * gFont=nullptr;
    init(window,renderer,gFont);
    SDL_Event e;
    bool quit=false;
    int _end;
    gallery gallery(renderer);
    int level=1;
    int screen=Screen::MAIN_MENU;
    while(!quit){
        switch(screen){
        case QUIT_SCREEN:
            quit=true;
            break;
        case MAIN_MENU:
            screen=render_menu(gFont,renderer,gallery,level,e);
            break;

        case GAME_SCREEN:
            {game game(level);
            get_high_score(game);
            int start=SDL_GetTicks();
            int start_stop;
            int end_stop;
            int start_cut=0;
            int end_cut;
            while(!quit&&game.status!=gamestatus::gameOver&&game.status!=gameQuit){
                _end=SDL_GetTicks();
                end_stop=SDL_GetTicks();
                if(_end-start>=game.step_delay){
                    if(game.status!=gamePause&&!game.stop()){
                        game.move_down();
                        start=_end;
                    }
                }
                game.handleEvent(e,quit);
                if(game.stop()){
                    if(game.can_clear()){
                        end_cut=SDL_GetTicks();
                        if(end_cut-start_cut>30){
                            game.cut();
                            start_cut=end_cut;
                        }
                    }
                    if(!game.wait){
                        start_stop=SDL_GetTicks();
                        game.wait=true;
                    }else if(end_stop-start_stop>=500){
                        game.set_type_board();
                        game.update();
                        game.wait=false;
                    }
                }else if(game.soft_drop)game.move_down();
                rendergame(gFont,game,renderer,gallery);
                SDL_Delay(1);
                SDL_RenderPresent(renderer);
            }
            if(game.status==gameQuit)screen=MAIN_MENU;
            else
            screen=GAMEOVER_SCREEN;
            break;
            }
        case TUTORIAL_SCREEN:
            screen=render_tutotial(renderer,gallery,e);
            break;
        case GAMEOVER_SCREEN:
            screen=render_gameover(renderer,gallery,e);
            break;
        }
    }
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    return 0;
}
