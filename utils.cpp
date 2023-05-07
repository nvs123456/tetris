#include "utils.h"
const int top=237;
const int bottom=29;
const int size_block=24;
SDL_Rect pause_rect={240,159,234,220};
SDL_Rect rect_image={0,0,size_block,size_block};
SDL_Rect rect_image2={0,0,size_block,size_block};
Block next_block[3];
Block holded_block;
void draw_board(SDL_Renderer *renderer,game _game)
{
    SDL_SetRenderDrawColor(renderer,70,70,70,0);
    for(int i=0;i<_game.w;i++){
        SDL_RenderDrawLine(renderer,top+i*size_block,bottom,top+i*size_block,bottom+_game.h*size_block);
    }
    for(int i=0;i<_game.h;i++){
        SDL_RenderDrawLine(renderer,top,bottom+i*size_block,top+_game.w*size_block,bottom+i*size_block);
    }
}
void init(SDL_Window* &window,SDL_Renderer * &renderer,TTF_Font* &gFont)
{
    SDL_Init(SDL_INIT_EVERYTHING);
    window=SDL_CreateWindow("Tetris",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,714,538,SDL_WINDOW_SHOWN);
    renderer=SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);
    if(TTF_Init()==-1){
        std::cout<<TTF_GetError();
        exit(-1);
    }
    gFont=TTF_OpenFont("font/calibri.TTF",1000);
    Mix_OpenAudio( 44410, MIX_DEFAULT_FORMAT, 2, 1024 ) ;
}
void draw_single_block(game &_game,point &p,SDL_Renderer *renderer,gallery& _gallery,const int& x)
{
    rect_image.x=top+p.x*size_block+x*2;
    rect_image.y=bottom+p.y*size_block+x*2;
    rect_image.w=size_block-x*4;
    rect_image.h=size_block-x*4;
    SDL_RenderCopy(renderer,_gallery.image_block[_game.board[p.y][p.x]],NULL,&rect_image);
}
void draw_next_block(game& _game,gallery& _gallery,SDL_Renderer * renderer)
{
    for(int i=0;i<3;i++){
        next_block[i].set_block(_game.next[i]);
        for(int j=0;j<4;j++){
            rect_image2.x=top+next_block[i].blocks[j].x*size_block+238;
            rect_image2.y=bottom+next_block[i].blocks[j].y*size_block+i*60+64;
            rect_image2.w=size_block;
            rect_image2.h=size_block;
            SDL_RenderCopy(renderer,_gallery.image_block[_game.next[i]],NULL,&rect_image2);
        }
    }
}
void draw_hold_block(game& _game,gallery& _gallery,SDL_Renderer * renderer)
{
    if((int)_game.hold.size()>0){
    holded_block.set_block(_game.hold[0]);
    for(int i=0;i<4;i++){
        rect_image2.x=top+holded_block.blocks[i].x*size_block-230;
        rect_image2.y=bottom+holded_block.blocks[i].y*size_block+75;
        rect_image2.w=size_block;
        rect_image2.h=size_block;
        SDL_RenderCopy(renderer,_gallery.image_block[_game.hold[0]],NULL,&rect_image2);
    }
    }
}
void rendergame(TTF_Font* gFont,game& _game,SDL_Renderer* renderer,gallery& _gallery)
{
    SDL_SetRenderDrawColor(renderer,0,0,0,0);
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer,_gallery.bg_game,NULL,NULL);
    draw_board(renderer,_game);
    if(!_game.disappearing)
    for(int i=0;i<4;i++){
        rect_image.x=top+_game._block.blocks[i].x*size_block;
        rect_image.y=bottom+_game._block.blocks[i].y*size_block;
    if(_game._block.blocks[i].y>=0)
        SDL_RenderCopy(renderer,_gallery.image_block[_game._block.m_type],NULL,&rect_image);
    }

    for(int i=0;i<10;i++){
        for(int j=0;j<20;j++){
            if(_game.board[j][i]!=none){
                point p(i,j);
                draw_single_block(_game,p,renderer,_gallery,_game.clear_row[j]);
            }
        }
    }
    render_text(renderer,std::to_string(_game.score).c_str(),gFont,21,127,353,_gallery.color);
    render_text(renderer,std::to_string(_game.level).c_str(),gFont,21,127,408,_gallery.color);
    render_text(renderer,std::to_string(_game.line).c_str(),gFont,21,127,462,_gallery.color);
    if(_game.status==gamePause){
        SDL_RenderCopy(renderer,_gallery.pause,NULL,&pause_rect);
    }
    draw_hold_block(_game,_gallery,renderer);
    draw_next_block(_game,_gallery,renderer);
    SDL_RenderPresent(renderer);

}

