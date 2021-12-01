#ifndef __POSN_H__
#define __POSN_H__

#include <string>

class Posn {
    int x;
    int y;
    public:
    Posn( const int &x, const int &y );
    int getX();
    int getY();
};

#endif