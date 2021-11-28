#ifndef __BISHOP_H__
#define __BISHOP_H__

#include "piece.h"

class Bishop {
    public:
    Bishop( const int &side, bool moved, const char &type );
    bool isValid( Posn *original, Posn *end ) override;
};

#endif