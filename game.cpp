#include<iostream>
#include<SDL.h>
#include<vector>
#include<random>
#include<ctime>
#include<set>
#include<string>
#include "obj.h"
#include "my_font.h"
using namespace std;
const int WIDTH=600;
const int HEIGHT=600;
 double delta_time =100.0/3;
SDL_Window* window=NULL;
SDL_Renderer*renderer=NULL;
vector<my_block> vt;
vector<my_block> hinh(7);
my_block chu_L_nguoc(0);
my_block chu_L(1);
my_block chu_Z(2);
my_block chu_Z_nguoc(3);
my_block vuong(4);
my_block chu_T(5);
my_block chu_I(6);
double time_play=0;
int hard=1;
set<int> num;
int randomNum(){
    if(num.size()==7)num.clear();
    int n=rand()%7;
    while(num.count(n)==1)n=rand()%7;
    num.insert(n);
    return n;
}
int row[20];
int main(int argc,char* argv[])
{   srand(time(NULL));
    if(SDL_Init(SDL_INIT_VIDEO)<0){
        std::cout<<"could not init sdl";
        return 1;
    }else{
        window=SDL_CreateWindow("title",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,WIDTH,HEIGHT,SDL_WINDOW_SHOWN);
        renderer=SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
    }
hinh[0]=chu_L_nguoc;
hinh[1]=chu_L;
hinh[2]=chu_Z;
hinh[3]=chu_Z_nguoc;
hinh[4]=vuong;
hinh[5]=chu_T;
hinh [6]=chu_I;
SDL_Rect show_score={310,10,290,70};
SDL_Color text_color={200,0,0};
int score=0;
string s="your score :";
int n=randomNum();
vt.push_back(hinh[n]);
n=randomNum();
bool quit=false;
bool pause=false;
SDL_Event e;
vector<SDL_Rect> next_block(4);
    while(!quit){
        vt.back().handleEvent(e,quit,vt);
        SDL_SetRenderDrawColor(renderer,0,0,0,255);
        SDL_RenderClear(renderer);
        hinh[n].render_next_block(renderer,next_block);
        SDL_Texture * text= CreateTextureFromString(renderer,(s+to_string(score)).c_str(),text_color,200,"basic_font.ttf");
        SDL_RenderCopy(renderer,text,NULL,&show_score);

        SDL_SetRenderDrawColor(renderer,250,0,0,255);
        SDL_RenderDrawLine(renderer,300,0,300,600);
        vt.back().render_all_block(renderer,vt);
        SDL_RenderPresent(renderer);
        SDL_Delay(delta_time);
        time_play+=delta_time;
        if(time_play>=40000*hard) {
                delta_time/=1.15;
                hard++;
        }
        if(!vt.back().down_stop(vt)){
            vt.back().update();
        }else{
            SDL_Delay(300);
            vt.back().handleEvent(e,quit,vt);
            while(!vt.back().down_stop(vt))vt.back().update();
            vt.back().update_row(row);
            for(int i=0;i<20;i++){
                if(row[i]==10){
                    score++;
                    for(int j=0;j<(int)vt.size();j++){
                        vt[j].delete_row(i);
                    }
                    for(int k=i;k>=0;k--){
                        row[k]=row[k-1];
                    }
                }
            }

            vt.push_back(hinh[n]);
            n=randomNum();
            if(vt.back().endgame(vt)){
                quit=true;
            }
        }
        SDL_DestroyTexture(text);

    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
