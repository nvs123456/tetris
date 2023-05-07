#include<SDL.h>
#include<iostream>
#include<vector>
using namespace std;
using std::vector;
const int step=3;
class my_block
{
private:
    SDL_Rect mBlock[4];
    SDL_Point center;
    SDL_Color mColor;
     int edge=30;
public:
    my_block(){}
//    void operator=()
    my_block(int x)
    {switch(x){
        case 0:
        mBlock[0]={120,0,30,30};
        mBlock[1]={120,30,30,30};
        mBlock[2]={150,30,30,30};
        mBlock[3]={180,30,30,30};
        mColor={255,153,51};
        center.x=mBlock[2].x+edge/2;
        center.y=mBlock[2].y+edge/2;
        break;
        case 1:
        mBlock[0]={180,0,30,30};
        mBlock[1]={120,30,30,30};
        mBlock[2]={150,30,30,30};
        mBlock[3]={180,30,30,30};
        mColor={0,0,255};
        center.x=mBlock[2].x+edge/2;
        center.y=mBlock[2].y+edge/2;
        break;
        case 2:
        mBlock[0]={120,0,30,30};
        mBlock[1]={150,0,30,30};
        mBlock[2]={150,30,30,30};
        mBlock[3]={180,30,30,30};
        mColor={255,0,0};
        center.x=mBlock[2].x+edge/2;
        center.y=mBlock[2].y+edge/2;
        break;
        case 3:
        mBlock[0]={150,0,30,30};
        mBlock[1]={120,30,30,30};
        mBlock[2]={150,30,30,30};
        mBlock[3]={180,0,30,30};
        mColor={0,255,0};
        center.x=mBlock[2].x+edge/2;
        center.y=mBlock[2].y+edge/2;
        break;
        case 4:
        mBlock[0]={120,0,30,30};
        mBlock[1]={120,30,30,30};
        mBlock[2]={150,30,30,30};
        mBlock[3]={150,0,30,30};
        mColor={255,255,0};
        center.x=(mBlock[0].x+mBlock[1].x+mBlock[2].x+mBlock[3].x)/4+15;
        center.y=(mBlock[0].y+mBlock[1].y+mBlock[2].y+mBlock[3].y)/4+15;
        break;
        case 5:
        mBlock[0]={150,0,30,30};
        mBlock[1]={120,30,30,30};
        mBlock[2]={150,30,30,30};
        mBlock[3]={180,30,30,30};
        mColor={255,0,255};
        center.x=mBlock[2].x+edge/2;
        center.y=mBlock[2].y+edge/2;
        break;
        case 6:
        mBlock[0]={120,0,30,30};
        mBlock[1]={150,0,30,30};
        mBlock[2]={180,0,30,30};
        mBlock[3]={210,0,30,30};
        mColor={0,255,255};
        center.x=mBlock[2].x;
        center.y=mBlock[2].y;
        break;



        }

    }
    // MOVE di chuyen, STAND la moc de so sanh
    bool right(SDL_Rect &MOVE,SDL_Rect &STAND){
        if(MOVE.y>STAND.y-MOVE.h&&MOVE.y<STAND.y+STAND.h&&MOVE.x>=STAND.x-STAND.w&&MOVE.x<=STAND.x)return true;
        return false;
    }
    bool left(SDL_Rect &MOVE,SDL_Rect &STAND){
        if(MOVE.y>STAND.y-MOVE.h&&MOVE.y<STAND.y+STAND.h&&MOVE.x<=STAND.x+STAND.w&&MOVE.x>=STAND.x)return true;
        return false;
    }
    bool down(SDL_Rect &MOVE,SDL_Rect &STAND){
         if(MOVE.x>STAND.x-MOVE.w&&MOVE.x<STAND.x+STAND.w&&MOVE.y==STAND.y-MOVE.h)return true;
        return false;
    }
    bool cannot_move_left( my_block& other)
    {
        for(int i=0;i<4;i++){
            for(int j=0;j<4;j++){
                if(left(mBlock[i],other.mBlock[j]))return true;
            }
        }
        return false;
    }
    bool cannot_move_right( my_block& other)
    {
        for(int i=0;i<4;i++){
            for(int j=0;j<4;j++){
                if(right(mBlock[i],other.mBlock[j]))return true;
            }
        }
        return false;
    }
    bool cannot_move_down( my_block& other)
    {
        for(int i=0;i<4;i++){
            for(int j=0;j<4;j++){
                if(down(mBlock[i],other.mBlock[j])){
                        return true;}
            }
        }
        return false;
    }
    bool left_stop(vector<my_block> vt)
    {
        for(int i=0;i<4;i++){
            if(mBlock[i].x==0)return true;
        }
        for(int i=0;i<(int)vt.size()-1;i++){
            if(cannot_move_left(vt[i]))return true;
        }
        return false;
    }
    bool right_stop(vector<my_block> vt)
    {
        for(int i=0;i<4;i++){
            if(mBlock[i].x==270)return true;
        }
        for(int i=0;i<(int)vt.size()-1;i++){
            if(cannot_move_right(vt[i]))return true;
        }
        return false;
    }
    bool down_stop(vector<my_block> vt)
    {
        for(int i=0;i<4;i++){
            if(mBlock[i].y==570)return true;
        }
        for(int i=0;i<(int)vt.size()-1;i++){
            if(cannot_move_down(vt[i])){
                    return true;}
        }
        return false;
    }

    bool endgame(vector<my_block> vt)
    {
        if(vt.back().down_stop(vt)){
            for(int i=0;i<4;i++){
                if(mBlock[i].y==0)return true;
            }
        }
        return false;
    }
    void move_right()
    {
        for(int i=0;i<4;i++){
            mBlock[i].x+=edge;
        }
        center.x+=edge;
    }
    void move_left()
    {
        for(int i=0;i<4;i++){
            mBlock[i].x-=edge;
        }
        center.x-=edge;
    }
    void rotate_block_nguoc(vector<my_block>vt)
    {
        for(int i=0;i<4;i++){
            mBlock[i].x+=edge;
            int cos=mBlock[i].x-center.x;
            int sin=mBlock[i].y-center.y;
            mBlock[i].x=sin+center.x;
            mBlock[i].y=-cos+center.y;
        }
    }
    void rotate_block(vector<my_block>vt)
    {
        for(int i=0;i<4;i++){
            mBlock[i].y+=edge;
            int cos=mBlock[i].x-center.x;
            int sin=mBlock[i].y-center.y;
            mBlock[i].x=-sin+center.x;
            mBlock[i].y=cos+center.y;
        }
        if(left_stop(vt)&&right_stop(vt))rotate_block_nguoc(vt);
        for(int i=0;i<4;i++){
            while(mBlock[i].x>270){
                move_left();
            }
        }
        for(int i=0;i<4;i++){
            if(mBlock[i].x<0)
            {
                move_right();
            }
        }
        for(int i=0;i<4;i++){
        }

    }

    void delete_row(int r){
        for(int i=0;i<4;i++){
            if(mBlock[i].y==r*edge){
                mBlock[i].w=0;
                mBlock[i].h=0;
            }
            if(mBlock[i].y<=r*edge)mBlock[i].y+=edge;
        }
    }
    void update()
    {
        for(int i=0;i<4;i++){
            mBlock[i].y+=step;
        }
        center.y+=step;

    }
    void update_row(int row[])
    {
        for(int i=0;i<4;i++){
            row[mBlock[i].y/30]++;
        }
    }
    void handleEvent(SDL_Event &e,bool &quit,vector<my_block> &vt){
        while(SDL_PollEvent(&e)>0){
            if(e.type== SDL_QUIT){
                quit=true;
            }else if(e.type==SDL_KEYDOWN){
                switch(e.key.keysym.sym)
                {
                case SDLK_d:
                    if(!(vt.back().right_stop(vt))){
                        vt.back().move_right();
                    }
                    break;
                case SDLK_a:
                    if(!vt.back().left_stop(vt)){
                        vt.back().move_left();
                    }
                    break;
                case SDLK_s:
                    if(!vt.back().down_stop(vt)){
                    vt.back().rotate_block(vt);

                    }
                    break;
                case SDLK_SPACE:
                    while(!vt.back().down_stop(vt)){
                        vt.back().update();
                    }
                }
            }
        }
    }

    void render_next_block(SDL_Renderer * renderer,vector<SDL_Rect> &v)
    {
        SDL_SetRenderDrawColor(renderer,mColor.r,mColor.g,mColor.b,255);
        for(int i=0;i<4;i++){
            v[i].x=mBlock[i].x+220;
            v[i].y=mBlock[i].y+120;
            v[i].w=mBlock[i].w;
            v[i].h=mBlock[i].h;
            SDL_RenderDrawRect(renderer,&v[i]);
            SDL_RenderFillRect(renderer,&v[i]);
        }

    }
    void render_all_block(SDL_Renderer *renderer,vector<my_block> &vt)
    {
        for(auto x:vt){
            SDL_SetRenderDrawColor(renderer,x.mColor.r,x.mColor.g,x.mColor.b,255);
            for(int i=0;i<4;i++){
                if(x.mBlock[i].w==0)continue;
                SDL_RenderDrawRect(renderer,&x.mBlock[i]);
                SDL_RenderFillRect(renderer,&x.mBlock[i]);
            }
        }
    }
};
