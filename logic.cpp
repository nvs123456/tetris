#include "logic.h"

int count_row=0;
int kick[4][10] ={  { 0, 0,     -1, 0,  -1,+1,   0,-2,  -1,-2},
                    { 0, 0,     +1, 0,  +1,-1,   0,+2,  +1,+2},
                    { 0, 0,     +1, 0,  +1,+1,   0,-2,  +1,-2},
                    { 0, 0,     -1, 0,  -1,-1,   0,+2,  -1,+2}
};
int kick_I[4][10]={{ 0, 0,  -2, 0,	+1, 0,	-2,-1,	+1,+2},
                    {0, 0,	-1, 0,	+2, 0,	-1,+2,	+2,-1},
                    {0, 0,	+2, 0,  -1, 0,	+2,+1,	-1,-2},
                    {0, 0,	+1, 0,	-2, 0,	+1,-2,	-2,+1}
};
int anti_kick[4][10]={
	 {0, 0,	+1, 0,	+1,+1,	 0,-2,	+1,-2},
	 {0, 0,	+1, 0,	+1,-1,	 0,+2,	+1,+2},
	 {0, 0, -1, 0,	-1,+1,	 0,-2,	-1,-2},
	 {0, 0,	-1, 0,	-1,-1,	 0,+2,	-1,+2}
};
int anti_kick_I[4][10]={
     {0, 0,	-1, 0,	+2, 0,	-1,+2,	+2,-1},
	 {0, 0,	+2, 0,	-1, 0,	+2,+1,	-1,-2},
	 {0, 0,	+1, 0,	-2, 0,	+1,-2,	-2,+1},
	 {0, 0,	-2, 0,	+1, 0,	-2,-1,	+1,+2}

};
game::game(int _level):
    board(20,std::vector<type_block>(10,type_block::none)),
    status(gameRunning),h(20),w(10),step_delay(600/std::sqrt(_level)),blocks_in_row(20,0),clear_row(20,0),disappearing(false),wait(false),holded(false),
    soft_drop(false),pressed_space(false),score(0),line(0),level(_level)
{
    m=Mix_LoadWAV("sound/move.wav");
    c=Mix_LoadWAV("sound/clear.wav");
    for(int i=0;i<3;i++)randomBlock();
    createBlock();
}
game::~game()
{
}
void game::randomBlock()
{
    if(st.size()==7)st.clear();
    int tmp;
    do{
        tmp=rand()%7;
    }while(st.count(tmp)!=0);
    st.insert(tmp);
    if(next.size()<3)next.push_back(tmp);
    else{
        next[0]=next[1];next[1]=next[2];next[2]=tmp;
    }
}
void game::createBlock()
{
    _block.set_block(next[0]);
    pseudo=_block;
    randomBlock();
    increase();
    pressed_space=false;
    holded=false;
}
void game::rotate_clockwise()
{
    decrease();
    int n=_block.pos;
    _block.rotate();

    for(int i=0;i<5;i++){
        for(int j=0;j<4;j++){
            if(_block.m_type==type_block::I){
                pseudo.blocks[j].x=_block.blocks[j].x+kick_I[n][i*2];
                pseudo.blocks[j].y=_block.blocks[j].y-kick_I[n][i*2+1];
            }else {
                pseudo.blocks[j].x=_block.blocks[j].x+kick[n][i*2];
                pseudo.blocks[j].y=_block.blocks[j].y-kick[n][i*2+1];
            }

        }
        if(!collision()){

            pseudo.center.x+=(pseudo.blocks[0].x-_block.blocks[0].x);
            pseudo.center.y+=(pseudo.blocks[0].y-_block.blocks[0].y);
            _block=pseudo;
            increase();
            return;
        }
    }
    _block.anti_rotate();
    pseudo=_block;
    increase();
}
void game::rotate_anti_clockwise()
{
    decrease();
    int n=_block.pos;
    _block.anti_rotate();
    for(int i=0;i<5;i++){
        for(int j=0;j<4;j++){
            if(_block.m_type==type_block::I){
                pseudo.blocks[j].x=_block.blocks[j].x+anti_kick_I[n][i*2];
                pseudo.blocks[j].y=_block.blocks[j].y-anti_kick_I[n][i*2+1];
            }else {
                pseudo.blocks[j].x=_block.blocks[j].x+anti_kick[n][i*2];
                pseudo.blocks[j].y=_block.blocks[j].y-anti_kick[n][i*2+1];
            }
        }
        if(!collision()){
            pseudo.center.x+=(pseudo.blocks[0].x-_block.blocks[0].x);
            pseudo.center.y+=(pseudo.blocks[0].y-_block.blocks[0].y);
            _block=pseudo;
            increase();
            return;
        }
    }
    _block.rotate();
    pseudo=_block;
    increase();
}
void game::move_to_right()
{
    pseudo.move_right();
    if(collision())pseudo.move_left();
    else _block.move_right();
    Mix_PlayChannel(-1,m,0);
}
void game::move_to_left()
{
    pseudo.move_left();
    if(collision())pseudo.move_right();
    else _block.move_left();
    Mix_PlayChannel(-1,m,0);
}
void game::move_down()
{
    decrease();
    pseudo.move_down();
    _block.move_down();
    increase();
}
void game::hard_drop()
{
    decrease();
    while(!collision()){
        pseudo.move_down();
        score+=2;
    }
        pseudo.move_up();
        _block=pseudo;
        increase();
        set_type_board();
        if(!can_clear())createBlock();
}
void game::hold_block()
{
    if((int)hold.size()==0){
        hold.push_back(_block.m_type);
        decrease();
        createBlock();
    }else {
        int tmp=_block.m_type;
        decrease();
        _block.set_block(hold[0]);
        pseudo=_block;
        increase();
        pressed_space=false;
        hold[0]=tmp;

    }
}
void game::update_level()
{
    if(score>1500*level&&level<10){
        level++;step_delay=600/std::sqrt(level);}
}
bool game::collision()
{
    for(int i=0;i<4;i++){
        int x=pseudo.blocks[i].x;
        int y=pseudo.blocks[i].y;
        if(x>=w||x<0||y>=h)return true;
        else if(y>=0&&board[y][x]!=none)return true;
    }
    return false;
}
bool game::stop()
{
    pseudo.move_down();
    if(collision()){
        pseudo.move_up();
        return true;
    }
    pseudo.move_up();
    return false;

}
void game::set_type_board()
{
    for(int i=0;i<4;i++){
        if(_block.blocks[i].y>=0)
        board[_block.blocks[i].y][_block.blocks[i].x]=_block.m_type;
    }
}
void game::decrease()
{
    for(int i=0;i<4;i++){
        blocks_in_row[_block.blocks[i].y]--;
    }
}
void game::increase()
{
    for(int i=0;i<4;i++){
        blocks_in_row[_block.blocks[i].y]++;
    }
}
bool game::can_clear()
{
    for(int i=0;i<20;i++)if(blocks_in_row[i]==10)return true;
    return false;
}
void game::cut()
{
    set_type_board();
    disappearing=true;
    for (int i=0;i<20;i++){
        if(blocks_in_row[i]==10){
            if(clear_row[i]==6){
                    return ;
            }
            clear_row[i]++;
        }
    }
    Mix_PlayChannel(-1,c,0);
}
void game::update()
{
//    for(int i=0;i<20;i++){
//        for(int j=0;j<10;j++){
//            std::cout<<board[i][j]<<' ';
//        }std::cout<<blocks_in_row[i]<<"\n";
//    }
    disappearing=false;
    update_level();
    count_row=0;
    for(int x=0;x<20;x++){
        clear_row[x]=0;

        if(blocks_in_row[x]==10){
            count_row++;
            line++;
            for(int i=x;i>0;i--){
                for(int j=0;j<10;j++){
                    board[i][j]=board[i-1][j];
                    blocks_in_row[i]=blocks_in_row[i-1];
                }
            }

        }
    }
    switch(count_row){
    case 1:
        score+=100*std::sqrt(level);
        break;
    case 2:
        score+=300*std::sqrt(level);
        break;
    case 3:
        score+=500*std::sqrt(level);
        break;
    case 4:
        score+=800*std::sqrt(level);
        break;
    }
    createBlock();
    if(collision()){
        status=gameOver;
        update_high_score();
        return;
    }

}

void game::handleEvent(SDL_Event &e,bool &quit)
{

    while(SDL_PollEvent(&e)>0){
         if(e.type==SDL_QUIT){
            quit=true;
        }
        if(status==gameRunning){
            if(e.type==SDL_KEYDOWN){

                switch(e.key.keysym.sym)
                {
                case SDLK_LEFT:
                    move_to_left();
                    break;
                case SDLK_RIGHT:
                    move_to_right();
                    break;
                case SDLK_UP:
                    rotate_clockwise();
                    break;
                case SDLK_z:
                    rotate_anti_clockwise();
                    break;
                case SDLK_DOWN:
                    if(!stop())soft_drop=true;
                    break;
                case SDLK_SPACE:
                    if(!pressed_space){
                    pressed_space=true;
                    hard_drop();
                    }

                    break;
                case SDLK_c:
                    if(!holded){
                        hold_block();holded=true;}
                    break;
                case SDLK_ESCAPE:
                    status=gamePause;
                }
            }
            else if(e.type==SDL_KEYUP) {
                    if(e.key.keysym.sym==SDLK_DOWN)soft_drop=false;
            }
            else if(e.type==SDL_MOUSEBUTTONDOWN){
                if(in_button_pause()){
                    if(status==gameRunning)status=gamePause;
                }
            }
        }
        else if(status==gamePause){
             if(e.type==SDL_MOUSEBUTTONDOWN){
                if(resume())status=gameRunning;
                if(quit_game()){
                    status=gameQuit;
                    update_high_score();
                    break;
                }
            }
        }
    }
}
void get_high_score(game& _game)
{
    std::ifstream file("high_score.txt");
    if(!file.is_open())exit(-1);
    int s;
    for(int i=0;i<5;i++){
        file>>s;
        _game.high_score[i]=s;
    }
}
void game::update_high_score(){
    if(score>high_score[4]){
        high_score[4]=score;
        std::sort(high_score,high_score+5,std::greater<int>());
        std::ofstream file("high_score.txt");
        if(!file.is_open())exit(-1);
        for(int i=0;i<5;i++){
            file<<high_score[i]<<std::endl;
        }
    }
}
