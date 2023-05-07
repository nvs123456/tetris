#ifndef LOGIC_H
#define LOGIC_H
#include<bits/stdc++.h>
#include<set>
#include<SDL.h>
#include "block.h"
#include "position.h"
#include <vector>
#include<fstream>
#include<algorithm>
#include<iostream>
#include<SDL_mixer.h>
#include<cmath>
#include "menu.h"
enum gamestatus
{
    gameOver,gameRunning,gamePause,gameQuit
};

struct game
{
    Block _block;
    Block pseudo;
    std::vector<std::vector<type_block>>board;
    gamestatus status;
    int h;int w;int step_delay;
    std::unordered_set<int> st;
    std::vector<int> next;
    std::vector<int>hold;
    std::vector<int> blocks_in_row;
    std::vector<int> clear_row;
    bool disappearing;
    bool wait;
    bool holded;
    bool soft_drop;
    bool pressed_space;
    int score;
    int line;
    int level;

    int high_score[5];
    Mix_Chunk* m;
    Mix_Chunk* c;
    game(int level);
    ~game();
    bool collision();
    bool stop();

    void set_type_board();
    void randomBlock();
    void createBlock();
    void hold_block();
    void handleEvent(SDL_Event &e,bool &quit);
    void cut();
    bool can_clear();
    void decrease();
    void increase();
    void update();
    void rotate_clockwise();
    void rotate_anti_clockwise();
    void move_to_left();
    void move_to_right();
    void move_down();
    void hard_drop();
    void update_level();
    void update_high_score();

};
void get_high_score(game& _game);
#endif // LOGIC_H
