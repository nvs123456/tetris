#include "menu.h"
SDL_Rect pause_button={640,473,61,55};
SDL_Rect resume_button={286,253,144,30};
SDL_Rect tutotial_button={336,444,40,30};
SDL_Rect quit_button={286,303,144,30};
SDL_Rect done_button={322,466,75,30};
SDL_Rect home_button={275,267,35,29};
SDL_Rect playagain_button={392,267,40,29};
SDL_Rect over_rect={236,212,242,113};

SDL_Color color[2]={{255,255,255},{100,100,100}};
SDL_Rect pos[2]={{276,193,161,35},{284,245,144,34}};
SDL_Rect rect_menu;
bool mouse_inside(const SDL_Rect& rect)
{
    int x;int y;
    SDL_GetMouseState(&x,&y);
    return x>rect.x&&x<rect.x+rect.w&&y<rect.y+rect.h&&y>rect.y;
}
bool in_button_pause(){
    return mouse_inside(pause_button);
}
bool resume()
{
    return mouse_inside(resume_button);
}

bool quit_game()
{
    return mouse_inside(quit_button);
}
bool home(){return mouse_inside(home_button);};
bool playagain(){return mouse_inside(playagain_button);};
void render_text(SDL_Renderer* renderer,const char* s,TTF_Font* gFont,int size,int center_x,int center_y,SDL_Color color)
{
    SDL_Surface* surface=TTF_RenderText_Solid(gFont,s,color);
    rect_menu.h=size;
    rect_menu.w=surface->w/(surface->h/size);
    rect_menu.x=center_x-rect_menu.w/2;
    rect_menu.y=center_y-rect_menu.h/2;
    if(surface==NULL){
        std::cout<<IMG_GetError();
    }
    SDL_Texture* texture=SDL_CreateTextureFromSurface(renderer,surface);
    SDL_FreeSurface(surface);
    SDL_RenderCopy(renderer,texture,NULL,&rect_menu);
    SDL_DestroyTexture(texture);
}
int render_menu(TTF_Font* gFont,SDL_Renderer* renderer,gallery& _gallery,int &level,SDL_Event&e)
{
    while(true){
    while(SDL_PollEvent(&e)>0){

        switch (e.type){
        case SDL_QUIT:
            return 0;break;
        case SDL_MOUSEBUTTONDOWN:
            int x;int y;
            SDL_GetMouseState(&x,&y);
            if(mouse_inside(pos[0])){
                return 2;
            }
            else if(mouse_inside(pos[1])){
                level++;
                if(level>10)level=1;
            }else if(mouse_inside(tutotial_button)){
               return 3;
            }
        }
    }
    SDL_RenderCopy(renderer,_gallery.bg_start,NULL,NULL);

    std::ifstream file("high_score.txt");
    if(!file.is_open())exit(-1);
    else {
        std::string s;
        for(int i=0;i<5;i++){
            file>>s;
            render_text(renderer,s.c_str(),gFont,16,356,327+i*22,color[0]);
        }
    SDL_RenderCopy(renderer,_gallery.button,NULL,&pos[0]);
    SDL_RenderCopy(renderer,_gallery.button,NULL,&pos[1]);
    render_text(renderer,"PLAY",gFont,25,356,210,color[0]);
    render_text(renderer,("LEVEL :"+std::to_string(level)).c_str(),gFont,20,356,261,color[0]);
    }
    SDL_Delay(1);
    SDL_RenderPresent(renderer);


    }
    return 1;
}
int render_tutotial(SDL_Renderer* renderer,gallery& _gallery,SDL_Event&e)
{
    while(true){
        while(SDL_PollEvent(&e)>0){
            if(e.type==SDL_MOUSEBUTTONDOWN){
                if(mouse_inside(done_button))return 1;
            }
        }
        SDL_RenderCopy(renderer,_gallery.tutorial,NULL,NULL);
        SDL_RenderPresent(renderer);
    }
    return 3;
}
int render_gameover(SDL_Renderer* renderer,gallery& _gallery,SDL_Event&e)
{
    while(true){
        while(SDL_PollEvent(&e)){
            if(e.type==SDL_MOUSEBUTTONDOWN){
                if(mouse_inside(home_button))return 1;
                else if(mouse_inside(playagain_button))return 2;
            }
        }
        SDL_RenderCopy(renderer,_gallery.gameover,NULL,&over_rect);
        SDL_RenderPresent(renderer);
    }
    return 4;



}
