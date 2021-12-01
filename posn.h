// Created By Zichu
// Last Modified At 2351, 20211130 (By Kunling Yang)
#ifndef __POSN_H__
#define __POSN_H__
#include <iostream>

class Posn {
    int x;
    int y;
    public:
    Posn( const int &x, const int &y );
    int getX() const noexcept;
    int getY() const noexcept;
    friend std::ostream &operator<<( std::ostream& , const Posn& );
};

#endif
