// Created By Zichu
// Last Modified At 2351, 20211130 (By Kunling Yang)

#include "posn.h"

Posn::Posn( const int &x, const int &y ) : x{ x }, y{ y } { }

int Posn::getX() const noexcept { return x; }

int Posn::getY() const noexcept { return y; }

std::ostream &operator<<( std::ostream& out, const Posn& aPosn) {
    return out << (char) (aPosn.getX() + 'a') << aPosn.getY() + 1;
}   // end Operator<<

bool Posn::operator==(Posn&b){
    return (x == b.getX()) && (y == b.getY());
}   // end Operator==
