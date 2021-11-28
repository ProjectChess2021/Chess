#ifndef __ROOK_H__
#define __ROOK_H__

#include "piece.h"

class Rook : public Piece {
    bool moved;
    public:
    Rook( const int &side, bool moved, const char &type );
    bool isValidMove( Posn *original, Posn *end ) override;
};

#endif