#ifndef BLOCK_H
#define BLOCK_H
#include "position.h"

enum type_block
{
    I,L,J,O,Z,S,T,none
};
struct Block
{
    point blocks[4];
    point center;
    type_block m_type;
    int pos;
    Block();
    void set_block(int t);
    void rotate();
    void anti_rotate();
    void move_right();
    void move_left();
    void move_down();
    void move_up();
    Block& operator= (const Block& other);
};
#endif // BLOCK_H

