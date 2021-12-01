// Created By Zichu
// Last Modified At 2351, 20211130 (By Kunling Yang)

#include "posn.h"

Posn::Posn( const int &x, const int &y ) : x{ x }, y{ y } { }

int Posn::getX() const { return x; }

int Posn::getY() const { return y; }

std::ostream &operator<<( std::ostream& out, const Posn& aPosn) {
    return out << aPosn.getX() << aPosn.getY();
}   // end Operator<<
