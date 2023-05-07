#ifndef _POSITION_H
#define _POSITION_H

struct point
{
    double x;double y;
    point( double _x=0,double _y=0)
    {
        x=_x;y=_y;
    }
    void set_position(double _x,double _y)
    {
        x=_x;y=_y;
    }
};
#endif // _POSITION_H

