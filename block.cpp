#include "block.h"
#include<iostream>
Block::Block()
{

}
void Block::set_block(int t)
{
    pos=0;
    switch(t)
    {
    case 0 :
        blocks[0].set_position(3,0);
        blocks[1].set_position(4,0);
        blocks[2].set_position(5,0);
        blocks[3].set_position(6,0);
        center.set_position(5,1);
        m_type=type_block::I;
        break;
    case 1 :
        blocks[0].set_position(3,1);
        blocks[1].set_position(4,1);
        blocks[2].set_position(5,1);
        blocks[3].set_position(5,0);
        center.set_position(4.5,1.5);
        m_type=type_block::L;
        break;
    case 2 :
        blocks[0].set_position(3,0);
        blocks[1].set_position(3,1);
        blocks[2].set_position(4,1);
        blocks[3].set_position(5,1);
        center.set_position(4.5,1.5);
        m_type=type_block::J;
        break;
    case 3 :
        blocks[0].set_position(4,0);
        blocks[1].set_position(5,0);
        blocks[2].set_position(5,1);
        blocks[3].set_position(4,1);
        center.set_position(5,1);
        m_type=type_block::O;
        break;
    case 4 :
        blocks[0].set_position(3,0);
        blocks[1].set_position(4,0);
        blocks[2].set_position(4,1);
        blocks[3].set_position(5,1);
        center.set_position(4.5,1.5);
        m_type=type_block::Z;
        break;
    case 5 :
        blocks[0].set_position(3,1);
        blocks[1].set_position(4,1);
        blocks[2].set_position(4,0);
        blocks[3].set_position(5,0);
        center.set_position(4.5,1.5);
        m_type=type_block::S;
        break;
    case 6 :
        blocks[0].set_position(3,1);
        blocks[1].set_position(4,1);
        blocks[2].set_position(4,0);
        blocks[3].set_position(5,1);
        center.set_position(4.5,1.5);
        m_type=type_block::T;
        break;
    }
}
void Block::rotate()
{
    for(int i=0;i<4;i++){
        blocks[i].y++;
        double cos=blocks[i].x-center.x;
        double sin=blocks[i].y-center.y;
        blocks[i].x=-sin+center.x;
        blocks[i].y=cos+center.y;
    }
    if(pos==3)pos=0;else pos++;
}
void Block::anti_rotate()
{
    for(int i=0;i<4;i++){
        blocks[i].x++;
        double cos=blocks[i].x-center.x;
        double sin=blocks[i].y-center.y;
        blocks[i].x=sin+center.x;
        blocks[i].y=-cos+center.y;
    }
    if(pos==0)pos=3;else pos--;

}
void Block::move_right()
{

    for(int i=0;i<4;i++){
        blocks[i].x++;
    }
    center.x++;
}
void Block::move_left()
{
    for(int i=0;i<4;i++){
        blocks[i].x--;
    }
    center.x--;
}
void Block::move_down()
{
    for(int i=0;i<4;i++){
        blocks[i].y++;
    }
    center.y++;
}
void Block::move_up()
{
    for(int i=0;i<4;i++){
        blocks[i].y--;
    }
    center.y--;
}
Block& Block::operator=(const Block& other)
{
    for(int i=0;i<4;i++){
        this->blocks[i].x=other.blocks[i].x;
        this->blocks[i].y=other.blocks[i].y;
    }
    this->center.x=other.center.x;
    this->center.y=other.center.y;
    return *this;
}
