#include<SDL.h>
#include<SDL_ttf.h>
#include<iostream>
SDL_Texture* CreateTextureFromString(SDL_Renderer* renderer,const char* text,SDL_Color text_color,int ptsize ,const char * file)
{
    SDL_Texture * gTexture;

    if(TTF_Init()<0){
        std::cout<<"could not initial ttf"<< TTF_GetError()<<std::endl;
        exit(-1);
    }else
    {
        TTF_Font *gFont=TTF_OpenFont(file,ptsize);
        if(gFont==NULL){
            std::cout<<"could not create font"<<TTF_GetError()<<std::endl;
            exit(-1);
        }else{
            SDL_Surface *gSurface=TTF_RenderText_Solid(gFont,text,text_color);
            if(gSurface==NULL){
                std::cout<<"could not create surface"<<TTF_GetError()<<std::endl;
                exit(-1);
            }else {
                 gTexture=SDL_CreateTextureFromSurface(renderer,gSurface);
                 SDL_FreeSurface(gSurface);
            }

        }
    }
    return gTexture;
}

