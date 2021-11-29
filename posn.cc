#include "posn.h"

Posn::Posn( const int &x, const int &y ) : x{ x }, y{ y } { }

int Posn::getX() { return x; }

int Posn::getY() { return y; }